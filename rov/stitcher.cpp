#include "stitcher.h"
#include<QDebug>
stitcher::stitcher() {}
// 函数用于获取当前时间的字符串格式
string getCurrentTimeString() {
    // 获取当前时间
    auto now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);

    // 格式化为字符串
    std::ostringstream os;
    os << std::put_time(now_tm, "%Y-%m-%d_%H-%M-%S"); // 使用时间格式 YYYY-MM-DD_HH-MM-SS

    return os.str();
}
/*opencv自带的stitching速度很慢，而且对多图容易出错,其中一个最大的原因是每一张图都要和其它的图去匹配，如果有10张图，除去自身不用匹配外，要匹配 10X(10-1) = 90 次。所以慢得不能忍受。
我们拍摄全景图的时候都是从左到右，或者从右到左，前后两张图一般有部分重合。如果按顺序读取图像，我们这里只对前后两张图匹配，然后连成一串即可。
拼接效果，对于相机拍照（相机可以上下左右移动，但不能旋转）的情况拼接相当好。相机发生旋转扭动则效果很差。*/
void f2_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &f2_matches)
{

    //vector<MatchesInfo> f2_matches;    //特征匹配
    BestOf2NearestMatcher matcher(false, 0.3f, 6, 6);    //定义特征匹配器，2NN方法
    matcher(features, f2_matches);    //进行特征匹配
}
//拍摄全景图的时候都是从左到右，或者从右到左，前后两张图一般有部分重合。所以一个节省时间的好办法就是我们这里只对前后两张图匹配，然后连成一串。即用串联匹配代替原匹配。从第二张图像（索引 1）开始，迭代每张图像，与前一张图像进行匹配。
//减少匹配复杂度: 只对相邻的（前后）两张图像进行匹配，而不是对所有图像进行全对全匹配，这样可以显著降低计算复杂度和时间开销。
void i_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &pairwise_matches)
{
    int num_images=features.size ();
    //1.串联匹配
    vector<vector<MatchesInfo> > f2_2;//f2_2[i] 表示 i 和 i+1 的匹配关系（0 开头，比图像数小 1）
    for (int i = 1; i < num_images; ++i)
    {
        vector<ImageFeatures> f2;
        vector<MatchesInfo> m2;
        f2.push_back (features[i-1]);
        f2.push_back (features[i]);
        f2_matcher(f2,m2);
        f2_2.push_back(m2);

    }
    //2.把串联匹配 ----按opencv stitching 拼接的匹配关系组在一起
    MatchesInfo f;//大小： n x n (n个图)
    for (int i = 0; i < num_images; ++i)
    {
        for (int j = 0; j < num_images; ++j)
        {
            //cout<<"i,j:"<<i<<","<<j<<endl;
            if(i==j)//自身不用匹配
            {
                f.src_img_idx = -1;
                f.dst_img_idx = -1;
                f.num_inliers = 0;
                f.confidence = 0;
                pairwise_matches.push_back (f);
            }else if(i+1==j)//相连（顺）
            {
                pairwise_matches.push_back (f2_2[i][1]);
                //修改匹配关系
                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
            }else if(j+1==i)//相连（倒）
            {
                pairwise_matches.push_back (f2_2[j][2]);
                //修改匹配关系
                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
            }else//其它略过
            {
                f.src_img_idx = -1;
                f.dst_img_idx = -1;
                f.num_inliers = 0;
                f.confidence = 0;
                pairwise_matches.push_back (f);
            }
            //cout<<"size:"<<pairwise_matches.size ()<<endl;
        }
    }
}

vector<string> stitcher::getFilesInDirectory(const string& directoryPath) {
    vector<std::string> file_paths;
    try {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                file_paths.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return file_paths;
}
//original stitching_detailed
int  stitcher::stitch_original(vector<string> img_names,string result_name)
{
    double ttt = getTickCount();
#if ENABLE_LOG
    int64 app_start_time = getTickCount();
#endif
    cv::setBreakOnError(true);
    int num_images = static_cast<int>(img_names.size());
    if (num_images < 2)
    {
        LOGLN("Need more images");
        return -1;
    }

    double work_scale = 1, seam_scale = 1, compose_scale = 1;
    bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

    LOGLN("Finding features...");
#if ENABLE_LOG
    int64 t = getTickCount();
#endif

    Ptr<Feature2D> finder;
    if (features_type == "surf")
    {
#if defined(HAVE_OPENCV_NONFREE) && defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            finder = new SurfFeaturesFinderGpu();
        else
            finder=xfeatures2d::SURF::create();
#else
        finder=xfeatures2d::SURF::create();
#endif
    }
    else if (features_type == "orb")
    {
        finder = ORB::create();
    }
    else
    {
        cout << "Unknown 2D features type: '" << features_type << "'.\n";
        return -1;
    }

    Mat full_img, img;
    vector<ImageFeatures> features(num_images);
    vector<Mat> images(num_images);
    vector<Size> full_img_sizes(num_images);
    double seam_work_aspect = 1;

    for (int i = 0; i < num_images; ++i)
    {
        full_img = imread(img_names[i]);
        full_img_sizes[i] = full_img.size();

        if (full_img.empty())
        {
            LOGLN("Can't open image " << img_names[i]);
            return -1;
        }
        if (work_megapix < 0)
        {
            img = full_img;
            work_scale = 1;
            is_work_scale_set = true;
        }
        else
        {
            if (!is_work_scale_set)
            {
                work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img.size().area()));
                is_work_scale_set = true;
            }
            resize(full_img, img, Size(), work_scale, work_scale);
        }
        if (!is_seam_scale_set)
        {
            seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
            seam_work_aspect = seam_scale / work_scale;
            is_seam_scale_set = true;
        }

        computeImageFeatures(finder,img,features[i]);
        features[i].img_idx = i;
        LOGLN("Features in image #" << i+1 << ": " << features[i].keypoints.size());
        resize(full_img, img, Size(), seam_scale, seam_scale);
        images[i] = img.clone();
    }
    full_img.release();
    img.release();

    LOGLN("Finding features, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    LOG("Pairwise matching");
#if ENABLE_LOG
    t = getTickCount();
#endif
    vector<MatchesInfo> pairwise_matches;
    //BestOf2NearestMatcher matcher(try_gpu, match_conf);
    //matcher(features, pairwise_matches);
    //matcher.collectGarbage();
    i_matcher(features,pairwise_matches);
    LOGLN("Pairwise matching, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    // Check if we should save matches graph
    if (save_graph)
    {
        LOGLN("Saving matches graph...");
        ofstream f(save_graph_to.c_str());
        f << matchesGraphAsString(img_names, pairwise_matches, conf_thresh);
    }

    // Leave only images we are sure are from the same panorama
    vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);
    vector<Mat> img_subset;
    vector<string> img_names_subset;
    vector<Size> full_img_sizes_subset;
    for (size_t i = 0; i < indices.size(); ++i)
    {
        img_names_subset.push_back(img_names[indices[i]]);
        img_subset.push_back(images[indices[i]]);
        full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
    }

    images = img_subset;
    img_names = img_names_subset;
    full_img_sizes = full_img_sizes_subset;

    // Check if we still have enough images
    num_images = static_cast<int>(img_names.size());
    if (num_images < 2)
    {
        LOGLN("Need more images");
        return -1;
    }

    HomographyBasedEstimator estimator;
    vector<CameraParams> cameras;
    estimator(features, pairwise_matches, cameras);

    for (size_t i = 0; i < cameras.size(); ++i)
    {
        Mat R;
        cameras[i].R.convertTo(R, CV_32F);
        cameras[i].R = R;
        LOGLN("Initial intrinsics #" << indices[i]+1 << ":\n" << cameras[i].K());
    }

    Ptr<detail::BundleAdjusterBase> adjuster;
    if (ba_cost_func == "reproj") adjuster = new detail::BundleAdjusterReproj();
    else if (ba_cost_func == "ray") adjuster = new detail::BundleAdjusterRay();
    else
    {
        cout << "Unknown bundle adjustment cost function: '" << ba_cost_func << "'.\n";
        return -1;
    }
    adjuster->setConfThresh(conf_thresh);
    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
    if (ba_refine_mask[0] == 'x') refine_mask(0,0) = 1;
    if (ba_refine_mask[1] == 'x') refine_mask(0,1) = 1;
    if (ba_refine_mask[2] == 'x') refine_mask(0,2) = 1;
    if (ba_refine_mask[3] == 'x') refine_mask(1,1) = 1;
    if (ba_refine_mask[4] == 'x') refine_mask(1,2) = 1;
    adjuster->setRefinementMask(refine_mask);
    (*adjuster)(features, pairwise_matches, cameras);

    // Find median focal length

    vector<double> focals;
    for (size_t i = 0; i < cameras.size(); ++i)
    {
        LOGLN("Camera #" << indices[i]+1 << ":\n" << cameras[i].K());
        focals.push_back(cameras[i].focal);
    }

    sort(focals.begin(), focals.end());
    float warped_image_scale;
    if (focals.size() % 2 == 1)
        warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
    else
        warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

    if (do_wave_correct)
    {
        vector<Mat> rmats;
        for (size_t i = 0; i < cameras.size(); ++i)
            rmats.push_back(cameras[i].R.clone());
        waveCorrect(rmats, wave_correct);
        for (size_t i = 0; i < cameras.size(); ++i)
            cameras[i].R = rmats[i];
    }

    LOGLN("Warping images (auxiliary)... ");
#if ENABLE_LOG
    t = getTickCount();
#endif

    vector<Point> corners(num_images);
    vector<UMat> masks_warped(num_images);
    vector<UMat> images_warped(num_images);
    vector<Size> sizes(num_images);
    vector<Mat> masks(num_images);

    // Preapre images masks
    for (int i = 0; i < num_images; ++i)
    {
        masks[i].create(images[i].size(), CV_8U);
        masks[i].setTo(Scalar::all(255));
    }

    // Warp images and their masks

    Ptr<WarperCreator> warper_creator;
#if defined(HAVE_OPENCV_GPU)
    if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
    {
        if (warp_type == "plane") warper_creator = new cv::PlaneWarperGpu();
        else if (warp_type == "cylindrical") warper_creator = new cv::CylindricalWarperGpu();
        else if (warp_type == "spherical") warper_creator = new cv::SphericalWarperGpu();
    }
    else
#endif
    {
        if (warp_type == "plane") warper_creator = new cv::PlaneWarper();
        else if (warp_type == "cylindrical") warper_creator = new cv::CylindricalWarper();
        else if (warp_type == "spherical") warper_creator = new cv::SphericalWarper();
        else if (warp_type == "fisheye") warper_creator = new cv::FisheyeWarper();
        else if (warp_type == "stereographic") warper_creator = new cv::StereographicWarper();
        else if (warp_type == "compressedPlaneA2B1") warper_creator = new cv::CompressedRectilinearWarper(2, 1);
        else if (warp_type == "compressedPlaneA1.5B1") warper_creator = new cv::CompressedRectilinearWarper(1.5, 1);
        else if (warp_type == "compressedPlanePortraitA2B1") warper_creator = new cv::CompressedRectilinearPortraitWarper(2, 1);
        else if (warp_type == "compressedPlanePortraitA1.5B1") warper_creator = new cv::CompressedRectilinearPortraitWarper(1.5, 1);
        else if (warp_type == "paniniA2B1") warper_creator = new cv::PaniniWarper(2, 1);
        else if (warp_type == "paniniA1.5B1") warper_creator = new cv::PaniniWarper(1.5, 1);
        else if (warp_type == "paniniPortraitA2B1") warper_creator = new cv::PaniniPortraitWarper(2, 1);
        else if (warp_type == "paniniPortraitA1.5B1") warper_creator = new cv::PaniniPortraitWarper(1.5, 1);
        else if (warp_type == "mercator") warper_creator = new cv::MercatorWarper();
        else if (warp_type == "transverseMercator") warper_creator = new cv::TransverseMercatorWarper();
    }

    if (warper_creator.empty())
    {
        cout << "Can't create the following warper '" << warp_type << "'\n";
        return 1;
    }

    Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));

    for (int i = 0; i < num_images; ++i)
    {
        Mat_<float> K;
        cameras[i].K().convertTo(K, CV_32F);
        float swa = (float)seam_work_aspect;
        K(0,0) *= swa; K(0,2) *= swa;
        K(1,1) *= swa; K(1,2) *= swa;

        corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
        sizes[i] = images_warped[i].size();

        warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
    }

    vector<UMat> images_warped_f(num_images);
    for (int i = 0; i < num_images; ++i)
        images_warped[i].convertTo(images_warped_f[i], CV_32F);

    LOGLN("Warping images, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(expos_comp_type);
    compensator->feed(corners, images_warped, masks_warped);

    Ptr<SeamFinder> seam_finder;
    if (seam_find_type == "no")
        seam_finder = new detail::NoSeamFinder();
    else if (seam_find_type == "voronoi")
        seam_finder = new detail::VoronoiSeamFinder();
    else if (seam_find_type == "gc_color")
    {
#if defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            seam_finder = new detail::GraphCutSeamFinderGpu(GraphCutSeamFinderBase::COST_COLOR);
        else
#endif
            seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR);
    }
    else if (seam_find_type == "gc_colorgrad")
    {
#if defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            seam_finder = new detail::GraphCutSeamFinderGpu(GraphCutSeamFinderBase::COST_COLOR_GRAD);
        else
#endif
            seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR_GRAD);
    }
    else if (seam_find_type == "dp_color")
        seam_finder = new detail::DpSeamFinder(DpSeamFinder::COLOR);
    else if (seam_find_type == "dp_colorgrad")
        seam_finder = new detail::DpSeamFinder(DpSeamFinder::COLOR_GRAD);
    if (seam_finder.empty())
    {
        cout << "Can't create the following seam finder '" << seam_find_type << "'\n";
        return 1;
    }

    seam_finder->find(images_warped_f, corners, masks_warped);

    // Release unused memory
    images.clear();
    images_warped.clear();
    images_warped_f.clear();
    masks.clear();

    LOGLN("Compositing...");
#if ENABLE_LOG
    t = getTickCount();
#endif

    Mat img_warped, img_warped_s;
    Mat dilated_mask, seam_mask, mask, mask_warped;
    Ptr<Blender> blender;
    //double compose_seam_aspect = 1;
    double compose_work_aspect = 1;

    for (int img_idx = 0; img_idx < num_images; ++img_idx)
    {
        LOGLN("Compositing image #" << indices[img_idx]+1);

        // Read image and resize it if necessary
        full_img = imread(img_names[img_idx]);
        if (!is_compose_scale_set)
        {
            if (compose_megapix > 0)
                compose_scale = min(1.0, sqrt(compose_megapix * 1e6 / full_img.size().area()));
            is_compose_scale_set = true;

            // Compute relative scales
            //compose_seam_aspect = compose_scale / seam_scale;
            compose_work_aspect = compose_scale / work_scale;

            // Update warped image scale
            warped_image_scale *= static_cast<float>(compose_work_aspect);
            warper = warper_creator->create(warped_image_scale);

            // Update corners and sizes
            for (int i = 0; i < num_images; ++i)
            {
                // Update intrinsics
                cameras[i].focal *= compose_work_aspect;
                cameras[i].ppx *= compose_work_aspect;
                cameras[i].ppy *= compose_work_aspect;

                // Update corner and size
                Size sz = full_img_sizes[i];
                if (std::abs(compose_scale - 1) > 1e-1)
                {
                    sz.width = cvRound(full_img_sizes[i].width * compose_scale);
                    sz.height = cvRound(full_img_sizes[i].height * compose_scale);
                }

                Mat K;
                cameras[i].K().convertTo(K, CV_32F);
                Rect roi = warper->warpRoi(sz, K, cameras[i].R);
                corners[i] = roi.tl();
                sizes[i] = roi.size();
            }
        }
        if (abs(compose_scale - 1) > 1e-1)
            resize(full_img, img, Size(), compose_scale, compose_scale);
        else
            img = full_img;
        full_img.release();
        Size img_size = img.size();

        Mat K;
        cameras[img_idx].K().convertTo(K, CV_32F);

        // Warp the current image
        warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

        // Warp the current image mask
        mask.create(img_size, CV_8U);
        mask.setTo(Scalar::all(255));
        warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

        // Compensate exposure
        compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);

        img_warped.convertTo(img_warped_s, CV_16S);
        img_warped.release();
        img.release();
        mask.release();

        dilate(masks_warped[img_idx], dilated_mask, Mat());
        resize(dilated_mask, seam_mask, mask_warped.size());
        mask_warped = seam_mask & mask_warped;

        if (blender.empty())
        {
            blender = Blender::createDefault(blend_type, try_gpu);
            Size dst_sz = resultRoi(corners, sizes).size();
            float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;
            if (blend_width < 1.f)
                blender = Blender::createDefault(Blender::NO, try_gpu);
            else if (blend_type == Blender::MULTI_BAND)
            {
                MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(static_cast<Blender*>(blender));
                mb->setNumBands(static_cast<int>(ceil(log(blend_width)/log(2.)) - 1.));
                LOGLN("Multi-band blender, number of bands: " << mb->numBands());
            }
            else if (blend_type == Blender::FEATHER)
            {
                FeatherBlender* fb = dynamic_cast<FeatherBlender*>(static_cast<Blender*>(blender));
                fb->setSharpness(1.f/blend_width);
                LOGLN("Feather blender, sharpness: " << fb->sharpness());
            }
            blender->prepare(corners, sizes);
        }

        // Blend the current image
        blender->feed(img_warped_s, mask_warped, corners[img_idx]);
    }

    Mat result,result1, result_mask;
    blender->blend(result, result_mask);
    LOGLN("Compositing, time: " <<((getTickCount() - t) / getTickFrequency())<< " sec");
    result1=cropBlackBorders(result);
    imwrite(result_name, result1);
    //esult.convertTo(result,CV_8UC1);
    //imshow("stitch",result);
    ttt = ((double)getTickCount() - ttt) / getTickFrequency();
    cout << "总的拼接时间:" << ttt << endl;
    waitKey(0);
    LOGLN("Finished, total time: " << ((getTickCount() - app_start_time) / getTickFrequency()) << " sec");
    return 0;
}
//improved stitching_detalled 串联匹配方式，type为1是视频流拼接，为0是读取图片序列拼接
int  stitcher::stitch(std::string path)
{
    string result_name="result.jpg";
    int type=1;
    vector<string> img_names;
    if(type)
    {
        VideoCapture video(path);
        if(!video.isOpened())
        {
            LOGLN("视频打开失败");
            exit(-1);
        }
        Mat frame,frame1;
        int i=0;
        string document="/home/stephen/图片/qqimage/videoForTest";
        while (video.read(frame)) {
            //resize(frame,frame1,Size(),0.5,0.5);
            string filepath=document+"/img_"+to_string(i)+".jpg";
            imwrite(filepath,frame);
            //imwrite(filepath,frame1);
            img_names.push_back(filepath);
            i++;
        }
    }
    else{
        img_names=getFilesInDirectory(path);
    }
    double ttt = getTickCount();
#if ENABLE_LOG
    int64 app_start_time = getTickCount();
#endif
    cv::setBreakOnError(true);
    int num_images = static_cast<int>(img_names.size());
    if (num_images < 2)
    {
        LOGLN("Need more images");
        return -1;
    }

    double work_scale = 1, seam_scale = 1, compose_scale = 1;
    bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

    LOGLN("Finding features...");
#if ENABLE_LOG
    int64 t = getTickCount();
#endif

    Ptr<Feature2D> finder;
    if (features_type == "surf")
    {
#if defined(HAVE_OPENCV_NONFREE) && defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            finder = new SurfFeaturesFinderGpu();
        else
            finder=xfeatures2d::SURF::create();
#else
        finder=xfeatures2d::SURF::create();
#endif
    }
    else if (features_type == "orb")
    {
        finder = ORB::create(1500);
    }
    else if (features_type == "akaze")
    {
        finder = AKAZE::create();
    }
    else if (features_type == "sift")
    {
        finder = SIFT::create();
    }
    else
    {
        cout << "Unknown 2D features type: '" << features_type << "'.\n";
        return -1;
    }

    Mat full_img, img;
    vector<ImageFeatures> features(num_images);
    vector<Mat> images(num_images);
    vector<Size> full_img_sizes(num_images);
    double seam_work_aspect = 1;



    for (int i = 0; i < num_images; ++i)
    {

        full_img = imread(img_names[i]);
        full_img_sizes[i] = full_img.size();

        if (full_img.empty())
        {
            LOGLN("Can't open image " << img_names[i]);
            return -1;
        }
        if (work_megapix < 0)
        {
            img = full_img;
            work_scale = 1;
            is_work_scale_set = true;
        }
        else
        {
            if (!is_work_scale_set)
            {
                work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img.size().area()));
                is_work_scale_set = true;
            }
            resize(full_img, img, Size(), work_scale, work_scale);
        }
        if (!is_seam_scale_set)
        {
            seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
            seam_work_aspect = seam_scale / work_scale;
            is_seam_scale_set = true;
        }
        //features[i].img_size=img.size();
        //finder->detectAndCompute(img,noArray(),features[i].keypoints,features[i].descriptors);
        computeImageFeatures(finder,img,features[i]);
        features[i].img_idx = i;
        LOGLN("Features in image #" << i+1 << ": " << features[i].keypoints.size());
        resize(full_img, img, Size(), seam_scale, seam_scale);
        images[i] = img.clone();
    }
    full_img.release();
    img.release();

    LOGLN("Finding features, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    LOG("Pairwise matching");
#if ENABLE_LOG
    t = getTickCount();
#endif
    vector<MatchesInfo> pairwise_matches;
    //BestOf2NearestMatcher matcher(try_gpu, match_conf);
    //matcher(features, pairwise_matches);
    //matcher.collectGarbage();
    i_matcher(features,pairwise_matches);
    LOGLN("Pairwise matching, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    // Check if we should save matches graph
    if (save_graph)
    {
        LOGLN("Saving matches graph...");
        ofstream f(save_graph_to.c_str());
        f << matchesGraphAsString(img_names, pairwise_matches, conf_thresh);
    }

    // Leave only images we are sure are from the same panorama
    vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);
    vector<Mat> img_subset;
    vector<string> img_names_subset;
    vector<Size> full_img_sizes_subset;
    for (size_t i = 0; i < indices.size(); ++i)
    {
        img_names_subset.push_back(img_names[indices[i]]);
        img_subset.push_back(images[indices[i]]);
        full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
    }

    images = img_subset;
    img_names = img_names_subset;
    full_img_sizes = full_img_sizes_subset;

    // Check if we still have enough images
    num_images = static_cast<int>(img_names.size());
    if (num_images < 2)
    {
        LOGLN("Need more images");
        return -1;
    }

    HomographyBasedEstimator estimator;
    vector<CameraParams> cameras;
    estimator(features, pairwise_matches, cameras);

    for (size_t i = 0; i < cameras.size(); ++i)
    {
        Mat R;
        cameras[i].R.convertTo(R, CV_32F);
        cameras[i].R = R;
        LOGLN("Initial intrinsics #" << indices[i]+1 << ":\n" << cameras[i].K());
    }

    Ptr<detail::BundleAdjusterBase> adjuster;
    if (ba_cost_func == "reproj") adjuster = new detail::BundleAdjusterReproj();
    else if (ba_cost_func == "ray") adjuster = new detail::BundleAdjusterRay();
    else
    {
        cout << "Unknown bundle adjustment cost function: '" << ba_cost_func << "'.\n";
        return -1;
    }
    adjuster->setConfThresh(conf_thresh);
    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
    if (ba_refine_mask[0] == 'x') refine_mask(0,0) = 1;
    if (ba_refine_mask[1] == 'x') refine_mask(0,1) = 1;
    if (ba_refine_mask[2] == 'x') refine_mask(0,2) = 1;
    if (ba_refine_mask[3] == 'x') refine_mask(1,1) = 1;
    if (ba_refine_mask[4] == 'x') refine_mask(1,2) = 1;
    adjuster->setRefinementMask(refine_mask);
    (*adjuster)(features, pairwise_matches, cameras);

    // Find median focal length

    vector<double> focals;
    for (size_t i = 0; i < cameras.size(); ++i)
    {
        LOGLN("Camera #" << indices[i]+1 << ":\n" << cameras[i].K());
        focals.push_back(cameras[i].focal);
    }

    sort(focals.begin(), focals.end());
    float warped_image_scale;
    if (focals.size() % 2 == 1)
        warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
    else
        warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

    if (do_wave_correct)
    {
        vector<Mat> rmats;
        for (size_t i = 0; i < cameras.size(); ++i)
            rmats.push_back(cameras[i].R.clone());
        waveCorrect(rmats, wave_correct);
        for (size_t i = 0; i < cameras.size(); ++i)
            cameras[i].R = rmats[i];
    }

    LOGLN("Warping images (auxiliary)... ");
#if ENABLE_LOG
    t = getTickCount();
#endif

    vector<Point> corners(num_images);
    vector<UMat> masks_warped(num_images);
    vector<UMat> images_warped(num_images);
    vector<Size> sizes(num_images);
    vector<Mat> masks(num_images);

    // Preapre images masks
    for (int i = 0; i < num_images; ++i)
    {
        masks[i].create(images[i].size(), CV_8U);
        masks[i].setTo(Scalar::all(255));
    }

    // Warp images and their masks

    Ptr<WarperCreator> warper_creator;
#if defined(HAVE_OPENCV_GPU)
    if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
    {
        if (warp_type == "plane") warper_creator = new cv::PlaneWarperGpu();
        else if (warp_type == "cylindrical") warper_creator = new cv::CylindricalWarperGpu();
        else if (warp_type == "spherical") warper_creator = new cv::SphericalWarperGpu();
    }
    else
#endif
    {
        if (warp_type == "plane") warper_creator = new cv::PlaneWarper();
        else if (warp_type == "cylindrical") warper_creator = new cv::CylindricalWarper();
        else if (warp_type == "spherical") warper_creator = new cv::SphericalWarper();
        else if (warp_type == "fisheye") warper_creator = new cv::FisheyeWarper();
        else if (warp_type == "stereographic") warper_creator = new cv::StereographicWarper();
        else if (warp_type == "compressedPlaneA2B1") warper_creator = new cv::CompressedRectilinearWarper(2, 1);
        else if (warp_type == "compressedPlaneA1.5B1") warper_creator = new cv::CompressedRectilinearWarper(1.5, 1);
        else if (warp_type == "compressedPlanePortraitA2B1") warper_creator = new cv::CompressedRectilinearPortraitWarper(2, 1);
        else if (warp_type == "compressedPlanePortraitA1.5B1") warper_creator = new cv::CompressedRectilinearPortraitWarper(1.5, 1);
        else if (warp_type == "paniniA2B1") warper_creator = new cv::PaniniWarper(2, 1);
        else if (warp_type == "paniniA1.5B1") warper_creator = new cv::PaniniWarper(1.5, 1);
        else if (warp_type == "paniniPortraitA2B1") warper_creator = new cv::PaniniPortraitWarper(2, 1);
        else if (warp_type == "paniniPortraitA1.5B1") warper_creator = new cv::PaniniPortraitWarper(1.5, 1);
        else if (warp_type == "mercator") warper_creator = new cv::MercatorWarper();
        else if (warp_type == "transverseMercator") warper_creator = new cv::TransverseMercatorWarper();
    }

    if (warper_creator.empty())
    {
        cout << "Can't create the following warper '" << warp_type << "'\n";
        return 1;
    }

    Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));

    for (int i = 0; i < num_images; ++i)
    {
        Mat_<float> K;
        cameras[i].K().convertTo(K, CV_32F);
        float swa = (float)seam_work_aspect;
        K(0,0) *= swa; K(0,2) *= swa;
        K(1,1) *= swa; K(1,2) *= swa;

        corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
        sizes[i] = images_warped[i].size();

        warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
    }

    vector<UMat> images_warped_f(num_images);
    for (int i = 0; i < num_images; ++i)
        images_warped[i].convertTo(images_warped_f[i], CV_32F);

    LOGLN("Warping images, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

    Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(expos_comp_type);
    compensator->feed(corners, images_warped, masks_warped);

    Ptr<SeamFinder> seam_finder;
    if (seam_find_type == "no")
        seam_finder = new detail::NoSeamFinder();
    else if (seam_find_type == "voronoi")
        seam_finder = new detail::VoronoiSeamFinder();
    else if (seam_find_type == "gc_color")
    {
#if defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            seam_finder = new detail::GraphCutSeamFinderGpu(GraphCutSeamFinderBase::COST_COLOR);
        else
#endif
            seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR);
    }
    else if (seam_find_type == "gc_colorgrad")
    {
#if defined(HAVE_OPENCV_GPU)
        if (try_gpu && gpu::getCudaEnabledDeviceCount() > 0)
            seam_finder = new detail::GraphCutSeamFinderGpu(GraphCutSeamFinderBase::COST_COLOR_GRAD);
        else
#endif
            seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR_GRAD);
    }
    else if (seam_find_type == "dp_color")
        seam_finder = new detail::DpSeamFinder(DpSeamFinder::COLOR);
    else if (seam_find_type == "dp_colorgrad")
        seam_finder = new detail::DpSeamFinder(DpSeamFinder::COLOR_GRAD);
    if (seam_finder.empty())
    {
        cout << "Can't create the following seam finder '" << seam_find_type << "'\n";
        return 1;
    }

    seam_finder->find(images_warped_f, corners, masks_warped);

    // Release unused memory
    images.clear();
    images_warped.clear();
    images_warped_f.clear();
    masks.clear();

    LOGLN("Compositing...");
#if ENABLE_LOG
    t = getTickCount();
#endif

    Mat img_warped, img_warped_s;
    Mat dilated_mask, seam_mask, mask, mask_warped;
    Ptr<Blender> blender;
    //double compose_seam_aspect = 1;
    double compose_work_aspect = 1;

    for (int img_idx = 0; img_idx < num_images; ++img_idx)
    {
        LOGLN("Compositing image #" << indices[img_idx]+1);

        // Read image and resize it if necessary
        full_img = imread(img_names[img_idx]);
        if (!is_compose_scale_set)
        {
            if (compose_megapix > 0)
                compose_scale = min(1.0, sqrt(compose_megapix * 1e6 / full_img.size().area()));
            is_compose_scale_set = true;

            // Compute relative scales
            //compose_seam_aspect = compose_scale / seam_scale;
            compose_work_aspect = compose_scale / work_scale;

            // Update warped image scale
            warped_image_scale *= static_cast<float>(compose_work_aspect);
            warper = warper_creator->create(warped_image_scale);

            // Update corners and sizes
            for (int i = 0; i < num_images; ++i)
            {
                // Update intrinsics
                cameras[i].focal *= compose_work_aspect;
                cameras[i].ppx *= compose_work_aspect;
                cameras[i].ppy *= compose_work_aspect;

                // Update corner and size
                Size sz = full_img_sizes[i];
                if (std::abs(compose_scale - 1) > 1e-1)
                {
                    sz.width = cvRound(full_img_sizes[i].width * compose_scale);
                    sz.height = cvRound(full_img_sizes[i].height * compose_scale);
                }

                Mat K;
                cameras[i].K().convertTo(K, CV_32F);
                Rect roi = warper->warpRoi(sz, K, cameras[i].R);
                corners[i] = roi.tl();
                sizes[i] = roi.size();
            }
        }
        if (abs(compose_scale - 1) > 1e-1)
            resize(full_img, img, Size(), compose_scale, compose_scale);
        else
            img = full_img;
        full_img.release();
        Size img_size = img.size();

        Mat K;
        cameras[img_idx].K().convertTo(K, CV_32F);

        // Warp the current image
        warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

        // Warp the current image mask
        mask.create(img_size, CV_8U);
        mask.setTo(Scalar::all(255));
        warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

        // Compensate exposure
        compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);

        img_warped.convertTo(img_warped_s, CV_16S);
        img_warped.release();
        img.release();
        mask.release();

        dilate(masks_warped[img_idx], dilated_mask, Mat());
        resize(dilated_mask, seam_mask, mask_warped.size());
        mask_warped = seam_mask & mask_warped;

        if (blender.empty())
        {
            blender = Blender::createDefault(blend_type, try_gpu);
            Size dst_sz = resultRoi(corners, sizes).size();
            float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;
            if (blend_width < 1.f)
                blender = Blender::createDefault(Blender::NO, try_gpu);
            else if (blend_type == Blender::MULTI_BAND)
            {
                MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(static_cast<Blender*>(blender));
                mb->setNumBands(static_cast<int>(ceil(log(blend_width)/log(2.)) - 1.));
                LOGLN("Multi-band blender, number of bands: " << mb->numBands());
            }
            else if (blend_type == Blender::FEATHER)
            {
                FeatherBlender* fb = dynamic_cast<FeatherBlender*>(static_cast<Blender*>(blender));
                fb->setSharpness(1.f/blend_width);
                LOGLN("Feather blender, sharpness: " << fb->sharpness());
            }
            blender->prepare(corners, sizes);
        }

        // Blend the current image
        blender->feed(img_warped_s, mask_warped, corners[img_idx]);
    }

    Mat result,result1,result2, result_mask;
    blender->blend(result, result_mask);
    LOGLN("Compositing, time: " <<((getTickCount() - t) / getTickFrequency())<< " sec");
    ttt = ((double)getTickCount() - ttt) / getTickFrequency();
    cout << "总的拼接时间:" << ttt << endl;
    //waitKey(0);
    string outputDir = "/home/stephen/图片/stitchedimgs";
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    string filename = outputDir + "/stitched_" + std::to_string(timestamp) + ".jpg";//时间戳当文件名
    imwrite(filename,result);
    result1=cropBlackBorders(result);
    //resize(result1,result2,Size(),2,2);
    imwrite(result_name, result1);
    //esult.convertTo(result,CV_8UC1);
    //imshow("stitch",result);
    LOGLN("Finished, total time: " << ((getTickCount() - app_start_time) / getTickFrequency()) << " sec");
    return 0;
}
cv::Mat stitcher::cropBlackBorders(cv::Mat& img)
{
    qDebug() << "img channels = " << img.channels();
    int nOffSet = 1;//偏移量，防止弧度极小时，不能往回退
    unsigned long AAtime = 0, BBtime = 0; //check processing time
    AAtime = cv::getTickCount(); //check processing time
    cv::Point2i leftTopPt;
    for (int i = 1; i < img.rows; ++i) {
        Vec3b& bgra = img.at<Vec3b>(i, i);
        if (!(bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0)) { //不等于黑色
            leftTopPt.x = i;
            leftTopPt.y = i;
            int x = leftTopPt.x - 1;
            for (; x > 0; --x) {//从第x列到第0列，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(leftTopPt.y + nOffSet, x);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (leftTopPt.x != x + 1)
            {
                leftTopPt.x = x + 1;
                leftTopPt.y += nOffSet;
            }
            int y = leftTopPt.y - 1;
            for (; y > 0; --y) {//从第y行到第0行，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(y, leftTopPt.x + nOffSet);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (leftTopPt.y != y + 1)
            {
                leftTopPt.y = y + 1;
                leftTopPt.x += nOffSet;
            }
            break;
        }
    }

    cv::Point2i rightTopPt;
    for (int i = 1; i < img.rows; ++i) {
        int x = img.cols - i;
        int y = i;
        Vec3b& bgra = img.at<Vec3b>(y, x);
        if (!(bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0)) { //不等于黑色
            rightTopPt.x = x;
            rightTopPt.y = y;
            x = rightTopPt.x + 1;
            for (; x < img.cols; ++x) {//从第x列到最后一列，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(rightTopPt.y + nOffSet, x);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (rightTopPt.x != x - 1)
            {
                rightTopPt.x = x - 1;
                rightTopPt.y += nOffSet;
            }
            y = rightTopPt.y - 1;
            for (; y > 0; --y) {//从第y行到第0行，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(y, rightTopPt.x - nOffSet);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (rightTopPt.y != y + 1)
            {
                rightTopPt.y = y + 1;
                rightTopPt.x -= nOffSet;
            }
            break;
        }
    }

    cv::Point2i leftBottomPt;
    for (int i = 1; i < img.rows; ++i) {
        int x = i;
        int y = img.rows - i;
        Vec3b& bgra = img.at<Vec3b>(y, x);
        if (!(bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0)) { //不等于黑色
            leftBottomPt.x = x;
            leftBottomPt.y = y;
            x = leftBottomPt.x - 1;
            for (; x > 0; --x) {//从第x列到第0列，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(leftBottomPt.y - nOffSet, x);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (leftBottomPt.x != x + 1)
            {
                leftBottomPt.x = x + 1;
                leftBottomPt.y -= nOffSet;
            }
            y = leftBottomPt.y + 1;
            for (; y < img.rows; ++y) {//从第y行到最后一行，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(y, leftBottomPt.x + nOffSet);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (leftBottomPt.y != y - 1)
            {
                leftBottomPt.y = y - 1;
                leftBottomPt.x += nOffSet;
            }
            break;
        }
    }

    cv::Point2i rightBottomPt;
    for (int i = 1; i < img.rows; ++i) {
        int x = img.cols - i;
        int y = img.rows - i;
        Vec3b& bgra = img.at<Vec3b>(y, x);
        if (!(bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0)) { //不等于黑色
            rightBottomPt.x = x;
            rightBottomPt.y = y;
            x = rightBottomPt.x + 1;
            for (; x < img.cols; ++x) {//从第x列到最后一列，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(rightBottomPt.y - nOffSet, x);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (rightBottomPt.x != x - 1)
            {
                rightBottomPt.x = x - 1;
                rightBottomPt.y -= nOffSet;
            }
            y = rightBottomPt.y + 1;
            for (; y < img.rows; ++y) {//从第y行到最后一行，往回找到最近一个黑点
                Vec3b& bgra = img.at<Vec3b>(y, rightBottomPt.x - nOffSet);
                if (bgra[0] == 0 && bgra[1] == 0 && bgra[2] == 0) { //等于黑色
                    break;
                }
            }
            if (rightBottomPt.y != y - 1)
            {
                rightBottomPt.y = y - 1;
                rightBottomPt.x -= nOffSet;
            }
            break;
        }
    }
    int topMaxY = max(leftTopPt.y, rightTopPt.y);
    int leftMaxX = max(leftTopPt.x, leftBottomPt.x);
    int rightMinX = min(rightTopPt.x, rightBottomPt.x);
    int bottomMinY = min(leftBottomPt.y, rightBottomPt.y);
    leftTopPt.y = topMaxY;
    rightTopPt.y = topMaxY;
    leftTopPt.x = leftMaxX;
    leftBottomPt.x = leftMaxX;
    rightTopPt.x = rightMinX;
    rightBottomPt.x = rightMinX;
    leftBottomPt.y = bottomMinY;
    rightBottomPt.y = bottomMinY;
    Mat tempMat = img(cv::Rect(leftTopPt.x, leftTopPt.y, rightBottomPt.x - leftTopPt.x, rightBottomPt.y - leftTopPt.y));
    BBtime = cv::getTickCount(); //check processing time
    float costtime = (BBtime - AAtime) / cv::getTickFrequency();
    QString costimeresult = QString("裁剪时间：%1").arg(costtime);
    qInfo() << costimeresult;
    return tempMat;
}

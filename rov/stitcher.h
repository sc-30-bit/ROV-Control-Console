#ifndef STITCHER_H
#define STITCHER_H
#include<vector>
#include<iostream>
#include<opencv2/opencv.hpp>
#include <filesystem>
#include<fstream>
#include<QObject>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include"opencv2/stitching/detail/matchers.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>    // 需要包含以使用 std::put_time
#include <ctime>      // 需要包含以使用 std::time_t 和 std::localtime
#include <sstream>    // 需要包含以使用 std::ostringstream


namespace fs = std::filesystem;
using namespace std;
using namespace cv;
using namespace cv::detail;

#define ENABLE_LOG 1
#define LOG(msg) std::cout << msg
#define LOGLN(msg) std::cout << msg << std::endl

class stitcher : public QObject
{
    Q_OBJECT
public:
    stitcher();
    //int  stitch(vector<string> img_names,string result_name);
    int  stitch_original(vector<string> img_names,string result_name);
    vector<string> getFilesInDirectory(const string& directoryPath);
    cv::Mat cropBlackBorders(cv::Mat& img);
public slots:
    int  stitch(string path);
private:
    //参数设置详情
    // --preview                                以预览模式运行拼接，速度更快但输出图像分辨率更低
    // --try_cuda(true|false)                       是否尝试使用CUDA加速，默认no
    // --work_megapix <float>                   图像配准阶段分辨率（单位：百万像素），默认0.6
    // --features(surf|orb|sift|akaze)          特征检测算法类型，默认surf（若不可用则用orb）
    // --matcher(homography|affine)             图像匹配变换模型，默认未指定
    // --estimator(homography|affine)           变换矩阵估计算法类型，默认未指定
    // --match_conf <float>                     特征匹配置信度阈值，surf默认0.65/orb默认0.3
    // --conf_thresh <float>                    全景图关联置信度阈值，默认1.0
    // --ba(no|reproj|ray|affine)               捆绑调整代价函数，默认ray
    // --ba_refine_mask(mask)                   捆绑调整优化掩码（格式：x_xxx），默认xxxxx
    // --wave_correct(no|horiz|vert)            波形校正模式，默认horiz
    // --save_graph <file_name>                 保存DOT格式匹配关系图到指定文件
    // --warp(affine|plane|cylindrical|...)     映射表面类型，默认spherical
    // --seam_megapix <float>                   拼接缝估计分辨率（单位：百万像素），默认0.1
    // --seam(no|voronoi|gc_color|gc_colorgrad) 拼接缝隙估计方法，默认gc_color
    // --compose_megapix <float>                合成阶段分辨率（-1=原始分辨率），默认-1
    // --expos_comp(no|gain|gain_blocks|...)    曝光补偿方法，默认gain_blocks
    // --expos_comp_nr_feeds <int>              曝光补偿输入次数，默认1
    // --expos_comp_nr_filtering <int>          曝光补偿增益滤波迭代次数，默认2
    // --expos_comp_block_size <int>            曝光补偿块大小（像素），默认32
    // --blend(no|feather|multiband)            融合方法，默认multiband
    // --blend_strength <float>                 融合强度[0-100]，默认5
    // --output <result_img>                    输出文件名，默认result.jpg
    // --timelapse(as_is|crop)                  输出逐帧变形图像用于延时摄影
    // --rangewidth <int>                       使用range_width限制匹配图像数量
    //vector<string> img_names;
    //string result_name;
    bool preview = false;
    bool try_gpu = true;
    double work_megapix = 0.6;
    double seam_megapix = 0.1;
    double compose_megapix = -1;
    float conf_thresh = 1.f;
    string features_type = "surf";
    string ba_cost_func = "ray";//把费时的光束平差法改成"ray";射线发散误差方法
    string ba_refine_mask = "xxxxx";
    bool do_wave_correct = true;
    WaveCorrectKind wave_correct = detail::WAVE_CORRECT_HORIZ;
    bool save_graph = false;
    std::string save_graph_to;
    string warp_type = "spherical";
    int expos_comp_type = ExposureCompensator::GAIN;//把费时的曝光补偿改成ExposureCompensator::GAIN;//增益法
    float match_conf = 0.65f;
    string seam_find_type = "gc_color";//把也费时的寻找接缝线改成"voronoi"; //逐点法
    int blend_type = Blender::MULTI_BAND;
    float blend_strength = 5;
};
#endif // STITCHER_H

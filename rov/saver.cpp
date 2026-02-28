#include "saver.h"

saver::saver() {}

Mat saver::QImageToMat(const QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_Grayscale8: // 灰度图，每个像素点1个字节（8位）
        // Mat构造：行数，列数，存储结构，数据，step每行多少字节
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_ARGB32: // uint32存储0xAARRGGBB，pc一般小端存储低位在前，所以字节顺序就成了BGRA
    case QImage::Format_RGB32: // Alpha为FF
        //    case QImage::Format_ARGB32_Premultiplied:
        //        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        //        break;
    case QImage::Format_ARGB32_Premultiplied:
    {
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        std::vector<cv::Mat>channels;
        split(mat, channels);
        channels.pop_back();
        cv::merge(channels, mat);
        return mat;
    }
    case QImage::Format_RGB888: // RR,GG,BB字节顺序存储
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        return mat.clone();
        break;
    case QImage::Format_RGBA64: // uint64存储，顺序和Format_ARGB32相反，RGBA
        mat = cv::Mat(image.height(), image.width(), CV_16UC4, (void*)image.constBits(), image.bytesPerLine());
        // opencv需要转为BGRA的字节顺序
        cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGRA);
        break;

    case QImage::Format_Mono:
    case QImage::Format_MonoLSB:
    {
        QImage rgbImage = image.convertToFormat(QImage::Format_Grayscale8);
        return cv::Mat(rgbImage.height(), rgbImage.width(), CV_8UC1, (void*)rgbImage.bits(), rgbImage.bytesPerLine()).clone();
    }

    case QImage::Format_Indexed8:
    {
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        return mat.clone();
    }
    default:
        return mat;

    }
    return mat;
}

void saver::savePicture(const QPixmap &pixmap,const int &cameraIndex)
{
    QString rootdir=rootdir1;
    if(cameraIndex==1){
        rootdir = rootdir1;
    }else if(cameraIndex==2){
        rootdir = rootdir2;
    }else{
        rootdir=rootdir3;
    }

    // 获取当前日期
    QString dateFolder = QDate::currentDate().toString("yyyy-MM-dd"); // 创建以日期命名的文件夹
    QString imageFolder = "Image"; // 子文件夹名称

    // 获取当前时间
    QString timeFileName = QTime::currentTime().toString("HH-mm-ss") + ".png"; // 生成以时间命名的文件名

    // 拼接完整的保存路径
    QString fullPath = rootdir + "/" + dateFolder + "/" + imageFolder + "/" + timeFileName;

    // 先创建日期文件夹
    QDir dir;
    if (!dir.exists(rootdir + "/" + dateFolder)) {
        dir.mkpath(rootdir + "/" + dateFolder); // 创建以日期为名的文件夹
    }

    // 创建Image子文件夹
    if (!dir.exists(fullPath)) {
        dir.mkdir(rootdir + "/" + dateFolder + "/" + imageFolder); // 创建Image子文件夹
    }

    // 保存pixmap为文件
    if (pixmap.save(fullPath, "PNG")) {
        qDebug() << "Image saved successfully:" << fullPath;
    } else {
        qDebug() << "Failed to save image.";
    }
}

void saver::saveVideo( const int &cameraIndex)
{
    // 设置根目录，根据摄像头索引选择不同的路径
    QString rootdir;
    std::vector<Mat> frames;
    if(cameraIndex==1){
        frames=frames1;
        rootdir = rootdir1;
    }else if(cameraIndex==2){
        frames=frames2;
        rootdir = rootdir2;
    }else{
        frames=frames3;
        rootdir=rootdir3;
    }


    // 获取当前日期，创建以日期命名的文件夹
    QString dateFolder = QDate::currentDate().toString("yyyy-MM-dd");
    QString videoFolder = "Video"; // 子文件夹名称

    // 获取当前时间，作为视频文件名
    QString timeFileName = QTime::currentTime().toString("HH-mm-ss") + ".mp4";

    // 拼接完整的保存路径
    QString fullPath = rootdir + "/" + dateFolder + "/" + videoFolder + "/" + timeFileName;

    // 创建日期文件夹
    QDir dir;
    if (!dir.exists(rootdir + "/" + dateFolder)) {
        dir.mkpath(rootdir + "/" + dateFolder); // 创建日期文件夹
    }

    // 创建Video子文件夹
    if (!dir.exists(rootdir + "/" + dateFolder + "/" + videoFolder)) {
        dir.mkpath(rootdir + "/" + dateFolder + "/" + videoFolder); // 创建Video子文件夹
    }

    // 获取第一帧的尺寸，假设所有图像的尺寸相同
    if (frames.empty()) {
        qDebug() << "No frames to save.";
        return;
    }

    // 获取视频的尺寸（假设所有图像尺寸一致）
    int width = frames[0].cols;
    int height = frames[0].rows;

    // 设置视频的帧率（可根据需求调整）
    double fps = 30.0;

    // 创建VideoWriter，指定视频编码、帧率、尺寸
    cv::VideoWriter videoWriter;
    videoWriter.open(fullPath.toStdString(), cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, cv::Size(width, height));

    // 检查VideoWriter是否打开成功
    if (!videoWriter.isOpened()) {
        qDebug() << "Failed to open video writer.";
        return;
    }

    // 将每一帧写入视频
    for (const auto &frame : frames) {
        videoWriter.write(frame);
    }

    // 释放视频资源
    videoWriter.release();
    if(cameraIndex==1){
        frames1.clear();
    }else if(cameraIndex==2){
        frames2.clear();
    }else{
        frames3.clear();
        emit stitching(fullPath.toStdString());
    }
    qDebug() << "Video saved successfully:" << fullPath;
}


void saver::fillVetctor(const QPixmap &videoFrame, const int &cameraIndex)
{
    if(cameraIndex==1){
        frames1.push_back(QImageToMat(videoFrame.toImage()));
    }
    else if(cameraIndex==2){
        frames2.push_back(QImageToMat(videoFrame.toImage()));
    }else{
        frames3.push_back(QImageToMat(videoFrame.toImage()));
    }
}

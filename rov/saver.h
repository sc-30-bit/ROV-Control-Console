#ifndef SAVER_H
#define SAVER_H

#include <QObject>
#include<QPixmap>
#include<QString>
#include<opencv2/opencv.hpp>
#include <QDate>
#include <QTime>
#include<string>
#include <QDir>
#include <QFileDialog>
#include <QCoreApplication>
#include<QDebug>

using namespace cv;

class saver : public QObject
{
    Q_OBJECT
public:
    saver();
    Mat QImageToMat(const QImage image);

public slots:
    void savePicture(const QPixmap &pixmap,const int &cameraIndex);
    void saveVideo(const int &cameraIndex);
    void fillVetctor(const QPixmap &videoFrame,const int &cameraIndex);
private:
    //RePlay for Camera1
    QString rootdir1="/home/stephen/桌面/Monitor/Camera1";
    //RePlay for Camera2
    QString rootdir2="/home/stephen/桌面/Monitor/Camera2";
    QString rootdir3="/home/stephen/桌面/Monitor/stitichingStream";
    std::vector<Mat> frames1;
    std::vector<Mat> frames2;
    std::vector<Mat> frames3;
signals:
    void stitching(std::string filepath);
};

#endif // SAVER_H

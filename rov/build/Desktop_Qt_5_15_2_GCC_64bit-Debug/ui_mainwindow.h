/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mapview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QLabel *label_heading;
    QLabel *label_pos_z;
    QLabel *label_4;
    QLabel *label_6;
    MapView *mapView;
    QLabel *label_depth;
    QLabel *label_pos_x;
    QLabel *label_dist_b;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_dist_a;
    QLabel *label_7;
    QLabel *label_base_dist;
    QLabel *label_5;
    QLabel *label_pos_y;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1561, 1064);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1210, 80, 80, 21));
        QFont font;
        font.setPointSize(13);
        label_2->setFont(font);
        label_heading = new QLabel(centralwidget);
        label_heading->setObjectName(QString::fromUtf8("label_heading"));
        label_heading->setGeometry(QRect(1180, 780, 131, 21));
        label_heading->setFont(font);
        label_pos_z = new QLabel(centralwidget);
        label_pos_z->setObjectName(QString::fromUtf8("label_pos_z"));
        label_pos_z->setGeometry(QRect(1320, 450, 141, 21));
        label_pos_z->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1210, 230, 80, 21));
        label_4->setFont(font);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1210, 380, 80, 21));
        label_6->setFont(font);
        mapView = new MapView(centralwidget);
        mapView->setObjectName(QString::fromUtf8("mapView"));
        mapView->setGeometry(QRect(60, 50, 1061, 911));
        label_depth = new QLabel(centralwidget);
        label_depth->setObjectName(QString::fromUtf8("label_depth"));
        label_depth->setGeometry(QRect(1320, 230, 131, 21));
        label_depth->setFont(font);
        label_pos_x = new QLabel(centralwidget);
        label_pos_x->setObjectName(QString::fromUtf8("label_pos_x"));
        label_pos_x->setGeometry(QRect(1320, 300, 131, 21));
        label_pos_x->setFont(font);
        label_dist_b = new QLabel(centralwidget);
        label_dist_b->setObjectName(QString::fromUtf8("label_dist_b"));
        label_dist_b->setGeometry(QRect(1320, 160, 121, 21));
        label_dist_b->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1210, 160, 80, 21));
        label_3->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1180, 630, 80, 21));
        label->setFont(font);
        label_dist_a = new QLabel(centralwidget);
        label_dist_a->setObjectName(QString::fromUtf8("label_dist_a"));
        label_dist_a->setGeometry(QRect(1320, 80, 141, 21));
        label_dist_a->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1210, 450, 80, 21));
        label_7->setFont(font);
        label_base_dist = new QLabel(centralwidget);
        label_base_dist->setObjectName(QString::fromUtf8("label_base_dist"));
        label_base_dist->setGeometry(QRect(1320, 630, 141, 21));
        label_base_dist->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1210, 300, 80, 21));
        label_5->setFont(font);
        label_pos_y = new QLabel(centralwidget);
        label_pos_y->setObjectName(QString::fromUtf8("label_pos_y"));
        label_pos_y->setGeometry(QRect(1320, 380, 141, 21));
        label_pos_y->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1561, 32));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "dist_A:", nullptr));
        label_heading->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_pos_z->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "depth:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Y\357\274\232", nullptr));
        label_depth->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_pos_x->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_dist_b->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "dist_B:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\237\272\347\272\277\350\267\235\347\246\273\357\274\232", nullptr));
        label_dist_a->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Z\357\274\232", nullptr));
        label_base_dist->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X\357\274\232", nullptr));
        label_pos_y->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

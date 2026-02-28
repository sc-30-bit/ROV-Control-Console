/********************************************************************************
** Form generated from reading UI file 'localizationmap.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCALIZATIONMAP_H
#define UI_LOCALIZATIONMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mapview.h"

QT_BEGIN_NAMESPACE

class Ui_LocalizationMap
{
public:
    QWidget *centralwidget;
    QLabel *label_pos_z;
    QLabel *label_pos_y;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_dist_a;
    QLabel *label_4;
    QLabel *label_6;
    MapView *mapView;
    QLabel *label_pos_x;
    QLabel *label_dist_b;
    QLabel *label_7;
    QLabel *label_depth;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LocalizationMap)
    {
        if (LocalizationMap->objectName().isEmpty())
            LocalizationMap->setObjectName(QString::fromUtf8("LocalizationMap"));
        LocalizationMap->resize(1561, 1064);
        centralwidget = new QWidget(LocalizationMap);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_pos_z = new QLabel(centralwidget);
        label_pos_z->setObjectName(QString::fromUtf8("label_pos_z"));
        label_pos_z->setGeometry(QRect(1320, 450, 141, 21));
        QFont font;
        font.setPointSize(13);
        label_pos_z->setFont(font);
        label_pos_y = new QLabel(centralwidget);
        label_pos_y->setObjectName(QString::fromUtf8("label_pos_y"));
        label_pos_y->setGeometry(QRect(1320, 380, 141, 21));
        label_pos_y->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1210, 80, 80, 21));
        label_2->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1210, 300, 80, 21));
        label_5->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1210, 160, 80, 21));
        label_3->setFont(font);
        label_dist_a = new QLabel(centralwidget);
        label_dist_a->setObjectName(QString::fromUtf8("label_dist_a"));
        label_dist_a->setGeometry(QRect(1320, 80, 141, 21));
        label_dist_a->setFont(font);
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
        label_pos_x = new QLabel(centralwidget);
        label_pos_x->setObjectName(QString::fromUtf8("label_pos_x"));
        label_pos_x->setGeometry(QRect(1320, 300, 131, 21));
        label_pos_x->setFont(font);
        label_dist_b = new QLabel(centralwidget);
        label_dist_b->setObjectName(QString::fromUtf8("label_dist_b"));
        label_dist_b->setGeometry(QRect(1320, 160, 121, 21));
        label_dist_b->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1210, 450, 80, 21));
        label_7->setFont(font);
        label_depth = new QLabel(centralwidget);
        label_depth->setObjectName(QString::fromUtf8("label_depth"));
        label_depth->setGeometry(QRect(1320, 230, 131, 21));
        label_depth->setFont(font);
        LocalizationMap->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LocalizationMap);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1561, 32));
        LocalizationMap->setMenuBar(menubar);
        statusbar = new QStatusBar(LocalizationMap);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LocalizationMap->setStatusBar(statusbar);

        retranslateUi(LocalizationMap);

        QMetaObject::connectSlotsByName(LocalizationMap);
    } // setupUi

    void retranslateUi(QMainWindow *LocalizationMap)
    {
        LocalizationMap->setWindowTitle(QCoreApplication::translate("LocalizationMap", "MainWindow", nullptr));
        label_pos_z->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
        label_pos_y->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
        label_2->setText(QCoreApplication::translate("LocalizationMap", "dist_A:", nullptr));
        label_5->setText(QCoreApplication::translate("LocalizationMap", "X\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("LocalizationMap", "dist_B:", nullptr));
        label_dist_a->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
        label_4->setText(QCoreApplication::translate("LocalizationMap", "depth:", nullptr));
        label_6->setText(QCoreApplication::translate("LocalizationMap", "Y\357\274\232", nullptr));
        label_pos_x->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
        label_dist_b->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
        label_7->setText(QCoreApplication::translate("LocalizationMap", "Z\357\274\232", nullptr));
        label_depth->setText(QCoreApplication::translate("LocalizationMap", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LocalizationMap: public Ui_LocalizationMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCALIZATIONMAP_H

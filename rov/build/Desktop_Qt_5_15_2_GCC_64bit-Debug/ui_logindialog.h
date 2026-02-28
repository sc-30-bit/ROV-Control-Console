/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInDialog
{
public:
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QLineEdit *edit_name;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *edit_pw;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btn_clear;
    QPushButton *btn_log;

    void setupUi(QDialog *LogInDialog)
    {
        if (LogInDialog->objectName().isEmpty())
            LogInDialog->setObjectName(QString::fromUtf8("LogInDialog"));
        LogInDialog->resize(795, 564);
        widget_3 = new QWidget(LogInDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(259, 180, 271, 111));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        edit_name = new QLineEdit(widget_3);
        edit_name->setObjectName(QString::fromUtf8("edit_name"));
        edit_name->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0); \n"
""));

        gridLayout_2->addWidget(edit_name, 0, 1, 1, 1);

        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0); \n"
""));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0); \n"
""));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        edit_pw = new QLineEdit(widget_3);
        edit_pw->setObjectName(QString::fromUtf8("edit_pw"));
        edit_pw->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0); \n"
""));

        gridLayout_2->addWidget(edit_pw, 1, 1, 1, 1);

        layoutWidget = new QWidget(LogInDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 70, 804, 56));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setPointSize(18);
        font1.setItalic(true);
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        btn_clear = new QPushButton(LogInDialog);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setGeometry(QRect(410, 310, 101, 41));
        btn_log = new QPushButton(LogInDialog);
        btn_log->setObjectName(QString::fromUtf8("btn_log"));
        btn_log->setGeometry(QRect(270, 310, 101, 41));

        retranslateUi(LogInDialog);

        QMetaObject::connectSlotsByName(LogInDialog);
    } // setupUi

    void retranslateUi(QDialog *LogInDialog)
    {
        LogInDialog->setWindowTitle(QCoreApplication::translate("LogInDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LogInDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("LogInDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("LogInDialog", "\346\276\234\345\267\241\346\231\272\345\215\253\342\200\224\346\260\264\345\210\251\345\267\245\347\250\213\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\223\215\344\275\234\345\217\212\347\233\221\346\265\213\345\271\263\345\217\260", nullptr));
        btn_clear->setText(QCoreApplication::translate("LogInDialog", "\345\217\226\346\266\210", nullptr));
        btn_log->setText(QCoreApplication::translate("LogInDialog", "\347\231\273\351\231\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInDialog: public Ui_LogInDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

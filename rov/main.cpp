#include "widget.h"
#include "logindialog.h"
#include<QTextCursor>
#include <QApplication>
#include<_3d.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QTextCursor>("QTextCursor");
    qRegisterMetaType<std::string>("std::string");
    Widget w;
    _3D _3d(&w,w.server1);
    LogInDialog logIn;
    logIn.setWindowTitle("登录界面");
    logIn.show();
    QObject::connect(&logIn, SIGNAL(showmain()), &w, SLOT(receiveLogin()));// 登录信号与主界面连接
    return a.exec();
}

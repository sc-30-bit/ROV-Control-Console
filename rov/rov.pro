QT       += core gui network
QT       += 3dcore 3drender 3dinput 3dextras 3dlogic
QT       += quickwidgets
QT       += charts
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RovKalmanFilter.cpp \
    _3d.cpp \
    global.cpp \
    localizationmap.cpp \
    logindialog.cpp \
    main.cpp \
    mapview.cpp \
    quiwidget.cpp \
    rtsp.cpp \
    saver.cpp \
    stitcher.cpp \
    tcpserver.cpp \
    widget.cpp

HEADERS += \
    RovKalmanFilter.h \
    _3d.h \
    global.h \
    head.h \
    localizationmap.h \
    logindialog.h \
    mapview.h \
    quiwidget.h \
    rtsp.h \
    saver.h \
    stitcher.h \
    tcpserver.h \
    widget.h

FORMS += \
    localizationmap.ui \
    logindialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#pro文件里加：
INCLUDEPATH += $$PWD/quc/include
LIBS += $$PWD/quc/libquc.a
#或者libqucd.a都可以
LIBS += -L/usr/local/cuda/lib64 -lcudart -lcublas -lcusparse -lcurand -lcusolver


RESOURCES += \
    icons.qrc \
    main.qrc \
    qss.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lopencv_world
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lopencv_world
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
INCLUDEPATH += $$PWD/../../../../usr/local/include/opencv4

INCLUDEPATH += /usr/local/cuda/include

INCLUDEPATH += /usr/local/include
DEPENDPATH +=/usr/local/include
INCLUDEPATH +=/usr/local/include/eigen3

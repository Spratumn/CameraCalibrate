TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    calibrate.cpp \
    calibrator.cpp
INCLUDEPATH += D:\Open\OpenCV\OpenCVBuild\include
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_core340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_highgui340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_imgcodecs340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_imgproc340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_features2d340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_calib3d340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_calib3d340.dll
LIBS += D:\Open\OpenCV\OpenCVBuild\bin\libopencv_videoio340.dll

HEADERS += \
    calibrator.h

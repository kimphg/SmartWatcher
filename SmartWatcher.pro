QT += core
QT += core gui
QT += network

CONFIG += c++11

TARGET = SmartWatcher
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    utils.cpp \
    VideoHandler.cpp \
    FeatureAnalyzer.cpp \
    FlameDecider.cpp \
    FlameDetector.cpp \
    TargetExtractor.cpp \
    Config.cpp \
    videowork.cpp


INCLUDEPATH += "D:/openCV/OpenCV320/build/include"
LIBS += "D:/openCV/OpenCV320/build/x86/vc12/lib/*.lib"

#win32:RC_FILE += FlameDetection.rc

RC_FILE = FlameDetection.rc

HEADERS += \
    common.h \
    utils.h \
    VideoHandler.h \
    FeatureAnalyzer.h \
    FlameDecider.h \
    FlameDetector.h \
    TargetExtractor.h \
    Config.h \
    videowork.h

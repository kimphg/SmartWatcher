//
//  VideoHandler.h
//  FlameDetection
//
//  Created by liberize on 14-4-6.
//  Copyright (c) 2014年 liberize. All rights reserved.
//

#ifndef __FlameDetection__VideoHandler__
#define __FlameDetection__VideoHandler__

#include "common.h"
#include "utils.h"
#include "FlameDetector.h"
#include "Config.h"
#include "videowork.h"
//#include "videowork1.h"
//#include "QSound"
#include <QUdpSocket>
class VideoHandler : public QObject
{
    Q_OBJECT
private:
    static const int WAIT_INTERVAL = 30;
    static const int MAX_EXTRA_FRAME_COUNT = 80;

    VideoCapture mCapture;
    //FlameDetector mDetector;
    Mat mOrgFrame,  mFrame;
    bool mFromCam;
    bool mSaveVideo;
    bool mSaveKeyFrame;
    double mVideoFPS;
    string mSaveVideoFile;
    VideoWriter mWriter;
    
    bool saveFrame();

    QThread         *m_thread;
    //VideoWork       *m_worker;

    QThread         *m_thread2;
    //VideoWork       *m_worker2;

    QThread         *m_thread3;
    //VideoWork       *m_worker3;


    

public:
    static const int STATUS_FLAME_DETECTED = 0;
    static const int STATUS_OPEN_CAP_FAILED = 1;
    static const int STATUS_NO_FLAME_DETECTED = 2;

    int mVideoChannel;

//    VideoHandler(int device, bool saveKeyFrame = false, bool saveVideo = false);
//    VideoHandler(const string& file, bool saveKeyFrame = false);


    FlameDetector mDetector;
    VideoHandler(int device);
    VideoHandler(const string& file);
    
    const FlameDetector& getDetector() const { return mDetector; }
    double getVideoFPS() const { return mVideoFPS; }
    int handle();

    void ActivateAlarm();
    void DeactivateAlarm();    
private slots:
    void onTimer();
};

#endif /* defined(__FlameDetection__VideoHandler__) */

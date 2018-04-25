//
//  VideoHandler.cpp
//  FlameDetection
//
//  Created by liberize on 14-4-6.
//  Copyright (c) 2014ๅนด liberize. All rights reserved.
//

#include "VideoHandler.h"

extern CConfig mConfig;
VideoWork       *m_worker = NULL;
VideoWork       *m_worker2 = NULL;
VideoWork       *m_worker3 = NULL;
//QSound sound("alarm.wav");

VideoHandler::VideoHandler(int device)
: mCapture(device)
{
}

VideoHandler::VideoHandler(const string& file)
: mCapture(file)
{
}
void VideoHandler::ActivateAlarm()
{
    QUdpSocket      alarmSocket;
//    if (sound.isFinished())
//    sound.play();
    unsigned char message[5];
    message[0]=0xff;
    message[1]=0xff;
    message[2]=0xff;
    message[3]= mConfig._config.alarmNumber;
    message[4]=0xff;
    alarmSocket.writeDatagram((char*)&message[0],5, QHostAddress("192.168.100.255") , 8888);
}
void VideoHandler::DeactivateAlarm()
{
    QUdpSocket      alarmSocket;
    unsigned char message[5];
    message[0]= 0xff;
    message[1]= 0xff;
    message[2]= 0xff;
    message[3]= mConfig._config.alarmNumber;
    message[4]= 0x00;
    alarmSocket.writeDatagram((char*)&message[0],5, QHostAddress("192.168.100.255") , 8888);
}
int angle = 0;
void VideoHandler::onTimer()
{
//    if(angle <3)
//    {
//        m_worker->setTilt("192.168.100.100",angle);
//        m_worker->setTilt("192.168.100.101",angle);
//        m_worker->setTilt("192.168.100.102",angle);
//        m_worker->setTilt("192.168.100.100",angle);
//        m_worker->setTilt("192.168.100.101",angle);
//        m_worker->setTilt("192.168.100.102",angle);
//    }
//    else
//    {
       //std::system("reset.bat");
//    }
//    angle++;

}
int VideoHandler::handle()
{
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(900000);

    mVideoChannel = 0;
    //alarmSocket = new QUdpSocket();
    bool continueToDetect = true;
    int extraFrameCount = 0;    

    Rect mROI(mConfig._config.cropX, mConfig._config.cropY, mConfig._config.frmWidth - (2*mConfig._config.cropX),
                 mConfig._config.frmHeight - (2*mConfig._config.cropY));

    if (!mCapture.isOpened()) {
        return STATUS_OPEN_CAP_FAILED;
    }

    while (continueToDetect)
    {
        if (!mCapture.read(mOrgFrame))
        {
            cout << (mFromCam ? "Camera disconnected." : "Video file ended.") << endl;
            break;
        }
        //resize(mOrgFrame, mOrgFrame, cvSize(600,400));
        imshow("result", mOrgFrame);
        cout<<"newframe"<<endl;
        cv::waitKey(30);
        continue;
        resize(mOrgFrame, mOrgFrame, cvSize(mConfig._config.frmWidth, mConfig._config.frmHeight));
        imshow("original", mOrgFrame);

        if(true)cv::cvtColor(mOrgFrame,mFrame, CV_BGRA2GRAY);
        mFrame = mFrame(mROI);


        if (true)
        {

            if (mFlameDetector.detect(mFrame))
            {
                if(saveFrame())
                {
                    this->ActivateAlarm();
                    cout << "Flame detected." << endl;
                }
            }

            imshow("result", mOrgFrame);

        }
        else if (++extraFrameCount >= MAX_EXTRA_FRAME_COUNT)
        {
            return STATUS_FLAME_DETECTED;
        }
#ifdef TRAIN_MODE
        if (trainComplete) {
            cout << "Train complete." << endl;
            break;
        }
#endif
        cv::waitKey(30);
//        if (waitKey(WAIT_INTERVAL) == 27) {
//            cout << "User abort." << endl;
//            break;
//        }
    }

    return STATUS_NO_FLAME_DETECTED;
}

bool VideoHandler::saveFrame()
{   
    rectangle(mOrgFrame, mFlameDetector.m_Rect, Scalar(0, 255, 0));
//    rectangle(mOrgFrame, Rect(mConfig._config.cropX, mConfig._config.cropY, mConfig._config.frmWidth - (2*mConfig._config.cropX), mConfig._config.frmHeight
//                              - (2*mConfig._config.cropY)), Scalar(0, 0, 255));

//    if (mDetector.m_Rect.x < (mConfig._config.frmWidth*1/3))
//        return false;
//    if ((mDetector.m_Rect.x +mDetector.m_Rect.width )> (mConfig._config.frmWidth*2/3))
//        return false;
    if ((mFlameDetector.m_Rect.y + mFlameDetector.m_Rect.height) >= (mConfig._config.frmHeight - mConfig._config.cropY - 2))
        return false;

    // save detected frame to jpg
    string fileName;
    getCurTime(fileName);
    fileName += ".jpg";
    cout << "Saving key frame to '" << fileName << "'." << endl;
    //printf("times: %d\n",it->second.times);
    return imwrite("C:\\FlameDetector\\" +fileName, mOrgFrame);
}

#include <QCoreApplication>
#include <QSharedMemory>

#include "common.h"
#include "VideoHandler.h"
#include "FlameDetector.h"
#include "Config.h"

#ifdef TRAIN_MODE
bool trainComplete = false;
#endif

VideoHandler* videoHandler = NULL;
CConfig mConfig;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.processEvents();
    QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");
    if( !shared.create( 512, QSharedMemory::ReadWrite) )
    {
        exit(0);
    }
    VideoHandler handler(0);
    //VideoHandler handler("http://root:root@192.168.1.201/mjpg/video.mjpg");

    videoHandler = &handler;

    int ret = handler.handle();
    return a.exec();
}

#include <QCoreApplication>
#include <opencv.hpp>

#include <TOFLib/include/tofmanager.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    TOFManager* manager = new TOFManager();
    namedWindow("test");
    while(1){
        struct captureData info = manager->getDevice()->captureDevice->capture();
        imshow("test", info.phaseData);
//        sleepFunction(40);
        waitKey(30);
    }

//    VideoCapture cap(0);
//    Mat test;
//    if(cap.isOpened()){
//        while(1){
//            if(!cap.read(test))
//            {
//                cout<<"fail"<<endl;
//                return -1;
//            }
//            imshow("test",test);
//        }
//    }else{
//        return -1;
//    }

}

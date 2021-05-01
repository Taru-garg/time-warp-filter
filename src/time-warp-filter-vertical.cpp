#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace cv;
using namespace std;
int main(int, char**)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    
    cv::Mat processedPhoto(480, 640, CV_8UC3);
    int num_cols = 0;
    bool flag = false;
    while(true)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        if(num_cols < frame.cols)
        frame.col(num_cols).copyTo(processedPhoto.col(num_cols));
        num_cols++;
        // processedPhoto = frame;
        imshow("Live", frame);
        if(!flag) sleep(5), flag = true; // Some time to get into position
        imshow("Processed", processedPhoto);
        if (waitKey(1) >= 0)
            break;
    }
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

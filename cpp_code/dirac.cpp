#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudaobjdetect.hpp"

#include <iostream>
#include <csignal>
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );
void signalHandler( int signum ); 

/** Global variables */
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

//Open Serial Port
int USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

/** @function main */
int main( int argc, const char** argv )
{
    CommandLineParser parser(argc, argv,
                             "{help h||}"
                             "{face_cascade|haarcascade_frontalface_alt.xml|Path to face cascade.}"
                             "{eyes_cascade|haarcascade_eye_tree_eyeglasses.xml|Path to eyes cascade.}"
                             "{camera|1|Camera device number.}");

    parser.about( "\nThis program uses cv::CascadeClassifier class to detect Faces in a video stream and directs a car's AC unit to automatically aim at the face.\n"
                  "You can use Haar or LBP features.\n\n" );
    parser.printMessage();
// This code is all BULLSHIT!
    String face_cascade_name = parser.get<String>(0);
    String eyes_cascade_name = parser.get<String>(1);

    //-- 1. Load the cascades
    cout << "Loading face cascade...\n";
    cout << face_cascade_name;
    cout << "\n";

    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
//        return -1;
    };

    cout << "Loading eyes cascade...\n";
    cout << eyes_cascade_name;
    cout << "\n";
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        cout << "--(!)Error loading eyes cascade\n";
//        return -1;
    };

    int camera_device = parser.get<int>(2);
    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( camera_device );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
//        return -1;
    }

    struct termios tty;
    struct termios tty_old;
    memset (&tty, 0, sizeof tty);
    
    /* Error Handling */
    if ( tcgetattr ( USB, &tty ) != 0 ) {
       std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
    }
    
    /* Save old tty parameters */
    tty_old = tty;
    
    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)B115200);
    cfsetispeed (&tty, (speed_t)B115200);
    
    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;
    
    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    
    /* Make raw */
    cfmakeraw(&tty);
    
    /* Flush Port, then applies attributes */
    tcflush( USB, TCIFLUSH );
    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
       std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    }

    Mat frame;
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );

        if( waitKey(10) == 27 )
        {
            break; // escape
        }
    }
    signal(SIGTERM, signalHandler);
    close(USB);
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Draw rectangle on screen. If the face is outside of that rectangle, then the fan must be moved.
    // height, width
    int height = frame.rows;
    int width = frame.cols;
    int rectangle_size = 100;
    rectangle(frame,Point(width/2-rectangle_size,height/2-rectangle_size),Point(width/2+rectangle_size,height/2+rectangle_size),Scalar(0,0,255), 1, 8, 0);

    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 255, 0 ), 4 );

        Mat faceROI = frame_gray( faces[i] );

        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
        }

	//-- Check if the face is within the rectangle.
        bool width_ok = false;
        bool mv_left = false;
        bool mv_right = false;
        bool height_ok = false;
        bool mv_up = false;
        bool mv_down = false;
        int font = cv::FONT_HERSHEY_SIMPLEX;

        int upper_width_bound =  (width/2)+rectangle_size;
        int lower_width_bound =  (width/2)-rectangle_size;
        int upper_height_bound = (height/2)+rectangle_size;
        int lower_height_bound = (height/2)-rectangle_size;

        unsigned char cmd[1];

        if (center.x < upper_width_bound && center.x > lower_width_bound){
            width_ok = true;
            cv::putText(frame,"Face is within width of rect.",Point(10, height-50), font, 0.5,Scalar(255,255,255),2,cv::LINE_AA);
            //cmd[0] = 'h';
        }else if (center.x > upper_width_bound){
            mv_right = true;            
            cv::putText(frame,"MOVE RIGHT.",Point(10, height-50), font, 0.5,Scalar(0,0,255),2,cv::LINE_AA);
            //cmd[0] = 'r';
        }else if (center.x < lower_width_bound){
            mv_left = true;
            cv::putText(frame,"MOVE LEFT.",Point(10, height-50), font, 0.5,Scalar(0,0,255),2,cv::LINE_AA);
            //cmd[0] = 'l';
        }

        if (center.y < upper_height_bound && center.y > lower_height_bound){
            height_ok = true;
            cv::putText(frame,"Face is within height of rect.",Point(10, height-25), font, 0.5,Scalar(255,255,255),2,cv::LINE_AA);
            //cmd[0] = 'v';
    	}else if (center.y > upper_height_bound){
            mv_up = true;
            cv::putText(frame,"MOVE UP.",Point(10, height-25), font, 0.5,Scalar(0,0,255),2,cv::LINE_AA);
            //cmd[0] = 'u';
        }else if (center.y < lower_height_bound){
            mv_down = true;
            cv::putText(frame,"MOVE DOWN.",Point(10, height-25), font, 0.5,Scalar(0,0,255),2,cv::LINE_AA);
            //cmd[0] = 'd';
        }

        if (width_ok && height_ok){
            cv::putText(frame,"Face OK",Point(10, 25), font, 1,Scalar(0,255,0),2,cv::LINE_AA);
            cmd[0] = 'a';
        }
        if (mv_up){
            cmd[0] = 'b';
        }
        if (mv_right){
            cmd[0] = 'c';
        }
        if (mv_down){
            cmd[0] = 'd';
        }
        if (mv_left){
            cmd[0] = 'e';
        }
        if (mv_up && mv_right){
            cmd[0] = 'f';
        }
        if (mv_up && mv_left){
            cmd[0] = 'g';
        }
        if (mv_down && mv_right){
            cmd[0] = 'h';
        }
        if (mv_down && mv_left){
            cmd[0] = 'i';
        }

        write( USB, cmd, 2 );	
//        cout << "Wrote " << cmd[0] << " ";
    }

    //-- Show what you got
    imshow( "Capture - Face detection", frame );
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here  
   // terminate program  
   close(USB);
   exit(signum);  
}


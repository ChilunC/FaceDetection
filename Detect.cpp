//#include <Python.h>
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 //#include "ffmpeg-3.2.4/libavformat/http.h"


#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
//#include <iostream>
//#include <curlpp/cURLpp.hpp>
//#include <curlpp/Options.hpp>
#include <unistd.h>
#include <stdio.h>
#include "SendCommands.h"
#define BUFFSIZE 32

 using namespace std;
 using namespace cv;

 /** Function Headers */
 //void detectAndDisplay( Mat frame, int* count, int *sizeFace, string IPAddr, time_t *start );

 /** Global variables */
 //String face_cascade_name = "haarcascade_frontalface_alt.xml";
 //String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 //CascadeClassifier face_cascade;
 //CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 //RNG rng(12345);

/*
typedef struct shop
{
        int n;
	int x;
	int y;
	int size;
        char *obj;
}shop;
*/
/** @function detectAndDisplay */
Point detectAndDisplay( Mat frame, int *count, int *presCount, int *sizeFace, string IPAddr, string userName, string PSW, time_t *start, CascadeClassifier face_cascade )
{
  std::vector<Rect> faces;
  Mat frame_gray;
  Point FaceDet;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  
  //CommandIP("left", userName,PSW, IPAddr);
  
  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  if(faces.size()>0&&faces.size()<2&&difftime( time(0), *start)>3){
	  CommandIP("stop", "admin","123456", IPAddr);
	  if(faces.size()!=*sizeFace){
	  	*sizeFace = faces.size();
		*count = 0;
	  }else{
		(*count)++;
	  }

	  for( size_t i = 0; i < faces.size(); i++ )
	  {
	    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
	    FaceDet = center;
	    cout << endl << faces.size() << endl;
	    //*facewidth = faces[i].width;
	    //count = 0;
/*
	    if(*count>10){
		    if(center.x>800){
			CommandIP("right", "admin", "123456", IPAddr);
		    }else if(center.x<400){
			CommandIP("left", "admin","123456", IPAddr);	    
		    }else{
			CommandIP("stop", "admin","123456", IPAddr);
		    }
		    *start = time(0);
		//*count = 0;
	    }//else{
		//*count++;
	    //}
*/


	    if(*count>10){
		    if(center.x>800){
			CommandIP("right", userName, PSW, IPAddr);
		    }else if(center.x<400){
			CommandIP("left", userName,PSW, IPAddr);	    
		    }else{
			CommandIP("stop", userName,PSW, IPAddr);
		    }
		    *start = time(0);
		//*count = 0;
	    }//else{
		//*count++;
	    //}


	    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

	    Mat faceROI = frame_gray( faces[i] );
	    std::vector<Rect> eyes;

	    //-- In each face, detect eyes
	    //eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	    //for( size_t j = 0; j < eyes.size(); j++ )
	     //{
	       //Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
	       //int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
	       //circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
	     //}
		//return center;
	}
  }else if(difftime( time(0), *start)>10){
	cout << endl << "sizeface" << endl;
	 //cout << endl << *sizeFace << endl;
	 //cout << endl << faces.size() << endl;
	if(faces.size()!=*sizeFace){
	  	*sizeFace = faces.size();
		*count = 0;
	  }else{
		(*count)++;
	  }
	
	//cout << endl << "sizeface" << endl;
	 //cout << endl << (*count)++ << endl;
	 //cout << endl << *count << endl;
	if(*count>3){
		
		
		switch((*presCount)){
			case 1:
				PresetIP("1", userName,PSW, IPAddr);
				*presCount = 2;
				break;
			case 2:
				PresetIP("2", userName,PSW, IPAddr);
				*presCount = 3;
				break;
			case 3:
				PresetIP("3", userName,PSW, IPAddr);
				*presCount = 4;
				break;
			case 4:
				PresetIP("4", userName,PSW, IPAddr);
				*presCount = 5;
				break;
			case 5:
				PresetIP("5", userName,PSW, IPAddr);
				*presCount = 6;
				break;
			case 6:
				PresetIP("6", userName,PSW, IPAddr);
				*presCount = 7;
				break;
			case 7:
				PresetIP("7", userName,PSW, IPAddr);
				*presCount = 8;
				break;
			case 8:
				PresetIP("8", userName,PSW, IPAddr);
				*presCount = 9;
				break;
			case 9:
				CommandIP("home", userName,PSW, IPAddr);
				*presCount = 1;
				(*count) = 0;
				break;
		}
		*start = time(0);
	} //else{
		//CommandIP("stop", "admin","123456", IPAddr);
		//*count++;
	//}

  }
  
  
  //-- Show what you got
  imshow( window_name, frame );
  //if(center){
  return FaceDet;
  //}
 }

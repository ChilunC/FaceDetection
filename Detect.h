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
 String face_cascade_name = "haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 //string window_name = "Capture - Face detection";
 RNG rng(12345);

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

Point detectAndDisplay( Mat frame, int *count, int *presCount, int *sizeFace, string IPAddr, string userName, string PSW, time_t *start, CascadeClassifier face_cascade);
/*
class TwoValues
{
public:
    TwoValues(void): iValue1(0), iValue2(0) {}
    TwoValues(int iValue1, int iValue2): iValue1(iValue1_), iValue2(iValue2_) {}

    int Addition(void) const {if (!this) return 0; return iValue1 + iValue2;}

public:
    int iValue1;
    int iValue2;
};
*/

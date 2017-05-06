 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 //#include "ffmpeg-3.2.4/libavformat/http.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
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
#include <stdlib.h>
#include "SendCommands.h"
#include "Detect.h"
#define BUFFSIZE 32
#define MAX_LEN 10000
#define FILEPATH "/tmp/mmapped.bin"
#define NUMINTS  (1000)
#define FILESIZE (NUMINTS * sizeof(int))

 using namespace std;
 using namespace cv;

 /** Function Headers */
// void detectAndDisplay( Mat frame, int* count, int *sizeFace, string IPAddr, time_t *start );

 /** Global variables */
 //String face_cascade_name = "haarcascade_frontalface_alt.xml";
 //String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 //CascadeClassifier face_cascade;
 //CascadeClassifier eyes_cascade;
 //string window_name = "Capture - Face detection";
 //RNG rng(12345);



int full=0,empty=1;
pthread_mutex_t *mutex,mutex1;


typedef struct shop
{
	int n;
	int x;
	int y;
	int size;
	char *obj;
}shop;

 /** @function main */
 int main( int argc, const char** argv )
 {
   //CvCapture* capture;
   //VideoCapture vcap;
   Mat frame;

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

   //-- 2. Read the video stream
   VideoCapture capture;
   const std::string IPAddr = "192.168.1.";
   const std::string videoStreamAddress = "rtsp://" + IPAddr + ":554/live/ch0.sdp";
   const std::string videoStreamAddress2 = "http://admin:123456@" + IPAddr + ":8081/cgi/mjpg/mjpg.cgi?.mjpg";
   const std::string videoStreamAddress3 = "rtsp://admin:123456@" + IPAddr + "/live/ch0";
   const std::string CommandStringStop = "http://192.168.2.7/hy-cgi/ptz.cgi?cmd=ptzctrl&act=stop";
   Point center;
   stringstream ss;
   string strss;
   //memory mapping
    int fdata, facedata3, result;
    unsigned int xdata, ydata, presdata, flagdata;
    char *data;
    struct stat sbuf;
    pid_t pid;
    shop *market,market1;
    //shop *facedata,facedata1;
    unsigned int *facedata, facedata1;
    market=&market1;
    //facedata=&facedata1;
    mutex=&mutex1;

    if ((mutex = (pthread_mutex_t *)mmap (NULL, sizeof(pthread_mutex_t),(PROT_READ | PROT_WRITE),(MAP_SHARED | MAP_ANON),-1, 0)) == MAP_FAILED){
	printf("Error mapping shared memory 'mutex': %s\n",strerror(errno));
	return errno;
    }

    if ((market = (shop *)mmap(NULL,sizeof(shop),(PROT_READ | PROT_WRITE),(MAP_SHARED | MAP_ANON),-1,0)) == MAP_FAILED){
    	printf("Error mapping shared memory 'market': %s\n",strerror(errno));
	return errno;
    }

    market->n=0;
    market->x = 0;
    market->y = 0;
    market->size = 0;

    
    //market->obj=buffer;
    //pid = fork();


    struct region {        /* Defines "structure" of shared memory */
	    int len;
	    char buf[MAX_LEN];
	};
    struct region *rptr;
    //int fd;
/*
    if (argc != 2) {
	fprintf(stderr, "usage: mmapdemo offset\n");
	exit(1);
    }
*/

    /* shared memory file descriptor */
    int shm_fd, n;
    /* pointer to shared memory obect */
    double *ptr;
    //const char *name;
	//cout << endl << "Weeeeellllll!!!!!" << endl;
    /* create the shared memory object */
    shm_fd = shm_open("data.c", O_RDWR | O_CREAT | O_TRUNC, 0666);
    //cout << endl << "Weeeeellllll  How?!!!!!" << endl;
    /* configure the size of the shared memory object */
    //n = ftruncate(shm_fd, MAX_LEN);
    /*
    size_t len = 4096;
	if (ftruncate(shm_fd, len) == -1) {
	    perror("ftruncate");
	    return 1;
	}
*/
    result = lseek(shm_fd, FILESIZE-1, SEEK_SET);
    if (result == -1) {
	close(shm_fd);
	perror("Error calling lseek() to 'stretch' the file");
	exit(EXIT_FAILURE);
    }
    result = write(shm_fd, "", 1);
    if (result != 1) {
	close(shm_fd);
	perror("Error writing last byte of the file");
	exit(EXIT_FAILURE);
    }




    if ((facedata = (unsigned int *)mmap(NULL,sizeof(shop),(PROT_READ | PROT_WRITE),(MAP_SHARED | MAP_ANON), shm_fd ,0)) == MAP_FAILED){
    	printf("Error mapping shared memory 'market': %s\n",strerror(errno));
	return errno;
    }
    /* memory map the shared memory object */
	//ptr = static_cast<double*>(mmap(0, MAX_LEN, PROT_WRITE, MAP_SHARED, shm_fd, 0));
	/* write to the shared memory object */
    /*
    if ((fdata = open("data.c", O_RDWR)) == -1) {
	perror("open");
	exit(1);
    }

    if (stat("data.c", &sbuf) == -1) {
	perror("stat");
	exit(1);
    }
    */
    //facedata->n=0;
    //facedata->x = 0;
    //facedata->y = 0;
    //facedata->size = 0;
    facedata[0] = 1;
    facedata[1] = 1;
    facedata[2] = 2;
    facedata[3] = 3;
    //offset = atoi(argv[1]);
    xdata = 1;
    ydata = 2;
    presdata = 3;
    flagdata = 4;
    facedata3 = 5;
/*
    if (offset < 0 || offset > sbuf.st_size-1) {
	fprintf(stderr, "mmapdemo: offset must be in the range 0-%d\n", \
	                                                      sbuf.st_size-1);
	exit(1);
    }
    */
    //data = static_cast<int*>(mmap((caddr_t)0, sbuf.st_size, O_RDWR, MAP_SHARED, fdata, 0)); // \
	                                                   //== (caddr_t)(-1)) {
/*
    if (data == (caddr_t)(-1)) {
	perror("mmap");
	exit(1);
    }
*/
    
   //end memory mapping





   time_t start = time(0);
   //PresetIP("1", "admin","123456", IPAddr);
   //CommandIP("hscan", "admin","123456", "192.168.2.7");
   //capture = cvCaptureFromCAM( -1 );
   //capture.open("http://192.168.226.101:8080/video?x.mjpeg");
   capture.open(videoStreamAddress3);
   if( capture.isOpened() )
   {
	     
		//curlpp::Cleanup myCleanup;
		//std::ostringstream os;
		//os << curlpp::options::Url(std::string(CommandStringStop));

		//string asAskedInQuestion = os.str(); 

	     int count = 0;
	     int presCount = 1;
	     int sizeFace = 0;
             
	     while( true )
	     {
	   //frame = cvQueryFrame( capture );

	    capture.read(frame);
	    //cout << endl << frame.size() << endl;
	    //VideoCapture cap; //
	    //if(count<3){
	    	
	   //-- 3. Apply the classifier to the frame
	       if( !frame.empty() )
	       { center = detectAndDisplay( frame, &count, &presCount, &sizeFace, IPAddr,"admin","123456", &start , face_cascade); }
	       else
	       { printf(" --(!) No captured frame -- Break!"); break; }
		//itoa(center.x, data[xdata],10);
		//ss << center.x;
		//cout << ss << endl;
		//strss = ss.str();
		//cout << strss.length;
		//for(int i=1;i<strss.length();i++) {
		 // cout << strss.at(i);
		  //data[xdata-1+i] = strss.at(i); //System.out.println(a.charAt(i));
		//}
		//int centerx = center.x;
		//sprintf(ptr, "%f", center.x);
		//data[xdata*20] = center.x;
		//*ptr = center.x;
		//facedata->x = center.x;
		//facedata->y = center.y;
		//facedata->size = sizeFace;
/*
		if(facedata[0]){
			facedata[0] = 0;
		        facedata[1] = center.x;
			facedata[2] = center.y;
			facedata[3] = sizeFace;
			facedata[0] = 1;
			//printf("%d", facedata[1]);
			printf("%d /n", facedata[0]);
		}
		*/
		//data[ydata] = center.y;
		//data[presdata] = presCount;
		//data[flagdata] = 1;
		//data[facedata] = sizeFace;

		//cout << endl << data[xdata] << endl;
		//cout << endl << center.x << endl;

		//getchar();
		//cout << endl << data[ydata] << endl;
		//cout << endl << data[presdata] << endl;
		//cout << endl << data[flagdata] << endl;
		//cout << endl << data[facedata] << endl;
	       int c = waitKey(10);
	       if( (char)c == 'c' ) { break; }
	      
	    //}else{
		//count = 0;
	    //}
	    //count = count++;
		//usleep(100);
    	    }
   }
   return 0;
 }

/** @function detectAndDisplay */
/*
void detectAndDisplay( Mat frame, int *count, int *sizeFace, string IPAddr, time_t *start )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

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
	    cout << endl << faces.size() << endl;
	    //count = 0;
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
	}
  }else if(difftime( time(0), *start)>10){
	//cout << endl << "sizeface" << endl;
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
		
		
		switch((*count) - 3){
			case 1:
				PresetIP("1", "admin","123456", IPAddr);
				break;
			case 2:
				PresetIP("2", "admin","123456", IPAddr);
				break;
			case 3:
				PresetIP("3", "admin","123456", IPAddr);
				break;
			case 4:
				PresetIP("4", "admin","123456", IPAddr);
				break;
			case 5:
				PresetIP("5", "admin","123456", IPAddr);
				break;
			case 6:
				PresetIP("6", "admin","123456", IPAddr);
				break;
			case 7:
				PresetIP("7", "admin","123456", IPAddr);
				break;
			case 8:
				PresetIP("8", "admin","123456", IPAddr);
				break;
			case 9:
				CommandIP("home", "admin","123456", IPAddr);
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
 }
*/

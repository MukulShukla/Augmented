#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cv.h>
#include <highgui.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <ctime>

using namespace std;

struct cons{
    int car;
    int cdr;
};  

int sqr (int x) {return x*x;}
cons prev;

#include "crosshair.cpp"
#include "recognize2.cpp"
#include "reset.cpp"
#include "keypress.cpp"

//find center of image, return the coordinate
cons findcenter (IplImage* img) {
	cons gest; gest.car = 0; gest.cdr = 0;
	int x, num=0, i;
	uchar * ptr;
	long int x_tot=0, y_tot=0;
	for( int y=0; y<img->height; y++ ) {
		ptr = (uchar*) (img->imageData + y * img->widthStep);
		for(x=0; x<(img->width); x++) {
			if (ptr[3*x]!=127 || ptr[3*x+1]!=127 || ptr[3*x+2]!=127) {
				x_tot+=x;
				y_tot+=y;
				num++;
			}
		}
	}
	
	if (num>20) {
		gest.car = x_tot/num ;
		gest.cdr = y_tot/num ;
	}
	return gest;
}

//write on image at cons coordinates
void writepoint(cons gest , IplImage* res) {
	int x, num=0, i; uchar * ptr;
	char* pt;
	float slope; 
	pt=res->imageData + (gest.cdr)*res->widthStep + gest.car;
	*((uchar*)pt)=255;
	if (prev.car!=0 || prev.cdr!=0) {
		slope=((float)(gest.car-prev.car))/(gest.cdr-prev.cdr);
		for (i=min(gest.cdr-prev.cdr,0);
					i<max(gest.cdr-prev.cdr,0);
					i++)
		{
			ptr=(uchar*)(pt-(int)(i*(res->widthStep)+i*slope));
			*ptr=255;
		}
	}
	prev.car = gest.car ;
	prev.cdr = gest.cdr ;
}

//difference between two images
void differ( IplImage* imgmid, IplImage* imgnew) {
	int k, x;
	float total=0, num=1.0/(3*(imgmid->width)*(imgmid->height)), sqs=0;
	for( int y=0; y<imgmid->height; y++ ) {
		uchar* ptrmid = (uchar*) (
		imgmid->imageData + y * imgmid->widthStep
		);
		uchar* ptrnew = (uchar*) (
		imgnew->imageData + y * imgnew->widthStep
		);
		for(x=0; x<3*(imgmid->width); x++ ) {
			k=ptrnew[x]-ptrmid[x];
			if (k > 30) ptrmid[x]=255;
			else if (k < -30) ptrmid[x]=0;
			else ptrmid[x]=127;
		}
	}
}

main( int argc, char* argv[] ) {
	bool a=false;
	char g='\0',l, str1[32]="";
	cons gest[256], curr_gest;
	int i=0,N=256, non=0, waittime,time=0;
	float ram;
	//openeing file for standard wait time	
	FILE * fp = fopen ("waittime.bin", "rb+");
	if (fp == NULL){
		waittime = 15; ram =3;}
	else{
	fread (&waittime, 4, 1, fp);
		fread (&ram, 4, 1,fp);
		fclose (fp);
		if(waittime<10 || waittime>60) waittime = 15;
		if(ram<0.10 || ram >32) ram = 3;
	}
	
	//loading gestures
	fp = fopen ("gestures.bin", "rb+");
	if (fp == NULL){
		cout<<"Gestures not found. Standard gestures taken.\n";}
	else{
		for(i=0; i<32; i++){
			fread(&l,1,1,fp);
			str1[i] = l;
		}
		fclose (fp);
		}
	

	//capturing frames
	CvCapture* capture = cvCreateCameraCapture( 0 );

	IplImage *mid = cvQueryFrame(capture);
	IplImage *frames = cvQueryFrame(capture);

	IplImage* res = cvCreateImage(
		cvGetSize(frames),
		IPL_DEPTH_8U,
		1
	);
	
	//cvNamedWindow( "Recording ...press ESC to stop !", CV_WINDOW_AUTOSIZE );
	
	//waittime = 15; ram=3;
	i=0; non=0;
	while (true) {
		//event loop
		mid = cvCloneImage(frames);
		frames = cvQueryFrame( capture );
		if (!frames) break;
		
		differ(mid,frames);
		crosshair(mid);
		curr_gest=findcenter(mid);	
		//show image to user, capture consecutive frames and evaluate diff
		
		cvShowImage( "Recording ...press ESC to stop !",frames );
		char c = cvWaitKey(33);
		// break on Esc, increase time
	
		if( c == 27 ) exit(0);
		time++;
		if(time > (ram*30*waittime)/3){
			if(!a) return 1;
		}	
		
		//break if gesture too long
		if (a) {
			if (i > 256) {
				cout<<"Too long gesture. unable to process.\n";
				a = false; non=0; i=0;
				cout<<"Try Again\n\n";
			}
			else {
				
				if (curr_gest.car!=0 || curr_gest.cdr!=0) {
					gest[i-non]=curr_gest;
					writepoint (curr_gest, res);
				}
				else non++;
				i++; 
				if (non >= waittime) {
					N = i-non;
					cout<<"N = "<<N<<"\n";
					if (N > waittime/2 && N < 64) {
						cout<<"Evaluating gesture... \n";
						
						scaleimg (gest, N);
						//evaluate gesture for similarity
						g = evalgest(gest, N , str1 , 500000);
						cvSaveImage("gesture1.jpg",res); 
						fakepress(g);
					}
					a=false; non=0; i=0;
					resetimg(res);
				}
			}
		}
		
		else if (curr_gest.car!=0 || curr_gest.cdr!=0) {
			a=true;cout<<"Starting gesture...\n";}
		
		cvReleaseImage (&mid);
		
	}
	//release loop
	cvReleaseCapture ( &capture );
	cvDestroyWindow ( "Recording ...press ESC to stop !");

	return 0;
}


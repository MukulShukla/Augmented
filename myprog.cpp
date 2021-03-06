#include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;

 /** Function Headers */
 void detectAndDisplay( Mat frame );

 /** Global variables */
 String face_cascade_name = "haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Anon!";
 string filename="mask2.png";
 RNG rng(12345);

 /** @function main */
 int main( int argc, const char** argv )
 {
   CvCapture* capture;
   Mat frame;

   //-- 1. Load the cascades that is the XML files generated which have detection data
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

   //-- 2. Read the video stream -- Start Capture from webcam
   capture = cvCaptureFromCAM( -1 );
   if( capture )
   {
     while( true )
     {
	//Get each frame out from the stream
   frame = cvQueryFrame( capture );
	
	//-- 3. Apply the classifier to the frame
       if( !frame.empty() )
       { detectAndDisplay( frame ); }
       else
       { printf(" --(!) No captured frame -- Break!"); break; }

       int c = waitKey(10);
       if( c == 27 ) { break; }
	else if (c == 97) {filename="sun.png";}
	else if (c == 98) {filename="mask1.png";}
	else if (c == 99){filename="mask2.png";}
   	
      }
   }
   return 0;
 }

void drawImage(IplImage* target, IplImage* source, int x, int y) {

    for (int ix=0; ix<source->width; ix++) {
        for (int iy=0; iy<source->height; iy++) {
            int r = cvGet2D(source, iy, ix).val[2];
            int g = cvGet2D(source, iy, ix).val[1];
            int b = cvGet2D(source, iy, ix).val[0];
            CvScalar bgr = cvScalar(b, g, r);
            cvSet2D(target, iy+y, ix+x, bgr);
        }
    }
}

void cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D)
{
 int x,y,i;

  for(x=0;x < overlay->width -10;x++)     
//replace '-10' by whatever x position you want your overlay image to begin. 
//say '-varX'
    {
        if(x+location.x>=src->width) continue;
        for(y=0;y < overlay->height -10;y++)  
//replace '-10' by whatever y position you want your overlay image to begin.
//say '-varY'
        {
            if(y+location.y>=src->height) continue;
            CvScalar source = cvGet2D(src, y+location.y, x+location.x);
            CvScalar over = cvGet2D(overlay, y, x);
            CvScalar merged;
            for(i=0;i<4;i++)
            merged.val[i] = (S.val[i]*source.val[i]+D.val[i]*over.val[i]);
            cvSet2D(src, y+location.y, x+location.x, merged);
        }
    }
}


void overlayImage(const Mat &background, const Mat &foreground, Mat &output, Point location)
{
  background.copyTo(output);


  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = std::max(location.y , 0); y < background.rows; ++y)
  {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows)
      break;

    // start at the column indicated by location, 

    // or at column 0 if location.x is negative.
    for(int x = std::max(location.x, 0); x < background.cols; ++x)
    {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols)
        break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity =
        ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

        / 255.;


      // and now combine the background and foreground pixel, using the opacity, 

      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c)
      {
        unsigned char foregroundPx =
          foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx =
          background.data[y * background.step + x * background.channels() + c];
        output.data[y*output.step + output.channels()*x + c] =
          backgroundPx * (1.-opacity) + foregroundPx * opacity;
      }
    }
  }
}





/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  //receives a floating point matrix containing the frame data
  std::vector<Rect> faces;
  Mat frame_gray;

  //Converts frame to gray scale for better detection and reduced noise
  cvtColor( frame, frame_gray, CV_BGR2GRAY ); 
  //It equalizes the image histogram which is a graphical representation of the intensity distribution of an image
  // It is a method that improves the contrast in an image, in order to stretch out the intensity range.
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces -- faces array contains the detected faces
  //Detects objects of different sizes in the input image. The detected objects are returned as a list of rectangles.
  // Pre-writen function
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    // iterating through the face
    // find center of the face
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    
//ellipse for face
//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

	//loading the image to render
	Mat image;
	image=imread(filename, -1);
	//Initializing a size object of face size
	Size size(faces[i].width, faces[i].height);
	//setting base point for resize	
	Point base(center.x-((faces[i].width)/2),center.y-((faces[i].width)/2));
	//image resized and stored to image again	
	resize(image, image, size);
//Try 1
//	IplImage ipl=image;
//	IplImage origi=frame;
//	cvOverlayImage(&origi, &ipl, center, cvScalar(0.5,0.5,0.5,0.5), cvScalar(0.5,0.5,0.5,0.5)); 


/*
Try2
    cv::resize(image,image,Size(70,70));  
    for(;;){
        Mat newFrame=frame.clone();
        int cx = (newFrame.cols - 70) / 2;
        if (!image.empty()) {
            // Get a BGR version of the face, since the output is BGR color
            Mat srcBGR = Mat(image.size(), CV_8UC3);


		// cvtColor(image, srcBGR, CV_GRAY2BGR);
if(image.empty())
    break;
else if(image.channels()>1)
    cvtColor(image, srcBGR, CV_BGR2GRAY);
else srcBGR = image;            



	// Get the destination ROI (and make sure it is within the image)
            Rect dstRC = Rect(cx, newFrame.rows/2, 70, 70);
            Mat dstROI = newFrame(dstRC);
            // Copy the pixels from src to dst.
            srcBGR.copyTo(dstROI);
        }
}

*/


//try3
//IplImage source=image;
//IplImage target=frame;
//drawImage(&target, &source, center.x, center.y);


//try4
//IplImage source=image;
//cvSetImageROI(&source, cvRect(center.x, center.y, 100, 100));
//cvAddWeighted(&frame, 0.5 , &frame, 0.5, 0, &frame);


//try5
//cvtColor( frame, frame, CV_BGR2BGRA );
//overlay.copyTo( frame.colRange(0,400).rowRange(0,400));

//try6

//Image is displayed after overlaying one image on another
overlayImage(frame, image, frame, base);

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       	// eyes may be displayed here
	//circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     

}
  }
  //-- Show what you got
  imshow( window_name, frame );
 }


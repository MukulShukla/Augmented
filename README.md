    This file is part of .SmartCam (made as a part of Senior Project by student at MSRIT)

    SmartCam is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SmartCam is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
    
--> We have used Haar Cascades(http://docs.opencv.org/trunk/doc/py_tutorials/py_objdetect/py_face_detection/py_face_detection.html) to detect face from live webcam feed in C++.

--> We pass the resulting coordinates to our rendering module, which presently is able to render transparent 2-D images with appropriate size at the desired location.

Our next step is to use a 3D image, add more features apart from face in detection module, improve rendering speed and if possible switch over back to Kinect. 

If OpenCV is setup successfully you can use

sudo g++ myprog.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

to compile.

Gesture Recognition:

Dependencies:
gcc, opencv-doc, libcv2.1, linhighgui2.1, libcvaux2.1, libcv-dev, libcvaux-dev, linhighgui-dev, libx11-dev, and libxtst-dev

To Run:
g++ install.cpp -o install
./install
./initialize
./gesture

Haar Training Procedure

--> Put your positive images in the ./positive_images folder and create a list of them:

find ./positive_images -iname "*.jpg" > positives.txt

--> Put the negative images in the ./negative_images folder and create a list of them:

find ./negative_images -iname "*.jpg" > negatives.txt

--> Create positive samples with the bin/createsamples.pl script and save them to the ./samples folder:

perl bin/createsamples.pl positives.txt negatives.txt samples 1500\
  "opencv_createsamples -bgcolor 0 -bgthresh 0 -maxxangle 1.1\
  -maxyangle 1.1 maxzangle 0.5 -maxidev 40 -w 80 -h 40"

--> Compile the mergevec.cpp file in the ./src directory:

cp src/mergevec.cpp ~/opencv-2.4.9/apps/haartraining
cd ~/opencv-2.4.9/apps/haartraining
g++ `pkg-config --libs --cflags opencv | sed 's/libtbb\.dylib/tbb/'`\
  -I. -o mergevec mergevec.cpp\
  cvboost.cpp cvcommon.cpp cvsamples.cpp cvhaarclassifier.cpp\
  cvhaartraining.cpp\
  -lopencv_core -lopencv_calib3d -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

--> Use the compiled executable mergevec to merge the samples in ./samples into one file:

find ./samples -name '*.vec' > samples.txt
./mergevec samples.txt samples.vec

--> Start training the classifier with opencv_traincascade, which comes with OpenCV, and save the results to ./classifier:

opencv_traincascade -data classifier -vec samples.vec -bg negatives.txt\
  -numStages 20 -minHitRate 0.999 -maxFalseAlarmRate 0.5 -numPos 1000\
  -numNeg 600 -w 80 -h 40 -mode ALL -precalcValBufSize 1024\
  -precalcIdxBufSize 1024

Wait until the process is finished (which takes a long time — a couple of days probably, depending on the computer you have and how big your images are).


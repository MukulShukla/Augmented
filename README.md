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


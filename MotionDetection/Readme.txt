    This file is part of SmartCam (made as a part of Senior Project by student at MSRIT)

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
    
How detect motion with images?

Suppose we have 2 images, the images are a linear subsequence with some delay c between them. If we would compare every pixel of the 2 images, and we notice they’re all the same, we can conclude the 2 images are identical. But if they don’t, we could say, something happened during the delay time c. Someone could place an object in front of the camera, or walked by. And yes, this is the idea we will use for the motion detection.

The method which I described, is also called “Differential Images”. It’s the result of substracting 2 images. There are several different combination of substracting images. We will use the method of Collins et al. as this method erases the phenomenon "ghosting".

Collins et al. uses 3 images, which are called prev, current and next. It first substract the images prev and next and then the images current and next. After this we will do a logical AND operations between the results of both and threshold the final result to make it accurate for large changements only.

Next we will place a window on the image (the thresholded result) and we will look for changes, this means for pixels with values equal to 255 (this will indicate motion, changed pixels). When motion is detected min and max values are evaluated. These min and max are used to compute the
bounding rectangle, which will contain all changed pixels.

If motion is detected we will draw the bounding rectangle on the resulting image. A cropped image is also saved: these sub images can be used for object detection eg. with a cascade classifier.


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
    
Implementing the code is very simple. However sometimes executable files do not run
correctly, in which case the code has to be compiled before running. The packages required for compiling the code are gcc, opencv-doc, libcv2.1, linhighgui2.1, libcvaux2.1, libcv-dev, libcvaux-dev, linhighgui-dev, libx11-dev, and libxtst-dev. These packages can be collectively
installed from the Synaptic Package Manager or using individual system commands:

$ sudo apt-get install [package-name]

After installing all the packages compile the file - install.cpp using the command:

$g++ install.cpp -o install

Running the file install inturn compiles all the other required files, provided the required libraries are installed correctly and up-to-date.

$ ./install


Altenetively, you can compile all the files individually using the command:
$ g++ `pkg-config opencv --cflags` [filename].cpp -o [filename]
`pkg-config opencv --libs` -lX11 -lXtst
The files to be compiled are : initialize.cpp, main.cpp, gesture.cpp, addgesture.cpp, checkgesture.cpp and delgesture.cpp.
****  ---------------------------- ***

Before beginning run the file initialize:
$ ./initialize

The main code is run using the file gesture :
$ ./gesture


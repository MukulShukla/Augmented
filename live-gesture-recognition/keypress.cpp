/*#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <ctime>
#include <iostream>

using namespace std;
*/
void wait (unsigned int t) {
	unsigned int t0=time(0);
	while (time(0)<t0+t);
}

void fakepress(char g) {
	int i; bool s=false;
	FILE* fp; char c;
	Display *display;
	unsigned int keycode1;
	unsigned int keycode2;
	display = XOpenDisplay(NULL);
	
	//XTestFakeKeyEvent(display, 65, True, 0);
	//XTestFakeKeyEvent(display, 65, False, 0);

	
	//cout<<"Final = '"<<g<<"'.\n\n";

		char com[50] = "gnome-terminal -e ",fname[10]="xcmmd.bin";
		fname[0] = g;
		fp = fopen(fname,"rb+");
		for(i=18; i<50; i++){
			fread(&c,1,1,fp);
			com[i] = c;
		}
		fclose(fp);
				
		system(com);
	
	
	XFlush(display);
	return;
}

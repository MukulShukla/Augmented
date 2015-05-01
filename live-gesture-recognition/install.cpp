#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(){

	system("g++ `pkg-config opencv --cflags` initialize.cpp -g -o initialize `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` addgesture.cpp -g -o addgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` checkgesture.cpp -g -o checkgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` delgesture.cpp -g -o delgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` main.cpp -g -o main `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` gesture.cpp -g -o gesture `pkg-config opencv --libs` -lX11 -lXtst");

return 0;
}

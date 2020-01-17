#include <iostream>
#include <fstream>

using namespace std;

int main() {
	//Initialize stream
	ofstream stream;

	//Populate GAMEOBJS.h
	stream.open("GAMEOBJS.h");
	//Use Boost Filesystem to loop through the header files and add a line for each header.

}
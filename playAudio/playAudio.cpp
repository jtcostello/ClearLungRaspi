#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	// create wav file
	system("sox -t raw -b 16 -e signed-integer -r 441000 -B -c2 mic1.txt record1.wav");
	// NEED TO TEST THIS TO MAKE SURE CORRECT COMMAND

	// play wav over speakers
	system("aplay record1.wav");


	return 0;
}



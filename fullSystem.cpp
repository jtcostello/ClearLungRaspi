#include <iostream>
#include <fstream>
#include <wiringPi.h>

// LCD - TESTING
#include "newLcdCode/CLP_lcd.h"
#include <lcd.h>
#include <vector>

#include <string>
#include <sstream>

// i2C
#include "pi2c.h";
#include <cassert>;
#include <unistd.h>;
#include <iostream>;
#include "stdlib.h";

using namespace std;

/* Files needed for compilation:
 - fullSystem.cpp
 - lcd.cpp
 - plotGraph.cpp
 - kiss_fft.h
 -  
 - "option -lwiringPi"
 - "option -lwiringPiDev"

 Compile with: g++ fullSystem.cpp pi2c.cpp -lwiringPi -lwiringPiDev -o fullSystem
*/


////////// Globals ////////////
int recordTimeSec = 1;

const int startButtonPin = 27;
const int upButtonPin = 28;
const int downButtonPin = 29;

const int teensyAddress = 7;
const int sentBytes = 128;

int lcd;



// function declarations
void waitForStart();
void updateWaitingScreen();
void setupPins();
string int2str(int num);



int main() {
	/////////////////////////////////// ON BOOT ///////////////////////////////////////
	// setup GPIO inputs and LCD
	wiringPiSetup();
	setupPins();
    lcd = setupLCD();

	// Display title text
	lcdClear(lcd);
	lcdPrint(lcd,"","Clear Lung Project","","");
	delay(2000);

    // Open output files for each mic
	ofstream mic1;
	mic1.open("mic1.txt");
	ofstream mic2;
	mic2.open("mic2.txt");

	// Display option to select recording time and wait for start button press 
	waitForStart();



	/////////////////////////////////// ON START ///////////////////////////////////////
	cout << "Recording now" << endl;
	lcdClear(lcd);
	lcdPrint(lcd,"Recording now","","","");

    // setup teensy communication
	Pi2c teensy1(teensyAddress);
	
    // send teensy the recording time (teensy starts recording)
    int recordTimeMS = recordTimeSec * 1000;
//    teensy1.i2cWrite(int2str(recordTimeMS).cstr(), (int2str(recordTimeMS).length()+1)); 

    // wait slightly longer than recording time
	delay(1000*recordTimeSec + 500);

	/*
	char recieve[chunkSize]; //temporary location to hold recieved bytes
    // Loop for reading multiple chunks of data
    for (int j=0; j<4; j++) {
        // Read a chunk from i2c
        cout << "Reading data" << std::endl;
        teensy1.i2cRead(recieve, chunkSize);
        // Print data to file
        cout << "Printing to file" << endl;
        for (int i = 0; i < chunkSize; i += 2) { 
            unsigned char lower = recieve[i];
            unsigned char upper = recieve[i+1];
            unsigned short value = (upper << 8) | lower;
            os << value << " " << endl;
        }
        // delay to let teensy read data
        usleep(600);
    }
    os.close();
	*/

/*
	// calculate total number of bytes for the recording time
	int numMics = 2;
	int totalBytes = 44100 * recordTimeSec * 2 * numMics;

	// request the total num bytes from teensy in increments of (128)
	// separate data into the files, write to files
	int mic1Counter = 0;
	int mic2Counter = 0;
	for (int j=0; j< totalBytes/chunkSize; j++) { // may need to adjust the upper loop limit
		receiveData(mic1, teensy1, chunkSize, &mic1Counter);
        usleep(600); // delay to let teensy read data
        receiveData(mic2, teensy1, chunkSize, &mic2Counter);
        usleep(600); // delay to let teensy read data
	}
	mic1.close();
	mic2.close();



	/////////////////////////////////// ON FINISH ///////////////////////////////////////
	lcdClear(lcd);
	lcdPrint(lcd,"Finished Recording","","","");

	/*
	// show graph of 1 sec of recording
	makeGraph("mic1.txt");

	// show graph of fft
	runFFT(nearestPow2(valueCounter), "mic2.txt", "fft.txt");
	makeGraph("fft.txt");
	*/

	return 0;
}




void setupPins() {
	pinMode(startButtonPin, INPUT);
	pinMode(upButtonPin, INPUT);
	pinMode(downButtonPin, INPUT);
	pullUpDnControl(startButtonPin, PUD_DOWN);
	pullUpDnControl(upButtonPin, PUD_DOWN);
	pullUpDnControl(downButtonPin, PUD_DOWN);
}


void waitForStart() {
	updateWaitingScreen();
	// while the start button hasn't been pressed
	while(!digitalRead(startButtonPin)) {
		if (digitalRead(upButtonPin)) {
			// increase the record time
			recordTimeSec++;
			cout << recordTimeSec << endl;
			updateWaitingScreen();
			delay(200);
		} else if (digitalRead(downButtonPin)) {
			// descrease record time
			if (recordTimeSec > 1) {
				recordTimeSec--;
			}
			cout << recordTimeSec << endl;
			updateWaitingScreen();
			delay(200);
		}
		
	}
}

void updateWaitingScreen() {
	string lengthString = int2str(recordTimeSec) + " sec";
	lcdClear(lcd);
	lcdPrint(lcd,"Record for", lengthString.c_str(), "Press start", "");
}

string int2str(int num) {
	stringstream strs;
	strs << num;
	return strs.str();
}

/*
// function reads in data from a teensy and writes to a file
void receiveData(ifstream &outfile, Pi2c &teensy, int bufSize, int *valueCounter) {
	char recieve[bufSize]; 
	teensy.i2cRead(recieve, bufSize);
	// convert from bytes to integer, write to file
	for (int i=0; i < bufSize; i+=2) {
		unsigned char lower = recieve[i];
		unsigned char upper = recieve[i+1];
		unsigned short value = (upper << 8) | lower;
		if (value > 10000){
			// subtract 2^16
			value -= 65536; 
		}
		outfile << *valueCounter << " " value << endl;
		(*valueCounter)++;
	}
}

*/

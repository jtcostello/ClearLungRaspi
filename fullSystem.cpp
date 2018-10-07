#include <iostream>
#include <fstream>
#include <wiringPi.h>

// LCD - TESTING
//#include "newLcdCode/lcd_just_library.h"
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
*/


////////// Globals ////////////
int recordTimeSec = 1;

const int startButtonPin = 27;
const int upButtonPin = 28;
const int downButtonPin = 29;

const int teensyAddress = 7;
const int sentBytes = 128;

int fd;



void waitForStart();
void updateWaitingScreen();

// temp
void lcdPrint(const char *words1,const char *words2,const char *words3, const char *words4);

int main() {
/////////////////////////////////// ON BOOT ///////////////////////////////////////
	// setup GPIO inputs and LCD
	wiringPiSetup();
	fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);

	// setup button pins
	pinMode(startButtonPin, INPUT);
	pinMode(upButtonPin, INPUT);
	pinMode(downButtonPin, INPUT);
	pullUpDnControl(startButtonPin, PUD_DOWN);
	pullUpDnControl(upButtonPin, PUD_DOWN);
	pullUpDnControl(downButtonPin, PUD_DOWN);

	// Display title text
	lcdClear(fd);
	lcdPrint("","Clear Lung Project","","");
	delay(2000);

	// Display option to select recording time
	// update the display on button presses
	// wait for start button press
	waitForStart();

	cout << "done waiting for start" << endl;
	lcdClear(fd);
	lcdPrint("Recording now","","","");





	////////// Start recording - ***** NEEDS TO BE TESTED ***   //////////////////////////
    Pi2c ard(teensyAddress); //look at address for i2c communications
    char recieve[sentBytes]; //temporary location to hold recieved bytes
    char recordingTime[8] = "300";
    const int recTime_Length = 3;
	// Open output file
    ofstream os; 
    os.open("output.txt");
    assert(os.is_open());
    // Send time to run
    cout << "Recording for " << atoi(recordingTime)/1000 << " milliseconds" << std::endl;
    ard.i2cWrite(recordingTime, recTime_Length); 
    // Wait for said time
    usleep((unsigned int)atoi(recordingTime));



    // TEMP: delay a little more to let teensy setup
    delay(1000);


    // Loop for reading multiple chunks of data
    for (int j=0; j<6; j++) {
        // Read a chunk from i2c
        cout << "Reading data" << std::endl;
        ard.i2cRead(recieve, sentBytes);
        // Print data to file
        cout << "Printing to file" << endl;
        for (int i = 0; i < sentBytes; i += 2) { 
            unsigned char lower = recieve[i];
            unsigned char upper = recieve[i+1];
            unsigned short value = (upper << 8) | lower;
            os << value << " " << endl;
        }
        // delay to let teensy read data
        usleep(600);
    }
    os.close();







    // Done Recording
	lcdClear(fd);
	lcdPrint("Finished Recording","","","");




	return 0;
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
			stringstream strs;
  			strs << recordTimeSec;
  			string lengthString = strs.str() + " sec";
			lcdClear(fd);
			lcdPrint("Record for", lengthString.c_str(), "Press start", "");

}



void lcdPrint(const char *words1,const char *words2,const char *words3, const char *words4) {
	//int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	std::vector <const char*> word_vector;
	word_vector.push_back(words1);
	word_vector.push_back(words2);
	word_vector.push_back(words3);
	word_vector.push_back(words4);
	for(int line = 0; line < 4; ++line){
		lcdPosition(fd, 0, line);
		lcdPuts(fd, word_vector[line]);
	}
}



#include <iostream>
#include <wiringPi.h>

// LCD - TESTING
#include "/home/pi/ClearLungRaspi/newLcdCode/CLP_lcd.h"
#include <lcd.h>
#include <vector>


using namespace std;


/*
 Compile with: 
 g++ pilcd.cpp /home/pi/ClearLungRaspi/newLcdCode/CLP_lcd.h 
 /home/pi/ClearLungRaspi/newLcdCode/CLP_lcd.cpp -o pilcd
*/



int main(int argc, char * argv[]) {
	
	wiringPiSetup();
	int lcd = setupLCD();
	lcdClear(lcd);
	if (argc==5) {
		lcdPrint(lcd, argv[1], argv[2], argv[3], argv[4]);
	} else {
		cout << "Need 4 input strings" << endl;
	}
	//lcdPrint(lcd,"","Clear Lung Project","","");

	return 0;
}

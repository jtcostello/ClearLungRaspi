#include <iostream>
#include <wiringPi.h>

// LCD - TESTING
#include "newLcdCode/CLP_lcd.h"
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
    lcd = setupLCD();
	lcdClear(lcd);
	lcdPrint(lcd, argv[0], argv[1], argv[2], argv[3])
	//lcdPrint(lcd,"","Clear Lung Project","","");

	return 0;
}
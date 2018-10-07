// simple code to test the lcd library
// compile with g++ testLCDLibrary.cpp CLP_lcd.cpp -lwiringPi -lwiringPiDev -o testLCDLibrary
// 4-15-18
 
#include <iostream>
#include "CLP_lcd.h"
#include <wiringPi.h>
#include <lcd.h>
using namespace std;



int main() {
	wiringPiSetup();
	int lcd = setupLCD();
	lcdClear(lcd);
	lcdPrint(lcd, "testing","4!@#$%^&*","now","");




	return 0;
}


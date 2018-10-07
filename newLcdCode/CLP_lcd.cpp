// functions for updating the lcd display text
// lcd.cpp for example usage


#include <iostream>
#include <wiringPi.h>
#include <lcd.h>
#include <vector>
#include "CLP_lcd.h"

void lcdPrint(int fd, const char *words1,const char *words2,const char *words3, const char *words4) {
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

/*
void lcdClear(int fd) {
	//int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	lcdClear(fd);
}
*/

int setupLCD() {
	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	return fd;
}



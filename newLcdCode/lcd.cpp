// Based off lcd1602 -> see that for more in depth usage
// This file provides example usage for lcd code
// Use "lcd_just_library.cpp" for functions to include in other code

#include <iostream>
#include <wiringPi.h>
#include <lcd.h>
#include <vector>

void lcdPrint(const char *words1,const char *words2,const char *words3, const char *words4) {
	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
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


void lcdClear() {
	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	lcdClear(fd);
}




int main(void) {
	wiringPiSetup();
	lcdClear();
	lcdPrint("M-HEAL","Clear Lung Projgect","","");

	return 0;
}

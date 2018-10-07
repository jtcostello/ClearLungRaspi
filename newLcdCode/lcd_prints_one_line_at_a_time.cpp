// Based off lcd1602 -> see that for more in depth usage
#include <iostream>
#include <wiringPi.h>
#include <lcd.h>

void lcdPrint(int line, const char *words) {
	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	lcdPosition(fd, 0, line); 
	lcdPuts(fd, words);
	std::cout << "fd = " << fd << std::endl;
}


void lcdClear() {
	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	lcdClear(fd);
        std::cout << "fd = " << fd << std::endl;
}




int main(void) {
	wiringPiSetup();
	std::cout << "1" << std::endl;
//	int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	std::cout << "2" << std::endl;
	 lcdClear();
	std::cout << "3" << std::endl;
	//char *words = "M-HEAL";
	lcdPrint(1, "M-HEAL");
	std::cout << "4" << std::endl;
	//words = "Clear Lung Project"
	delay(2000);
	lcdPrint(2, "Clear Lung Project");

	/*int fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0);
	lcdClear(fd);*/
	return 0;
}

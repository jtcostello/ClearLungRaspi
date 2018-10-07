#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>


int main(void)
{
	int fd;
	int i;
	
	if(wiringPiSetup() == -1){
		exit(1);
	}
	
	fd = lcdInit(4,20,4, 2,3, 6,5,4,1,0,0,0,0); //see /usr/local/include/lcd.h
	printf("%d", fd);
	if (fd == -1){
		printf("lcdInit 1 failed\n") ;
		return 1;
	}
	sleep(1);
	lcdClear(fd);
	lcdPosition(fd, 0, 0); 
	lcdPuts(fd, "M-HEAL");

	lcdPosition(fd, 0, 1); 
	lcdPuts(fd, "Clear Lung Project");

	sleep(1000);
	lcdClear(fd);

	return 0;
}

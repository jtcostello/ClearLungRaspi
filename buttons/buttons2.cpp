#include <wiringPi.h>
#include <iostream>
using namespace std;

int main () {
    wiringPiSetup ();

    int pin = 29;
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_DOWN);

    while(1) {
    	if (digitalRead(pin)) {
    		cout << "high" << endl;
    	} else {
    		cout << "low" << endl;
    	}
	delay(1);
    }


    return 0;
}

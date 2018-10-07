#include <wiringPi.h>
#include <iostream>
using namespace std;


// simple code to test pin output works


int main () {
    wiringPiSetup ();

    int pin = 25;
    pinMode(pin, OUTPUT);

    while(1) {
    	digitalWrite(pin,HIGH);
    	delay(1000);
    	digitalWrite(pin,LOW);
    	delay(1000);
    }


    return 0;
}

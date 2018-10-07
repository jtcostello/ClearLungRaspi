
// Code to run at startup - displays the IP address on the lcd screen
// Makes it so you don't need a full screen/keyboard
// 4-15-18

// compile with
// g++ displayIP.cpp /home/pi/Desktop/newLcdCode/CLP_lcd.cpp -lwiringPi -lwiringPiDev -o displayIP

// /etc/rc.local was edited to include this program

#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <unistd.h> // for usleep
#include <iostream>
#include "/home/pi/Desktop/newLcdCode/CLP_lcd.h"
#include <wiringPi.h>
#include <lcd.h>

using namespace std;


char * getIPAddress();



int main () {
	wiringPiSetup();
    int lcd = setupLCD();
    // runs for 40 sec before stopping (so other tasks can use lcd)
    for(int i=0; i<4; i++) {
        // display IP on screen
        lcdClear(lcd);
        lcdPrint(lcd, getIPAddress(), "", "","");
        // update every 10 sec
        usleep(10*1000000);
    }
    lcdClear(lcd);
    lcdPrint(lcd, getIPAddress(), "(done updating IP)","","");
    return 0;
}





// function to get all IP addresses, returns the last IP as a char array
// (the last IP in the list is usually wifi IP)
char * getIPAddress() {
	struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            //printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
        }
    }
    freeifaddrs(ifap);
    return addr;
}


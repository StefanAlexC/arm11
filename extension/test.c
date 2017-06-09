#include <stdio.h>
#include <math.h>
#include <time.h>
#include "tick.h"
#include <wiringPi.h>
#include "BrickPi.h"
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 10
#define UP_DOWN_PIN 1
#define PEN_MOTOR PORT_A
#define PAPER_MOTOR PORT_B
#define PEN_HORIZONTAL_MOTOR PORT_C

void enableMotor(int motorIndex) {
    BrickPi.MotorEnable[motorIndex] = 1;
}

void disableMotor(int motorIndex) {
    BrickPi.MotorEnable[motorIndex] = 0;
}

void setMotorSpeed(int motorIndex, int speed) {
    BrickPi.MotorSpeed[motorIndex] = speed;
}


void penDown(void) {
    setMotorSpeed(PEN_MOTOR, 255);
    printf("%s\n", "MOVING PEN DOWN");
    BrickPi.Timeout = 100;
    BrickPiSetTimeout();
    BrickPiUpdateValues();
    setMotorSpeed(PEN_MOTOR, 0);
    usleep(500000);
    //usleep(1000000);
    //printf("%s\n", "stopped motor A");
}

void penUp(void) {
    setMotorSpeed(PEN_MOTOR, -255);
    printf("%s\n", "MOVING PEN UP");
    BrickPi.Timeout = 100;
    BrickPiSetTimeout();
    BrickPiUpdateValues();
    setMotorSpeed(PEN_MOTOR, 0);
    usleep(500000);
    //setMotorSpeed(PEN_MOTOR, 0);
}

void printDot(void) {
    penDown();
    penUp();
}

void movePenRight() {
	setMotorSpeed(PEN_HORIZONTAL_MOTOR, 255);
    printf("%s\n", "MOVING PEN TO NEXT ELEMENT");
    BrickPi.Timeout = 100;
    BrickPiSetTimeout();
    BrickPiUpdateValues();
    setMotorSpeed(PEN_HORIZONTAL_MOTOR, 0);
    usleep(500000);
}

void movePenAtStart() {
	setMotorSpeed(PEN_HORIZONTAL_MOTOR, -255);
    printf("%s\n", "MOVING PEN TO START");
    BrickPi.Timeout = 2000;
    BrickPiSetTimeout();
    time_t start = time(0);
    while (time(0) - start < 2) {	
        BrickPiUpdateValues();
	}
    setMotorSpeed(PEN_HORIZONTAL_MOTOR, 0);
    usleep(100000);
    
}

void printRow(int picture[]) {
    int j = 0;
    for (j = 0; j < WIDTH; j++) {
		movePenRight();
		printf("MOVED PEN TO x coord %i\n", j + 1);
        if (picture[j]) {
            printDot();
        }
    }
}

void scrollPaper(void) {
    setMotorSpeed(PAPER_MOTOR, 255);
    printf("%s\n", "SCROLLING PAPER");
    BrickPi.Timeout = 100;
    BrickPiSetTimeout();
    BrickPiUpdateValues();
    usleep(100000);
    setMotorSpeed(PAPER_MOTOR, 0);
}

void print(int picture[][10]) {
  
    int i = 0;
    for (i = 0; i < HEIGHT; i++) {
        printRow(picture[i]);
        movePenAtStart();
        scrollPaper();
    }
}

int main() {
    
    int result;
    
    ClearTick();

	result = BrickPiSetup();
	// printf("BrickPiSetup: %d\n", result);
	if(result)
	return 0;

	BrickPi.Address[0] = 1;
	BrickPi.Address[1] = 2;
	
	enableMotor(PEN_MOTOR);	//Enable the motors
	enableMotor(PAPER_MOTOR);
	enableMotor(PEN_HORIZONTAL_MOTOR);
	
	result = BrickPiSetupSensors();		//Set up the properties of sensors for the BrickPi

	BrickPi.Timeout=1000;				//Set timeout value for the time till which to run the motors after the last command is pressed
	BrickPiSetTimeout();				//Set the timeout
	
	//BrickPi.MotorSpeed[PEN_MOTOR] = 255;
	
	int test[10][10] = {
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
    };

    print(test);

	
	BrickPiUpdateValues();	//Update the motor values
	usleep(10000);	

    return 0;
}

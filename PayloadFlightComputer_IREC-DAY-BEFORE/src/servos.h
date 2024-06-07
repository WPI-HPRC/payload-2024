#pragma once 
#include <ServoControls/ServoController.h>

struct Servos {
    ServoController *paraServo_1; 
	ServoController *paraServo_2; 
	ServoController *paraServo_3;  
	ServoController *paraServo_4;
	ServoController *cameraServo; 
}; 
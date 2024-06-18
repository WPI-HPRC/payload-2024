#pragma once 
#include <Arduino.h>
#include <Servo.h>
#include <stdlib.h>
#include <math.h>
#include <Wire.h>
#include "analogData.h"

#define ANALOG_I2C_ADDRESS 0x35 

class ServoController {
    private:    
        Servo servo; 
        bool clockwise; 
        int inputPin; 
    public: 

        ServoController(int, bool); 

        /**
         * @brief Reads current Servo value 
        */
        uint32_t readServo(); 
        /**
         * @brief Writes desired Servo value  
        */
        void writeServo(int value); 

        bool readAnalogData(AnalogData *analogData); 
};
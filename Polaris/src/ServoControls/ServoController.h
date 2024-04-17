#pragma once 
#include <Arduino.h>
#include <Servo.h>
#include <stdlib.h>
#include <math.h>

class ServoController {
    private:    
        Servo servo; 
        bool clockwise;
        // servo angle is in degrees
        float p; // s^-1
        float pulleyDiameter; // cm
        float stringLength;   // cm
        int inputPin;
        int woundTick;
    public: 
        ServoController(int, bool, float, float, float, int, int);

        ServoController(int); 

        void setServo(float); 
        /**
         * @brief Sets servo speed to aim for target string length.
         * @param newStringLength The target length. 
        */
        void adjustString(float);
        /**
         * @brief Sets servo speed to aim for target angle.
         * @param newAngle The target angle.
         * @param currAngle The current angle. 
        */
        void setToAngle(float, float);
        
        /**
         * @brief "Wraps" t to find the shortest distance to 0 around a circle of circumference WRAP_MAX
         * @param t the number to wrap
        */
        int wrap(int);

        /**
         * @brief Reads current Servo value 
        */
        uint32_t readServo(); 
};

/**
 * @brief Converts an angle in degrees to be within the range of [-180, 180).
 * @param angle The angle in degrees to be converted.
*/
float shortestAngle(float);
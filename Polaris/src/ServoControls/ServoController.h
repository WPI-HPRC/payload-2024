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
		int zeroPos;
        int woundTicks;
    public: 
        ServoController(int, bool, float, float, float, int, int);

        ServoController(int); 

        void setServo(float); 
        /**
         * @brief Sets servo speed to aim for target string length in cm.
         * @param newStringLength The target length in cm.
        */
        void adjustString(float);
        /**
         * @brief Sets servo speed to aim for target angle in ° offset from neutral.
         * @param newAngle The target angle in °.
        */
        void setToAngle(float);
        /**
         * @brief "Wraps" t to find the shortest distance to 0 around a circle of circumference WRAP_MAX
         * @param t the number to wrap
        */
        int wrap(int);

        /**
         * @brief Reads current Servo value 
        */
        uint32_t readServo(); 
	private:
		/**
		 * @brief Set servo speed using P controller to change the angle by angleDiff.
		 * Use `setServo` or `adjustString` to target a specific length or angle instead.
		 * @param angleDiff Angle difference in °.
		*/
		void setSpeedP(float);
};

/**
 * @brief Converts an angle in degrees to be within the range of [-180, 180).
 * @param angle The angle in degrees to be converted.
*/
float shortestAngle(float);
#include <Servo.h>
#include <stdlib.h>
#include "ServoController.h"

class ServoController {
    private:    
        Servo servo;
        bool clockwise;
        // servo angle is in degrees
        float p; // s^-1
        float pulleyDiameter; // cm
        float stringLength;   // cm
    public:
        ServoController(int, bool);
        void adjustString(float);
        void setToAngle(float);
};
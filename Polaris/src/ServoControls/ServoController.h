#include <Servo.h>
#include <stdlib.h>
#include "ServoController.h"

class ServoController {
    private:    
        Servo myServo;
        bool clockwise;
        // servo angle is in degrees
        float angle;
    public:
        ServoController(int, bool);
        void updateServo(float);
        void setToAngle(float);
};
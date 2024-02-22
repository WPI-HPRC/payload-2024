#include <Servo.h>
#include <stdlib.h>
#include "ServoController.h"

// const float pulleyDiameter = 4.374;
// const float stringLength = 100.;
// const float pGain = 5.;

ServoController::ServoController(int pin, bool clockwise, float p,
        float pulleyDiameter, float stringLength) {
    this->clockwise = clockwise;
    this->servo.attach(pin);
    this->p = p;
    this->pulleyDiameter = pulleyDiameter; //p is P-gain 
    this->stringLength = stringLength;
    // Set servo to be still
    this->servo.write(90.);
}

float shortestAngle(float angle) {
    return fmod(angle + 180., 360.) - 180.;
}

void ServoController::setToAngle(float newAngle, float currAngle) {
    float angleDiff = shortestAngle((newAngle - currAngle));
    float degreesPerSec = (this->clockwise ? -1. : 1.)*(this->p)*angleDiff;
    const float reduction = 1. / 1.;
    this->servo.write(constrain(90. + (0.085*90./60.)/reduction*degreesPerSec,
                                0., 180.));
}

void ServoController::adjustString(float newStringLength) {
    const float  angleOffset = 0.0;
    float currAngle = servo.read();
    float currStringLength = shortestAngle(currAngle - angleOffset) *
                             PI/180.*(0.5*this->pulleyDiameter);
    float newAngle = newStringLength/(0.5*this->pulleyDiameter)*(180./PI) +
                     angleOffset;
    
    setToAngle(newAngle, currAngle);
}
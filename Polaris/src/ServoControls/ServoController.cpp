#include "ServoController.h"

// const float pulleyDiameter = 4.374;
// const float stringLength = 100.;
// const float pGain = 5.;

ServoController::ServoController(
        int pin,
        bool clockwise,
        float p,
        float pulleyDiameter,
        float stringLength,
        int inputPin,
        int zeroPos) {
    this->servo = servo; 
    this->clockwise = clockwise;
    this->servo.attach(pin);
    this->p = p;
    this->pulleyDiameter = pulleyDiameter; //p is P-gain 
    this->stringLength = stringLength;
    this->inputPin = inputPin;
    this->woundTicks = zeroPos + wrap(analogRead(inputPin) - zeroPos);
    this->zeroPos = zeroPos;
    // Set servo to be still
    this->servo.write(90.);
}

ServoController::ServoController(int pin){
    this->servo.attach(pin); //check if this is the correct syntax 
    this->servo.write(90.);
}

void ServoController::setServo(float value){
    this->servo.write(value); //cause cam servo is easy...
}

// float shortestAngle(float angle) {
//     return fmod(angle + 180., 360.) - 180.;
// }

int wrap(int t) {
    return (t + WRAP_MAX/2) % WRAP_MAX - WRAP_MAX/2;
}

void ServoController::updateWoundTicks() {
    woundTicks += wrap(analogRead(inputPin) - woundTicks);
}

void ServoController::setToAngle(float newAngle) {
    float currAngle = (woundTicks - zeroPos) * 360. / WRAP_MAX; // °
    setSpeedP(newAngle - currAngle);
}

void ServoController::adjustString(float newStringLength) {
    float currStringLength = (woundTicks - zeroPos) * 2.*PI / WRAP_MAX
                             *(0.5*this->pulleyDiameter); // cm
    float angleDiff = 360. * (newStringLength - currStringLength) // °
                      / (PI*this->pulleyDiameter);
    setSpeedP(angleDiff);
}

void ServoController::setSpeedP(float angleDiff) {
    float targetSpeed = (this->clockwise ? -1. : 1.)*(this->p)*angleDiff; // °
    const float reduction = 1. / 1.; // Not true
    const float maxSpeed = ( // in °/s
        // from https://docs.axon-robotics.com/axon-servos/axon-max+
        60./0.085 // 0.085 s/60° -> °/s
    )*reduction;
    this->servo.write(180.*constrain(.5 + .5*targetSpeed/maxSpeed, 0., 1.));
}

uint32_t ServoController::readServo(){ //Need to check if this works...
    return analogRead(inputPin);
}
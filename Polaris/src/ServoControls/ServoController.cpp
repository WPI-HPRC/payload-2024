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
		int avgFirst,
        int zeroPos) {
    this->servo = servo; 
    this->clockwise = clockwise;
    this->servo.attach(pin);
    this->p = p;
    this->pulleyDiameter = pulleyDiameter; //p is P-gain 
    this->stringLength = stringLength;
    this->inputPin = inputPin;
    this->woundTicks = zeroPos + wrap(analogRead(inputPin) - zeroPos);
	this->avgFirst = avgFirst;
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

float shortestAngle(float angle) {
    return fmod(angle + 180., 360.) - 180.;
}

int wrap(int t) {
    const int WRAP_MAX = 1024;
	return (t + WRAP_MAX/2) % WRAP_MAX - WRAP_MAX/2;
}

void ServoController::updateWoundTicks() {
    woundTicks += wrap(analogRead(inputPin) - woundTicks);
}

void ServoController::setToAngle(float newAngle, float currAngle) {
    float angleDiff = shortestAngle(newAngle - currAngle);
    float targetSpeed = (this->clockwise ? -1. : 1.)*(this->p)*angleDiff;
    const float reduction = 1. / 1.; // Not true
	const float maxSpeed = ( // in °/s
		60./0.085 // 0.085 s/60° -> °/s (from https://docs.axon-robotics.com/axon-servos/axon-max+)
	)*reduction;
    this->servo.write(180.*constrain(.5 + .5*targetSpeed/maxSpeed, 0., 1.));
}

void ServoController::adjustString(float newStringLength) {
    const float angleOffset = 0.0;
    float currAngle = analogRead(inputPin);
    float currStringLength = shortestAngle(currAngle - angleOffset) *
                             PI/180.*(0.5*this->pulleyDiameter);
    float newAngle = newStringLength/(0.5*this->pulleyDiameter)*(180./PI) +
                     angleOffset;
    
    setToAngle(newAngle, currAngle);
}

uint32_t ServoController::readServo(){ //Need to check if this works...
    return analogRead(inputPin);
}
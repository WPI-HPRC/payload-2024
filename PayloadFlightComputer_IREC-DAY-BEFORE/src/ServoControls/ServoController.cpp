#include "ServoController.h"
#include "analogData.h"

// const float pulleyDiameter = 4.374;
// const float stringLength = 100.;
// const float pGain = 5.;

// ServoController::ServoController(int pin, bool clockwise, float p, float pulleyDiameter, float stringLength, int inputPin) {
//     this->servo = servo; 
//     this->clockwise = clockwise;
//     this->servo.attach(pin);
//     this->p = p;
//     this->pulleyDiameter = pulleyDiameter; //p is P-gain 
//     this->stringLength = stringLength;
//     this->inputPin = inputPin; 
//     // Set servo to be still
//     this->servo.write(90.);
// }

ServoController::ServoController(int pin, bool clockwise){ 
    this->servo.attach(pin); 
    this->clockwise = clockwise; 
    if(pin == 28){ 
        this->servo.writeMicroseconds(988);
    }
    else{
        this->servo.writeMicroseconds(1493);
    }
    
}

// float shortestAngle(float angle) {
//     return fmod(angle + 180., 360.) - 180.;
// }

// void ServoController::setToAngle(float newAngle, float currAngle) {
//     float angleDiff = shortestAngle((newAngle - currAngle));
//     float degreesPerSec = (this->clockwise ? -1. : 1.)*(this->p)*angleDiff;
//     const float reduction = 1. / 1.;
//     this->servo.write(constrain(90. + (0.085*90./60.)/reduction*degreesPerSec,
//                                 0., 180.));
// }

// void ServoController::adjustString(float newStringLength) {
//     const float  angleOffset = 0.0;
//     float currAngle = analogRead(inputPin);
//     float currStringLength = shortestAngle(currAngle - angleOffset) *
//                              PI/180.*(0.5*this->pulleyDiameter);
//     float newAngle = newStringLength/(0.5*this->pulleyDiameter)*(180./PI) +
//                      angleOffset;
    
//     setToAngle(newAngle, currAngle);
// }

uint32_t ServoController::readServo(){ //Need to check if this works...
    return analogRead(inputPin);
}

void ServoController::writeServo(int value){
    this->servo.writeMicroseconds(value); 
}

// bool ServoController::controlServo(float desiredStringLength, int encoderStart){

//     float desiredStringDistance = desiredStringLength - currentStringLength; //Change in length of string required
//     bool withinThreshold = false; 

//     int direction = (desiredStringLength - currentStringLength)/ abs((desiredStringLength - currentStringLength)); 
   
//     //CHANGE TO CONSTANTS SO THEY ARE NICE 
//     float circumferencePulley = 43.75 * 3.14; //circumference of pulley 
//     float encoderTicksPerMM = 1024/circumferencePulley; //No. encoder ticks per mm conversion 

//     float desiredEncoderDistance =  desiredStringDistance * encoderTicksPerMM;  //Includes direction as well 

//     if(abs(desiredEncoderDistance) > 1792){ //Fail safe 1, stop at 1 rotation 
//        desiredEncoderDistance = 1024 * direction; 
//     }

//     while(!withinThreshold){
//         int encoderDistanceTraveled = encoderStart - currentEncoderCount; 

//     }
    
//     //TODO: Finish this :) 

// }

bool ServoController::readAnalogData(AnalogData *analogData){

    bool retVal = false;

    //delayMicroseconds(250); //may need to delete this depending on speed requirements 

    uint8_t buffer[sizeof(AnalogData)];
    //use some explicit casts to suppress warnings
    if (Wire.requestFrom(ANALOG_I2C_ADDRESS, (int)sizeof(AnalogData), true) == sizeof(AnalogData)) //WHAT IS THE I2C Address?? 
    {
        for(uint8_t i = 0; i < sizeof(AnalogData); i++) buffer[i] = Wire.read();
        memcpy(analogData, buffer, sizeof(AnalogData));
        
        //TODO: add basic error checking, including checksum

        retVal = true;
    }
    return retVal;
}
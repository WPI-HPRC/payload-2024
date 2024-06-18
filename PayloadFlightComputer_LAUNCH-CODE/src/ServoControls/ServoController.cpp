#include "ServoController.h"

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


uint32_t ServoController::readServo(){ 
    return analogRead(inputPin);
}

void ServoController::writeServo(int value){
    this->servo.writeMicroseconds(value); 
}


bool ServoController::readAnalogData(AnalogData *analogData){

    bool retVal = false;

    //delayMicroseconds(250); //may need to delete this depending on speed requirements 

    uint8_t buffer[sizeof(AnalogData)];
    //use some explicit casts to suppress warnings
    if (Wire.requestFrom(ANALOG_I2C_ADDRESS, (int)sizeof(AnalogData), true) == sizeof(AnalogData)) 
    {
        for(uint8_t i = 0; i < sizeof(AnalogData); i++) buffer[i] = Wire.read();
        memcpy(analogData, buffer, sizeof(AnalogData));

        retVal = true;
    }
    return retVal;
}
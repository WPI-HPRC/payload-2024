
// Coast state
// This state occurs after the motor has burned out as the rocket is on its way to apogee

#include "02-Coast.h"
#include "03-DrogueDescent.h"
#include "06-Abort.h"
#include "FlightParams.hpp"
#include "State.h"

Coast::Coast() : State() {}

Coast::~Coast() {
    airbrakesServo.write(AIRBRAKE_RETRACTED);
}

void Coast::initialize_impl() {}

void Coast::loop_impl()
{
    // calculate vertical velocity
    float verticalVelocity = (telemPacket.altitude - lastAltitude) / (deltaTime / 1000.0);
    lastAltitude = telemPacket.altitude;

    // add vertical velocity to cyclic buffer
    verticalVelocityBuffer[bufferIndex] = verticalVelocity;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageVerticalVelocity = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += verticalVelocityBuffer[i];
    }
    averageVerticalVelocity = sum / 10.0;

    bufferIndex = (bufferIndex + 1) % 10;
    
    // If the average vertical velocity <= 0 for more than 30 cycles, rocket has passed apogee
    apogeePassed = apogeeDebouncer.checkOut(averageVerticalVelocity <= 0);

    // Serial.print("SERVO POS: ");
    // Serial.println(analogRead(SERVO_FEEDBACK_GPIO));

    // Handle airbrake control
    // TODO: I don't really know which values correspond to which positions yet, so these values are subject to change
    switch (this->servoState) {
    case WAIT:
        airbrakesServo.write(AIRBRAKE_RETRACTED);
        if (this->currentTime >= 500) {
            this->servoState = HALF;
        }
        break;
    case FULL:
        // NOTE: This is misnamed since we changed it at the last moment to be another 50% extension
        airbrakesServo.write(AIRBRAKE_HALF_EXTENSION);
        if (this->currentTime >= 12500) {
            this->servoState = RETRACTED;
        }
        break;
    case THREE_QUARTERS:
        airbrakesServo.write(AIRBRAKE_75_EXTENSION);
        if (this->currentTime >= 6500) {
            this->servoState = ONE_QUARTER;
        }
        break;
    case HALF:
        airbrakesServo.write(AIRBRAKE_HALF_EXTENSION);
        if (this->currentTime >= 4500) {
            this->servoState = THREE_QUARTERS;
        }
        break;
    case ONE_QUARTER:
        airbrakesServo.write(AIRBRAKE_25_EXTENSION);
        if (this->currentTime >= 8500) {
            this->servoState = FULL;
        }
        break;
    case RETRACTED:
        airbrakesServo.write(AIRBRAKE_RETRACTED);
        break;
    }
}

//! @details max 8 seconds until deploy
State *Coast::nextState_impl()
{
    // Transition state if condition met
    if (apogeePassed)
    {
        return new DrogueDescent();
    }

    // if the state hasn't changed for much more than the expected COAST time, go to abort
    // 1.5 * TIME_IN_COAST == 28.5 seconds
    if (this->currentTime > 1.5 * TIME_IN_COAST)
    {
        return new Abort();
    }
    return nullptr;
}

enum StateId Coast::getId()
{
    return StateId::ID_Coast;
}

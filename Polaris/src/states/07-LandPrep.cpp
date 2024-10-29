#include "State.h"
#include "08-Recovery.h"
#include "07-LandPrep.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(Sensorboard *sensors, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(sensors, attitudeStateEstimator, xbee, servos, openMV) {}

void LandPrep::initialize_impl()
{
    stateStartTime = currentTime;
}

void LandPrep::loop_impl()
{
    stateTime = currentTime - stateStartTime;
    if (stateTime < MAX_SERVO_WIND_TIME)
    {
        servos->paraServo_1->writeServo(SERVO_COUNTER_UNWIND);
        servos->paraServo_2->writeServo(SERVO_CLOCK_UNWIND); // Check Servo values
    }
    else
    {
        servos->paraServo_1->writeServo(SERVO_CENTER);
        servos->paraServo_2->writeServo(SERVO_CENTER); // Check Servo values
    }

    servos->cameraServo->writeServo(CAM_RETRACT);

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

    // if the average vertical velocity is less than the expected landing velocity for 30 cycles, the rocket has landed
    landed = landedDebouncer.checkOut(abs(averageVerticalVelocity) < LANDING_VELOCITY);
}

State *LandPrep::nextState_impl()
{
    if (landed)
    {
        #ifdef DEBUG_MODE
        Serial.println("Entering Recovery!");
        #endif
        return new Recovery(sensors, attitudeStateEstimator, xbee, servos, openMV);
    }
    return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}

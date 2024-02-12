// #include "Land.h"
// #include "State.h"
// #include "Recovery.h"

// Land::Land(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip) : State(sensors, stateEstimator, flashChip) {}

// void Land::initialize_impl() {}

// void Land::loop_impl() {
//     // calculate vertical velocity
//     float verticalVelocity = (sensorPacket.altitude - lastAltitude) / (deltaTime / 1000.0);
//     lastAltitude = sensorPacket.altitude;

//     // Velocity value gets updated in sensor reading fcn
//     // add to cyclic buffer
//     transitionBufVelVert[transitionBufIndVelVert] = verticalVelocity;
//     // take running average value
//     float sum = 0.0;
//     float average = 0.0;
//     for (int i = 0; i < 10; i++)
//     {
//         sum += transitionBufVelVert[i];
//     }
//     average = sum / 10.0;

//     transitionBufIndVelVert = (transitionBufIndVelVert + 1) % 10;
//     // if average vertical velocity is negative, passed apogee
//     if (average < 0)   //change to == 0?????
//     {
//         // TODO: debounce apogeePassed
//         Serial.println("Land detected!");
//         apogeePassed = true;
//     }
// }

// //! @details max 8 seconds until deploy
// State *Land::nextState_impl()
// {
//     if (this->currentTime > MAX_LAND_TIME || apogeePassed)
//     {
//         return new Recovery(sensors, stateEstimator, flash);
//     }
//     return nullptr;
// }


#include "Land.h"
#include "State.h"
#include "Recovery.h"

Land::Land(struct Sensors *sensors) : State(sensors) {}

void Land::initialize_impl() {}

void Land::loop_impl() {
	// read 10 velocity samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *Land::nextState_impl() {
	if (/*this->sensorPacket.velocity == 0 ||*/ this->currentTime > MAX_LAND_TIME)
	{
		return new Recovery(sensors);
	}
	return nullptr;
}

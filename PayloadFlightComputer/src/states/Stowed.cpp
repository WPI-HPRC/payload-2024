
// #include "Stowed.h"
// #include "State.h"
// #include "Stabalize.h"
// #include "Sensors.h"
// Stowed::Stowed(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip) : State(sensors, stateEstimator, flashChip) {
// }

// void Stowed::initialize_impl(){

// }
// /*this->sensorPacket.altitude <*/
// void Stowed::loop_impl() {
//     // old motorBurnoutDetect code
//     // accel value gets updated in sensor reading fcn
//     // add to cyclic buffer
//     transitionBufAcc[transitionBufIndAcc] = sensorPacket.accelZ;
//     // take running average value
//     float sum = 0.0;
//     float average = 0.0;
//     for (int i = 0; i < 10; i++)
//     {
//         sum += transitionBufAcc[i];
//     }
//     average = sum / 10.0;

//     transitionBufIndAcc = (transitionBufIndAcc + 1) % 10;
//     // compare running average value to defined threshold

// // NEED to change this section to be specific to altitude

//     if (average < ALT_THRESHOLD_STOWED)
//     {
//         transitionBufIndAcc = 0;
//         Serial.println("Change to Initial Descent!");
//         motorBurnout = true;
//         // TODO: debounce motorBurnout with counter for like 50 loops etc
//     }
// }

// State *Stowed::nextState_impl()
// {
//     // Stay in this state for at least 3 seconds to prevent airbrake activation
//     if (this->currentTime > MAX_STOWED_TIME && motorBurnout)
//     {
//         return new Stabalize(sensors, stateEstimator, flash);
//     }
//     // TODO: add abort
//     return nullptr;
// }



#include "Stowed.h"
#include "State.h"
#include "Stabalize.h"
#include "Sensors.h"


Stowed::Stowed(struct Sensors *sensors) : State(sensors) {
}

void Stowed::initialize_impl() {
}

void Stowed::loop_impl() {

}

State *Stowed::nextState_impl()
{
	//this->sensorPacket.accelX or this->sensorPacket.altitude
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_STOWED || this->currentTime > MAX_STOWED_TIME ){
		return new Stabalize(sensors);
	}
	return nullptr;
}

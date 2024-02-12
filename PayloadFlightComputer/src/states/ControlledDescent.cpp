// #include "State.h"
// #include "ControlledDescent.h"
// #include "Land.h"
// #include "Sensors.h"
// ControlledDescent::ControlledDescent(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip) : State(sensors, stateEstimator, flashChip) {

// }

// void ControlledDescent::initialize_impl() {

// }

// void ControlledDescent::loop_impl() {
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
//     if (average < ALT_THRESHOLD_CONTROLLED)
//     {
//         transitionBufIndAcc = 0;
//         Serial.println("Change to Initial Descent!");
//         motorBurnout = true;
//         // TODO: debounce motorBurnout with counter for like 50 loops etc
//     }
// }

// State *ControlledDescent::nextState_impl()
// {
//     // Stay in this state for at least 3 seconds to prevent airbrake activation
//     if (this->currentTime > MAX_CONTROLLED_DESCENT_TIME && motorBurnout)
//     {
//         return new Land(sensors, stateEstimator, flash);
//     }
//     // TODO: add abort
//     return nullptr;
// }


#include "State.h"
#include "ControlledDescent.h"
#include "Land.h"


ControlledDescent::ControlledDescent(struct Sensors *sensors) : State(sensors) {

}

void ControlledDescent::initialize_impl() {

}

void ControlledDescent::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *ControlledDescent::nextState_impl() {
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_CONTROLLED ||this->currentTime > MAX_CONTROLLED_DESCENT_TIME)
	{
		return new Land(sensors);
	}
	return nullptr;
}

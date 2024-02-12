// #include "State.h"
// #include "Stabalize.h"
// #include "InitialDescent.h"
// #include "Sensors.h"
// Stabalize::Stabalize(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip) : State(sensors, stateEstimator, flashChip) {}
// void Stabalize::initialize_impl() {

// }
// /*this->sensorPacket.altitude <*/
// void Stabalize::loop_impl() {
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
//     if (average < ACC_THRESHOLD_STABALIZE)
//     {
//         transitionBufIndAcc = 0;
//         Serial.println("Change to Initial Descent!");
//         motorBurnout = true;
//         // TODO: debounce motorBurnout with counter for like 50 loops etc
//     }
// }

// State *Stabalize::nextState_impl()
// {
//     // Stay in this state for at least 3 seconds to prevent airbrake activation
//     if (this->currentTime > MAX_STABALIZE_TIME && motorBurnout)
//     {
//         return new InitialDescent(sensors, stateEstimator, flash);
//     }
//     // TODO: add abort
//     return nullptr;
// }



#include "State.h"
#include "Stabalize.h"
#include "InitialDescent.h"

Stabalize::Stabalize(struct Sensors *sensors) : State(sensors) {}
void Stabalize::initialize_impl() {

}
void Stabalize::loop_impl() {
// read 10 accelZ samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}
State *Stabalize::nextState_impl() {
	if (/*this->sensorPacket.accelZ >*/ ACC_THRESHOLD_STABALIZE || this->currentTime > MAX_STABALIZE_TIME)
	{
		return new InitialDescent(sensors);
	}
	return nullptr;
}

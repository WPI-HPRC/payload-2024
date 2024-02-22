#include "State.h"
#include "Freefall.h"
#include "WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall() {}
void Freefall::initialize_impl() {

}
void Freefall::loop_impl() {
// read 10 accelZ samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
		if(this->currentTime > MAX_STABALIZE_TIME ){
			//Release Camera servo
			//think of best way to start flow of camera data, just do it in each state?  
		}
}
State *Freefall::nextState_impl() {
	if (this->currentTime > MAX_FREEFALL_TIME)
	{	
		Serial.println("Entering WindLeft!")
		return new WindLeft();
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}

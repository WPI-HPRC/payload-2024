#include "Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}


void Stowed::initialize_impl() {
 
}

void Stowed::loop_impl() {
	
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	
	if (digitalRead(IR_PIN)==HIGH || stateTime > MAX_STOW_TIME){ 
		Serial.println("Entering Freefall!"); 
		return new Freefall(sensors, stateEstimator); 
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}
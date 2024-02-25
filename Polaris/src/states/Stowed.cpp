#include "Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}


void Stowed::initialize_impl() {
	this->stateStartTime = this->currentTime; 
	this->servo.attach(PARACHUTE_SERVO_4); 
	//servo.writeMicroseconds(1493); 
}

void Stowed::loop_impl() { //Shouldn't need anything in here 

	this->stateTime = this->currentTime - this->stateStartTime; 
	Serial.println(analogRead(PARACHUTE_SERVO_4_IN)); 
	if(this->stateTime < 1000){
		servo.writeMicroseconds(1100); 	
	}
	else{
		servo.writeMicroseconds(1493); 
	}	
	//Serial.println(analogRead(17)); 

	// servo.writeMicroseconds(CAM_OUT); 
	// delay(1000); 
	// servo.writeMicroseconds(CAM_RETRACT); 
	// while(true){}
	// Serial.println(analogRead(PARACHUTE_SERVO_2_IN)); 
	// Serial.println(analogRead(PARACHUTE_SERVO_3_IN)); 
	// Serial.println(analogRead(PARACHUTE_SERVO_4_IN)); 
	

	
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	return nullptr; //Don't switch
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}
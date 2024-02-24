#include "Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}


void Stowed::initialize_impl() {
	this->stateStartTime = this->currentTime; 
	this->servo.attach(PARACHUTE_SERVO_1); 
	servo.writeMicroseconds(1500); 
}

void Stowed::loop_impl() { //Shouldn't need anything in here 

	// this->stateTime = this->currentTime - this->stateStartTime; 
	// Serial.println(this->stateTime); 
	// if(this->stateTime < 2000){
	// 	servo.writeMicroseconds(1200); 
	// 	Serial.println("Servo Values"); 
	// 	Serial.println(analogRead(PARACHUTE_SERVO_1_IN)); 
	// }
	// servo.writeMicroseconds(1500); 

	Serial.println(analogRead(20)); 
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
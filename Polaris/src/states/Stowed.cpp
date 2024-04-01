#include "Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}


void Stowed::initialize_impl() {
	this->stateStartTime = this->currentTime; 
	this->servo.attach(PARACHUTE_SERVO_4); 
	//servo.writeMicroseconds(1493); 
}

//Testing
int total1 = 0,
    total2 = 0,
    total3 = 0,
    total4 = 0;

void Stowed::loop_impl() { //Shouldn't need anything in here 

	this->stateTime = this->currentTime - this->stateStartTime; 
	// Serial.println(analogRead(PARACHUTE_SERVO_4_IN));
	if (this->stateTime > 1.0) {
		total1 += analogRead(PARACHUTE_SERVO_1_IN);
		total2 += analogRead(PARACHUTE_SERVO_2_IN);
		total3 += analogRead(PARACHUTE_SERVO_3_IN);
		total4 += analogRead(PARACHUTE_SERVO_4_IN);
	}
	// if (loopCount % 101 == 0) { // Show averages every 101 (prime) loops
	// 	// Serial.printf("Avg  |      1 |      2 |      3 |      4 |\n     | %6.0f | %6.0f | %6.0f | %6.0f |\n",
	// 	// 	((float) total1) / loopCount,
	// 	// 	((float) total2) / loopCount,
	// 	// 	((float) total3) / loopCount,
	// 	// 	((float) total4) / loopCount
	// 	// );
	// }
	Serial.printf("Curr |      1 |      2 |      3 |      4 |\n     | %6d | %6d | %6d | %6d |\n",
		analogRead(PARACHUTE_SERVO_1_IN),
		analogRead(PARACHUTE_SERVO_2_IN),
		analogRead(PARACHUTE_SERVO_3_IN),
		analogRead(PARACHUTE_SERVO_4_IN)
	);


	// if(this->stateTime < 1000){
	// 	servo.writeMicroseconds(1100); 	
	// }
	// else{
	// 	servo.writeMicroseconds(1493); 
	// }	
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
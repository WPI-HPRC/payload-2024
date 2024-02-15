#include "State.h"
#include <Arduino.h>

void State::initialize() {
	this->startTime = millis();
	initialize_impl();

	// for z acceleration
	float transitionBufAcc[10];
    uint8_t transitionBufIndAcc = 0;

	// for vertical velocity
	int16_t transitionBufVelVert[10];
    uint8_t transitionBufIndVelVert = 0;

	// Altitude buffer
	int16_t transitionBufAlt[10];
	uint8_t transitionBufIndAlt = 0;
	int16_t altitudePreviousAvg;
}

void State::loop() {
	long long now = millis();
	this->currentTime = now - this->startTime;
	this->deltaTime = now - this->lastLoopTime;
	loop_impl();
	this->lastLoopTime = millis();
}

State *State::nextState() {
	return nextState_impl();
}


// put sensor code here

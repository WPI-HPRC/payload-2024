#include <Arduino.h>
#include <Metro.h>

#include <SPI.h>
#include <Wire.h>

#include <states/State.h>
#include <states/PreLaunch.h>
#include "libs/Flash/Flash.h"
#include "utility.hpp"
#include <Controls/EKF/EKF.h>
#include <OpenMV/camera.h>

// #include <TeensyDebug.h>
// #pragma GCC optimize ("O0")

#include <typeinfo>

SensorFrame sensorFrame;

FlashChip *flash = new FlashChip();
StateEstimator *stateEstimator = nullptr; 
XbeeProSX *xbee = new XbeeProSX(17); // CS GPIO17
Utility::Servos *servos; 
OpenMV *openMV = new OpenMV(); 


unsigned long previousTime = 0;
unsigned long currentTime = 0;
uint32_t counter = 0;

Metro timer = Metro(1000/ LOOP_RATE);

State * state;

Sensorboard sensorBoard;

void setup() {
	Serial.begin(115200);

	while(!Serial);
	Wire.begin();
	Wire.setClock(400000);

	Serial.println("[Polaris] Initializing Sensor Board");
	if(sensorBoard.setup()) {
		Serial.println("[Polaris] Sensor Setup Complete!");
	} else {
		Serial.println("[Polaris] Sensor Setup Failed!");
		while(1) {};
	}

	state = new PreLaunch(flash, stateEstimator, xbee, servos, openMV);

	state->initialize();

	flash->init();
	// int startAddress = 0;
	// startAddress = flash.rememberAddress();
	// Serial.println("Starting Flash Chip At Address: " + String(startAddress));

	currentTime = millis();
	previousTime = millis();
};

void readSensors() {
	sensorBoard.readInertialSensors();
	memcpy(&sensorFrame, &sensorBoard.Inertial_Baro_frame, sizeof(sensorBoard.Inertial_Baro_frame));
};

void loop() {
	if(timer.check() == 1) {
		readSensors();

		memcpy(&state->sensorData, &sensorFrame, sizeof(sensorFrame));

		state->loop();

		String timestamp = (String) millis();

		// Check for state transition each loop
		State *nextState = state->nextState();

		if(nextState != nullptr) {
			Serial.print("State Change Detected: ");
			state = nextState;

			state->initialize();
		};
	};
};
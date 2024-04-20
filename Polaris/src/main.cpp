#include <Arduino.h>
#include <Metro.h>

#include <SPI.h>
#include <Wire.h>

#include <states/State.h>
#include <states/00-PreLaunch.h>
#include "libs/Flash/Flash.h"
#include "utility.hpp"
#include <Servo.h>
#include <SensorBoardLibraries/Sensor_Frames.hpp>
#include <SensorBoardLibraries/SensorBoard.hpp>

// #include <TeensyDebug.h>
// #pragma GCC optimize ("O0")

#include <typeinfo>

SensorFrame sensorFrame;

FlashChip flash = FlashChip();
Servo airbrakesServo = Servo();

unsigned long previousTime = 0; //still need these? 
unsigned long currentTime = 0;
uint32_t counter = 0;

Metro timer = Metro(1000/ LOOP_RATE);

State *state = new PreLaunch();

Sensorboard sensorBoard;

void setup() {
	Serial.begin(115200);

	while(!Serial); //Double check this- should be ok
	Wire.begin();
	Wire.setClock(400000);

	pinMode(SERVO_FEEDBACK_GPIO, INPUT);
    Serial.println(airbrakesServo.attach(SERVO_PWM_GPIO));
    airbrakesServo.write(AIRBRAKE_RETRACTED);

	Serial.println("[Polaris] Initializing Sensor Board"); //Make sure GPS is off (should be)
	if(sensorBoard.setup()) {
		Serial.println("[Polaris] Sensor Setup Complete!");
	} else {
		Serial.println("[Polaris] Sensor Setup Failed!");
		while(1) {};
	}

	flash.init();
	int startAddress = 0;
	startAddress = flash.rememberAddress();
	Serial.println("Starting Flash Chip At Address: " + String(startAddress));

	state->initialize();

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

		String timestamp = (String) millis();
	
		state->loop();

		// Check for state transition each loop
		State *nextState = state->nextState();

		if(nextState != nullptr) {
			Serial.print("State Change Detected: ");
			state = nextState;
			state->initialize();
		};
	};
};
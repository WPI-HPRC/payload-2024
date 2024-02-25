#include "State.h"
#include <Arduino.h>
State::State(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos), openMV(openMV){}
void State::initialize() {
	this->startTime = millis();
	initialize_impl();
	xbee->begin();
    BLA::Matrix<10> x_0 = {1,0,0,0,0,0,0,0,0,0};
    stateEstimator = new StateEstimator(x_0, 0.025); 
}

void State::loop() {
	long long now = millis();
	this->currentTime = now - this->startTime;
	this->deltaTime = now - this->lastLoopTime;
	this->loopCount++;
	loop_impl();
	this->lastLoopTime = millis();
	//Sensor stuff here 
	this->currentState = stateEstimator->onLoop(sensorData); //THis is sus, check pointers and such (tomorrow)
 
    
	this->telemPacket.state = this->getId();
    telemPacket.accelX = sensorData.ac_x; 
    telemPacket.accelY = sensorData.ac_y;
    telemPacket.accelZ = sensorData.ac_z;

 

    telemPacket.gyroX = sensorData.gy_x;
    telemPacket.gyroY = sensorData.gy_y;
    telemPacket.gyroZ = sensorData.gy_z;

    telemPacket.magX = sensorData.mag_x;
    telemPacket.magY = sensorData.mag_y;
    telemPacket.magZ = sensorData.mag_z;

    telemPacket.pressure = sensorData.Pressure;
    telemPacket.altitude = Utility::pressureToAltitude(sensorData.Pressure);
    telemPacket.timestamp = this->currentTime;
    telemPacket.w = currentState(0);
    telemPacket.i = currentState(1);
    telemPacket.j = currentState(2);
    telemPacket.k = currentState(3);
	telemPacket.posX = 0.0; 
	telemPacket.posY = 0.0;
	telemPacket.posZ = 0.0;
	telemPacket.velX = 0.0; 
	telemPacket.velY = 0.0;
	telemPacket.velZ = 0.0;
   

	telemPacket.gpsLat = sensorData.gpsLat; //Make sure consistent, look at Pre-launch 
    telemPacket.gpsLong = sensorData.gpsLong;
    telemPacket.gpsAltMSL = sensorData.gpsAltMSL;
	telemPacket.gpsAltAGL = sensorData.gpsAltAGL;
	//telemPacket.epochTime = sensorData.epochTime;
	telemPacket.satellites = sensorData.satellites;
	telemPacket.gpsLock = sensorData.gpsLock;
    
    this->camGPS = openMV->onLoop(telemPacket, data); 

	//Deal with these once objects are defined 
	telemPacket.cx = data.cx; //Camera Centroids  
    telemPacket.cy = data.cy;
     

    telemPacket.targetGpsLat = this->camGPS.lat; //Target Point GPS Estimations
    telemPacket.targetGpsLong = this->camGPS.lon;
    
    //Controls 
    telemPacket.desiredServoPos1 = MAX_SERVO_POS; 
    telemPacket.actualServoPos1 = this->servos->paraServo_1->readServo(); //IDK if this works...
    telemPacket.desiredServoPos2 = MAX_SERVO_POS; 
    telemPacket.actualServoPos2 = this->servos->paraServo_2->readServo();
    telemPacket.desiredServoPos3 = MAX_SERVO_POS; 
    telemPacket.actualServoPos3 = this->servos->paraServo_3->readServo();
    telemPacket.desiredServoPos4 = MAX_SERVO_POS;  
    telemPacket.actualServoPos4 = this->servos->paraServo_4->readServo(); 


    // float trajA = 0.0f; //Calculated Trajectory Constants 
    // float trajB = 0.0f;
    // float trajC = 0.0f;
    // float trajD = 0.0f; 

	xbee->send(0x0013A200423F474C, &telemPacket, sizeof(telemPacket));
	Utility::logData(flash, telemPacket); 
    

    Serial.print("Packet Success: ");
    Serial.println(millis());

}

State *State::nextState() {
	return nextState_impl();
}


// put sensor code here

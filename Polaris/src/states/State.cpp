#include "State.h"
#include <Arduino.h>
#include "utility.hpp"
#include <SD.h>

State::State(Sensorboard *sensors, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : sensors(sensors), attitudeStateEstimator(attitudeStateEstimator), xbee(xbee), servos(servos), openMV(openMV){}


void State::initialize() {
	this->startTime = millis();
	initialize_impl();
	//xbee->begin();
    BLA::Matrix<10> x_0 = {1,0,0,0,0,0,0,0,0,0};
    // stateEstimator = new StateEstimator(x_0, 0.025);
    // I am unaware if there is an AttitudeStateEstimator equivalent to this that should be used Oct 7 2024
}

void State::loop() {
	long long now = millis();
	this->currentTime = now - this->startTime;
	this->deltaTime = now - this->lastLoopTime;
	this->loopCount++;
	
    this->sensors->readInertialSensors();

	this->lastLoopTime = millis();
	//Sensor stuff here 
	//this->currentState = stateEstimator->onLoop(sensorData); //THis is sus, check pointers and such (tomorrow)
    //Once again- unsure if there is an AttitudeStateEstimator equivalent which should be used Oct 7 2024
    
	this->telemPacket.state = this->getId();
    this->telemPacket.accelX = this->sensors->Inertial_Baro_frame.ac_x;
    this->telemPacket.accelY = this->sensors->Inertial_Baro_frame.ac_y;
    this->telemPacket.accelZ = this->sensors->Inertial_Baro_frame.ac_z;

    this->telemPacket.gyroX = this->sensors->Inertial_Baro_frame.gy_x;
    this->telemPacket.gyroY = this->sensors->Inertial_Baro_frame.gy_y;
    this->telemPacket.gyroZ = this->sensors->Inertial_Baro_frame.gy_z;

    this->telemPacket.magX = this->sensors->Inertial_Baro_frame.mag_x;
    this->telemPacket.magY = this->sensors->Inertial_Baro_frame.mag_y;
    this->telemPacket.magZ = this->sensors->Inertial_Baro_frame.mag_z;

    this->telemPacket.pressure = this->sensors->Inertial_Baro_frame.Pressure;
    this->telemPacket.temperature = this->sensors->Inertial_Baro_frame.Temperature;
    this->telemPacket.altitude = Utility::pressureToAltitude(this->telemPacket.pressure);
    this->telemPacket.initialAltitude = initialAltitude;

    this->telemPacket.gpsLat = this->sensors->Inertial_Baro_frame.gpsLat;
    this->telemPacket.gpsLong = this->sensors->Inertial_Baro_frame.gpsLong;
    this->telemPacket.gpsLock = this->sensors->Inertial_Baro_frame.gpsLock;
    this->telemPacket.satellites = this->sensors->Inertial_Baro_frame.satellites;

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

    this->telemPacket.loopCount = this->loopCount;
    this->telemPacket.timestamp = now;

    //this->camGPS = openMV->onLoop(telemPacket, data); 

	//Deal with these once objects are defined 
	// telemPacket.cx = data.cx; //Camera Centroids  
    // telemPacket.cy = data.cy;
    telemPacket.cx = 0; //Camera Centroids  
    telemPacket.cy = 0;
    // Serial.println(telemPacket.cx); 
    // Serial.println(telemPacket.cy); 

    // telemPacket.targetGpsLat = this->camGPS.lat; //Target Point GPS Estimations
    // telemPacket.targetGpsLong = this->camGPS.lon;
    telemPacket.targetGpsLat = 0.0; //Target Point GPS Estimations
    telemPacket.targetGpsLong = 0.0;
    
    //Controls 
    telemPacket.desiredServoPos1 = MAX_SERVO_POS; 
    telemPacket.actualServoPos1 = this->servos->paraServo_1->readServo(); //IDK if this works...
    telemPacket.desiredServoPos2 = MAX_SERVO_POS; 
    telemPacket.actualServoPos2 = this->servos->paraServo_2->readServo();
    telemPacket.desiredServoPos3 = MAX_SERVO_POS; 
    telemPacket.actualServoPos3 = this->servos->paraServo_3->readServo();
    telemPacket.desiredServoPos4 = MAX_SERVO_POS;  
    telemPacket.actualServoPos4 = this->servos->paraServo_4->readServo(); 

    static const BLA::Matrix<3, 3> softIronCal = {
        1.120602,
        -0.003242,
        0.005510,
        -0.003242,
        1.143276,
        0.013794,
        0.005510,
        0.013794,
        1.104641,
    };

    static const BLA::Matrix<3> hardIronCal = {54062.849827, 5545.343210, 89181.770655};

    BLA::Matrix<3> magVector = {telemPacket.magX, telemPacket.magY, telemPacket.magZ};

    BLA::Matrix<3> magCal = softIronCal * (magVector - hardIronCal);

    this->telemPacket.magX = magCal(0);
    this->telemPacket.magY = magCal(1);
    this->telemPacket.magZ = magCal(2);

    if (this->attitudeStateEstimator->initialized)
    {
        this->attitudeStateEstimator->onLoop(this->telemPacket);
        this->telemPacket.w = this->attitudeStateEstimator->x(0);
        this->telemPacket.i = this->attitudeStateEstimator->x(1);
        this->telemPacket.j = this->attitudeStateEstimator->x(2);
        this->telemPacket.k = this->attitudeStateEstimator->x(3);
    }
    loop_impl();
    this->lastLoopTime = now;
    
    // float trajA = 0.0f; //Calculated Trajectory Constants 
    // float trajB = 0.0f;
    // float trajC = 0.0f;
    // float trajD = 0.0f; 
    #ifndef NO_XBEE
    if (loopCount % 5 == 0)
    {
        SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
        xbee->sendTransmitRequestCommand(0x0013A200423F474C, (uint8_t *)&telemPacket, sizeof(telemPacket));
        SPI.endTransaction();
    }
    #endif

    // char* testPacket = "PLEASE JUST WORK AHGGGGGGAHHDH"; 
    // xbee->send(0x0013A200423F474C, &testPacket, sizeof(testPacket));

    #ifndef NO_SDCARD
    if (sdCardInitialized)
    {
        dataFile.write((uint8_t *)&this->telemPacket, sizeof(this->telemPacket));
        if (this->loopCount % 20 == 0)
        {
            dataFile.flush();
        }
    }   
    #endif 

}

State *State::nextState() {
    #ifndef NO_TRANSITION
	    return nextState_impl();
    #else
        return nullptr;
    #endif
}


// put sensor code here

#pragma once
#include "FlightParams.hpp"
#include <ServoControls/ServoController.h>

// #define DEBUG_MODE 
#define LOOP_RATE 40

class Utility
{
public:
    static float pressureToAltitude(float pressure)
    {
        // physical parameters for model
        const float pb = 101325;   // [Pa] pressure at sea level
        const float Tb = 288.15;   // [K] temperature at seal level
        const float Lb = -0.0065;  // [K/m] standard temperature lapse rate
        const float hb = 0;        // [m] height at bottom of atmospheric layer (sea level)
        const float R = 8.31432;   // [N*m/mol*K] universal gas constant
        const float g0 = 9.80665;  // [m/s^2] Earth standard gravity
        const float M = 0.0289644; // [kg/mol] molar mass of Earth's air

        // convert pressure from [hPa] to [Pa]
        float pressure_Pa = pressure * 100;

        // compute altitude from formula
        return hb + (Tb / Lb) * (pow((pressure_Pa / pb), (-R * Lb / (g0 * M))) - 1);
    };


    #pragma pack(push,1)
    struct TelemPacket {

	    // State Integer
        // 0 - PreLaunch
        // 1 - Stowed
        // 2 - Freefall
        // 3 - WindLeft
        // 4 - HoldLeft
        // 5 - WindRight
	    // 6 - HoldRight
	    // 7 - LandPrep
	    // 8 - Recovery 
        // 9 - Abort
        uint8_t state;

        // Raw Sensor Readings
        float accelX = 0.0f;
        float accelY = 0.0f;
        float accelZ = 0.0f;
        float gyroX = 0.0f;
        float gyroY = 0.0f;
        float gyroZ = 0.0f;
        float magX = 0.0f;
        float magY = 0.0f;
        float magZ = 0.0f;
        float pressure = 0.0f;

        // Calculated Values
        float altitude = 0.0f;

        // EKF Results
        float w = 0.0f; // Quaternion State
        float i = 0.0f;
        float j = 0.0f;
        float k = 0.0f;
        float posX = 0.0f; // Position State ECEF
        float posY = 0.0f;
        float posZ = 0.0f;
        float velX = 0.0f; // Velocity State ECEF
        float velY = 0.0f;
        float velZ = 0.0f;

        // GPS Inputs
        float gpsLat = 0.0f;
        float gpsLong = 0.0f;
        float gpsAltMSL = 0.0f;
        float gpsAltAGL = 0.0f;
        uint32_t epochTime = 0;
        uint8_t satellites = 0;
        boolean gpsLock = false;

        uint32_t timestamp = 0;

        //Payload Specific 

        //CV 
        uint32_t cx = 0; //Camera Centroids 
        uint32_t cy = 0;

        float targetGpsLat = 0.0f; //Target Point GPS Estimations
        float targetGpsLong = 0.0f;

        //Controls 
        uint32_t desiredServoPos1 = 0; //Servo Controls Values 
        uint32_t actualServoPos1 = 0;
        uint32_t desiredServoPos2 = 0; //Servo Controls Values 
        uint32_t actualServoPos2 = 0;
        uint32_t desiredServoPos3 = 0; //Servo Controls Values 
        uint32_t actualServoPos3 = 0;
        uint32_t desiredServoPos4 = 0; //Servo Controls Values 
        uint32_t actualServoPos4 = 0;

        float trajA = 0.0f; //Calculated Trajectory Constants 
        float trajB = 0.0f;
        float trajC = 0.0f;
        float trajD = 0.0f; 
    }; 
    #pragma pack(pop)

    struct Servos{
        ServoController paraServo_1 = new ServoController(PARACHUTE_SERVO_1, PARACHUTE_SERVO_1_DIR, SERVO_GAIN, PULLEY_D, STRING_BASE_LENGTH); //double check direction
        ServoController paraServo_2 = new ServoController(PARACHUTE_SERVO_2, PARACHUTE_SERVO_2_DIR, SERVO_GAIN, PULLEY_D, STRING_BASE_LENGTH); //double check direction
        ServoController paraServo_3 = new ServoController(PARACHUTE_SERVO_3, PARACHUTE_SERVO_3_DIR, SERVO_GAIN, PULLEY_D, STRING_BASE_LENGTH); //double check direction
        ServoController paraServo_4 = new ServoController(PARACHUTE_SERVO_4, PARACHUTE_SERVO_4_DIR, SERVO_GAIN, PULLEY_D, STRING_BASE_LENGTH); //double check direction
    }


    static void logData(FlashChip *flash, TelemPacket telemPacket) //Need to fix to be Polaris Variables 
    {
        String structString = String(telemPacket.accelX) + "," +
                              String(telemPacket.accelY) + "," +
                              String(telemPacket.accelZ) + "," +
                              String(telemPacket.gyroX) + "," +
                              String(telemPacket.gyroY) + "," +
                              String(telemPacket.gyroZ) + "," +
                              String(telemPacket.magX) + "," +
                              String(telemPacket.magY) + "," +
                              String(telemPacket.magZ) + "," +
                              String(telemPacket.pressure) + "," +
                              String(telemPacket.altitude) + "," +
                              String(telemPacket.q) + "," +
                              String(telemPacket.i) + "," +
                              String(telemPacket.j) + "," +
                              String(telemPacket.k) + "," +
                              String(telemPacket.X) + "," +
                              String(telemPacket.Y) + "," +
                              String(telemPacket.Z) + "," + //No Position??
                              String(telemPacket.gpsLat) + "," +
                              String(telemPacket.gpsLong) + "," +
                              String(telemPacket.gpsAltMSL) + "," +
                              String(telemPacket.gpsAltAGL) + "," +
                              String(telemPacket.gpsLock) + "," +
                              String(telemPacket.satellites) + "," +
                              String(telemPacket.timestamp) + "," +
                              String(telemPacket.cx) + "," +
                              String(telemPacket.cy) + "," +
                              String(telemPacket.targetGpsLat) + "," +
                              String(telemPacket.targetGpsLong) + "," +
                              String(telemPacket.desiredServoPos) + "," +
                              String(telemPacket.trajA) + "," +
                              String(telemPacket.trajB) + "," +
                              String(telemPacket.trajC) + "," +
                              String(telemPacket.trajD); 
                              

        flash->writeStruct(structString);
    }


    // WGS84 Ellipsoid Model
    constexpr static float a_earth = 6378137.0;       // [m] Semi-major axis of Earth
    constexpr static float b_earth = 6356752.3142;    // [m] Semi-Minor axis of Earth
    constexpr static float e_earth = 0.0818191908426; // Eccentricity of Earth
    constexpr static float r_earth = 6378137; // [m] Radius of Earth
};

#include <cstdint>

#pragma pack(push, 1)
struct TelemPacket {

        uint8_t packetType = 0x02;

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
        bool gpsLock = false;

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
        uint32_t desiredServoPos2 = 0; 
        uint32_t actualServoPos2 = 0;
        uint32_t desiredServoPos3 = 0; 
        uint32_t actualServoPos3 = 0;
        uint32_t desiredServoPos4 = 0; 
        uint32_t actualServoPos4 = 0;

        float trajA = 0.0f; //Calculated Trajectory Constants 
        float trajB = 0.0f;
        float trajC = 0.0f;
        float trajD = 0.0f; 

        uint32_t loopCount = 0;
    }; 
    #pragma pack(pop)
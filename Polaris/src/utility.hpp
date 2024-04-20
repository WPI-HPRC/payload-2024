#pragma once
#include "FlightParams.hpp"
#include <libs/Flash/Flash.h>
#include <Servo.h>

// #define DEBUG_MODE 
#define LOOP_RATE 40

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define SERVO_FEEDBACK_GPIO 20
#define SERVO_PWM_GPIO 6

extern Servo airbrakesServo;
extern FlashChip flash; 

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
        // 1 - Launch
        // 2 - Coast
        // 3 - DrogueDescent
        // 4 - MainDescent
        // 5 - Recovery
        // 6 - Abort
        uint8_t state = 0;

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

        uint32_t servoPosition = 0;

        // Calculated Values
        float altitude = 0.0f;

        uint32_t timestamp = 0;
    }; 
    #pragma pack(pop) 


    static void logData(FlashChip flash, TelemPacket telemPacket) //Need to fix to be Polaris Variables 
    {
        String structString = String(telemPacket.accelX) + "," + //Need to add in state lol
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
                              String(telemPacket.servoPosition); 
                              
        flash.writeStruct(structString);
        //Serial.println(structString.length()); 
        //Serial.println(structString); 
    }

    // WGS84 Ellipsoid Model
    constexpr static float a_earth = 6378137.0;       // [m] Semi-major axis of Earth
    constexpr static float b_earth = 6356752.3142;    // [m] Semi-Minor axis of Earth
    constexpr static float e_earth = 0.0818191908426; // Eccentricity of Earth
    constexpr static float r_earth = 6378137; // [m] Radius of Earth
};

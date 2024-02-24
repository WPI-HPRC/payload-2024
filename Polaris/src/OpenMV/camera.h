//Code Adapted from RBE 2002 D23 Repository 

#ifndef __CAMERA_H
#define __CAMERA_H

#include <Arduino.h>
#include <Wire.h>

#define CAMERA_I2C_ADDRESS 0x12 
//Properties of the Image
#define CAMERA_FOV_VERTICAL 55.6
#define CAMERA_FOV_HORIZONTAL 70.8
#define CAMERA_RESOLUTION_X 160
#define CAMERA_RESOLUTION_Y 120
//Meters to Longitude and Latitude
#define METERS_TO_LATITUDE 1.0 / 111111.0
//Degrees to Radians
#define DEGREES_TO_RADIANS 3.14159265358979323846/180.0

#include <OpenMV/cameraData.h>
#include <OpenMV/gps.h>
#include <SensorBoardLibraries/Sensor_Frames.hpp>
#include "utility.hpp"

class Camera {};

class OpenMV : public Camera
{
protected:
    uint8_t mvArray[sizeof(CameraData)]; //array for receiving data from the OpenMV cam
    uint8_t mvIndex = 0; //for counting bytes

public:
    OpenMV(); 
    bool readData(CameraData& data); 

    //add functions for GPS point Calcs 
    GPSPoint getTargetPoint(CameraData& data, float currLat, float currLong, float alt, float anglePitch, float heading); 
    GPSPoint onLoop(Utility::TelemPacket sensorPacket, CameraData& data); 
    // Trajectory getReferenceTrajectory(GPSPoint targetPoint, GPSPoint payloadPos); 
};

#endif

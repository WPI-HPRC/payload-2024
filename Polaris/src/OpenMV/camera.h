//Code Adapted from RBE 2002 D23 Repository 

#ifndef __CAMERA_H
#define __CAMERA_H

#include <Arduino.h>
#include <Wire.h>

#define CAMERA_I2C_ADDRESS 0x12 

#include <OpenMV/cameraData.h>
#include <OpenMV/gps.h>

class Camera {};

class OpenMV : public Camera
{
protected:
    uint8_t mvArray[sizeof(CameraData)]; //array for receiving data from the OpenMV cam
    uint8_t mvIndex = 0; //for counting bytes

public:
    uint8_t getData(void);
    bool readData(CameraData& data);

    bool checkUART(CameraData& data);
    bool handleUART(uint8_t b);

    //add functions for GPS point Calcs 
    GPSPoint getTargetPoint(CameraData& data, float currLat, float currLong, float alt); 
    // Trajectory getReferenceTrajectory(GPSPoint targetPoint, GPSPoint payloadPos); 
};

#endif

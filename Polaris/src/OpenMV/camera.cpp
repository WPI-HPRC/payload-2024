//Code Adapted from RBE 2002 D23 Repository 
#include "OpenMV/camera.h"
#include "OpenMV/cameraData.h"

//cx then cy
bool OpenMV::readData(CameraData& data)
{
    bool retVal = false;

    delayMicroseconds(250); //may need to delete this depending on speed requirements 

    uint8_t buffer[sizeof(CameraData)];
    //use some explicit casts to suppress warnings
    if (Wire.requestFrom(CAMERA_I2C_ADDRESS, (int)sizeof(CameraData), true) == sizeof(CameraData))
    {
        for(uint8_t i = 0; i < sizeof(CameraData); i++) buffer[i] = Wire.read();
        memcpy(&data, buffer, sizeof(CameraData));
        
        //TODO: add basic error checking, including checksum

        retVal = true;
    }
    return retVal;
}

GPSPoint OpenMV::getTargetPoint(struct CameraData &data, float currLat, float currLong, float alt, float anglePitch, float heading){

    GPSPoint point;
    //CHANGE ALL OF THIS SO THAT 0º IS DIRECTLY UPWARDS OPPOSED TO GRAVITY
    int16_t cx = data.cx;
    int16_t cy = data.cy;

   //Distance Calculations 
    float degreePerPixelVertical =  CAMERA_FOV_VERTICAL / CAMERA_RESOLUTION_Y;
    float degreePerPixelHorizontal =  CAMERA_FOV_HORIZONTAL / CAMERA_RESOLUTION_X;

    float pixelVerticalDegrees = (cy * degreePerPixelVertical) - (CAMERA_FOV_VERTICAL/2);
    float pixelHorizontalDegrees = (cx * degreePerPixelHorizontal) - (CAMERA_FOV_HORIZONTAL/2);

    float pixelVerticalRadians = pixelVerticalDegrees * DEGREES_TO_RADIANS;
    float pixelHorizontalRadians = pixelHorizontalDegrees * DEGREES_TO_RADIANS;
    
    // Add in quaternion angle orientation
    float anglePitchRadians = anglePitch * DEGREES_TO_RADIANS; 

    //This is the relative distance from the camera in meters
    float forwardY = tan(anglePitchRadians + pixelVerticalRadians) * alt; //Pitch is a factor in this calculation because it would be rotational around the camera's y axis
    float deflectionX = tan(pixelHorizontalRadians) * alt; //Roll shouldn't be a factor in this calculation, yaw would but we factor it in later

    //This is for the conversion of the relative distance to the absolute distance

    //The conversion angle is the angle from true north to point the camera has targeted
    float conversionAngle = pixelHorizontalRadians + (heading * DEGREES_TO_RADIANS);
    //The magnitude is solving for the hypotenuse of the triangle that is the distance from the camera to the target
    float magnitude = sqrt(pow(deflectionX,2.0)+pow(forwardY,2.0));
    //Then we scale this down by the easy conversion to Long/Lat based on the fact that 1 degree of latitude is 111,111 meters
    float Ycomponent = cos(conversionAngle) * magnitude;
    float Xcomponent = sin(conversionAngle) * magnitude;
    //Now we can scale by long and latitude
    float targetLatitude = Ycomponent * METERS_TO_LATITUDE;
    //This should be the target latitude based on the target latitude and the current latitude
    point.lat = targetLatitude + currLat;
    //This should be the target longitude based on the updated target latitude
    float targetLongitude = Xcomponent * METERS_TO_LATITUDE / cos(point.lon * DEGREES_TO_RADIANS);
    point.lon = targetLongitude + currLong;

    return point;   
}
//Code Adapted from RBE 2002 D23 Repository 
#include "OpenMV/camera.h"

uint8_t OpenMV::getData(void)
{
    uint8_t dataCount = 0;

    delayMicroseconds(100); //may need to delete this depending on speed requirements 

    if (Wire.requestFrom(CAMERA_I2C_ADDRESS, (uint8_t)1, true) == 1) dataCount = Wire.read(); //need to double check byte size of data being sent over 

    return dataCount;
}

bool OpenMV::readData(CameraData& data)
{
    bool retVal = false;

    //Wire.begin();
    //Wire.setClock(100000ul);

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

//UART, need to look at bytes sent and stuff in the python folder, but will prob use i2c anyways

bool OpenMV::checkUART(CameraData& tag)  
{
  bool retVal = false;
  while(Serial1.available())
  {
    uint8_t b = Serial1.read();
    if(handleUART(b))
    {
      memcpy(&tag, &mvArray, 16);
      retVal = true;
    }
  }

  return retVal;
}

bool OpenMV::handleUART(uint8_t b)
{
  bool retVal = false;
  switch(mvIndex)
  {
    case 0:
      if(b == 0xff) mvIndex++; //first byte must be 0xff
      break;
    case 1:
      if(b == 0x55) mvIndex++;
      else mvIndex = 0; //didn't get the 0x55 byte, so restart
      break;
    case 16:
      if(b == 0xaa) //correct end byte, so process
      {
        retVal = true;
        mvIndex = 0;
      } 
      else mvIndex = 0; //didn't get the aa byte, so restart
      break;
    case 17:
      Serial.println("Something is very wrong!"); //PANIC
      break;
    default:
      mvArray[mvIndex++] = b;
  }

  //TODO: add checksum verification

  return retVal;
}

GPSPoint OpenMV::getTargetPoint(CameraData &data, float currLat, float currLong, float alt){

    GPSPoint point;
    
    float distLat = 0;
    float distLong = 0;

    float angleroll = data.angleroll;
    float anglepitch = data.anglepitch;
    int16_t cx = data.cx;
    int16_t cy = data.cy;

   //Distance Calculations 
    float degreePerPixelVertical =  CAMERA_FOV_VERTICAL / CAMERA_RESOLUTION_Y;
    float degreePerPixelHorizontal =  CAMERA_FOV_HORIZONTAL / CAMERA_RESOLUTION_X;

    float pixelVerticalDegrees = (cy * degreePerPixelVertical) - (CAMERA_FOV_VERTICAL/2);
    float pixelHorizontalDegrees = (cx * degreePerPixelHorizontal) - (CAMERA_FOV_HORIZONTAL/2);

    float pixelVerticalRadians = pixelVerticalDegrees * DEGREES_TO_RADIANS;
    float pixelHorizontalRadians = pixelHorizontalDegrees * DEGREES_TO_RADIANS;
    //This is the relative distance from the camera in meters
    float forwardY = tan(anglepitch + pixelVerticalRadians) * alt; //Pitch is a factor in this calculation because it would be rotational around the camera's y axis
    float deflectionX = tan(pixelHorizontalRadians) * alt; //Roll shouldn't be a factor in this calculation, yaw would but we factor it in later

    //This is for the conversion of the relative distance to the absolute distance

    //The conversion angle is the angle from true north to point the camera has targeted
    float conversionAngle = pixelHorizontal + heading;
    //The magnitude is solving for the hypotenuse of the triangle that is the distance from the camera to the target
    float magnitude = sqrt(pow(deflectionX,2.0)+pow(forwardY,2.0));
    //Then we scale this down by the easy conversion to Long/Lat based on the fact that 1 degree of latitude is 111,111 meters
    float Ycomponent = cos(conversionAngle) * magnitude;
    float Xcomponent = sin(conversionAngle) * magnitude;
    //Now we can scale by long and latitude
    float targetLatitude = Ycomponent * METERS_TO_LATITUDE;
    //This should be the target latitude based on the target latitude and the current latitude
    point.latitude = targetLatitude + currLat;
    //This should be the target longitude based on the updated target latitude
    float targetLongitude = Xcomponent * METERS_TO_LATITUDE / cos(point.latitude * DEGREES_TO_RADIANS);
    point.longitude = targetLongitude + currLong;

    return point;   
}



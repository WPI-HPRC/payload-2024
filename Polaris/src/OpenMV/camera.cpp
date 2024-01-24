//Code Adapted from RBE 2002 D23 Repository 
#include <OpenMV/camera.h>

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
    
}



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

    #pragma pack(push,1)
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
        float temperature = 0.0f;

        // Calculated Values
        float altitude = 0.0f;
        float initialAltitude = 0.0f;

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

        uint32_t loopCount = 0;
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
    }; 
    #pragma pack(pop)

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Provide a file to read data from\n");
    return -1;
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "failed to open file %s\n", argv[1]);
    return -1;
  }

  uint8_t buf[sizeof(struct TelemPacket)];
  struct TelemPacket packet;

  printf("state,accelX,accelY,accelZ,gyroX,gyroY,gyroZ,magX,magY,magZ,pressure,temperature,altitude,initialAltitude,w,i,j,k,posX,posY,posZ,velX,velY,velZ,gpsLat,gpsLong,gpsAltMSL,gpsAltAGL,epochTime,satellites,gpsLock,loopCount,timestamp,covQW,covQX,covQY,covQZ,drogue,main\n");
  while (fread(buf, sizeof(struct TelemPacket), 1, file)) {
    packet = *(struct TelemPacket *)buf;
    printf("%hhd,", packet.state);
    printf("%f,", packet.accelX);
    printf("%f,", packet.accelY);
    printf("%f,", packet.accelZ);
    printf("%f,", packet.gyroX);
    printf("%f,", packet.gyroY);
    printf("%f,", packet.gyroZ);
    printf("%f,", packet.magX);
    printf("%f,", packet.magY);
    printf("%f,", packet.magZ);
    printf("%f,", packet.pressure);
    printf("%f,", packet.temperature);
    printf("%f,", packet.altitude);
    printf("%f,", packet.initialAltitude);
    printf("%f,", packet.w);
    printf("%f,", packet.i);
    printf("%f,", packet.j);
    printf("%f,", packet.k);
    printf("%f,", packet.posX);
    printf("%f,", packet.posY);
    printf("%f,", packet.posZ);
    printf("%f,", packet.velX);
    printf("%f,", packet.velY);
    printf("%f,", packet.velZ);
    printf("%f,", packet.gpsLat);
    printf("%f,", packet.gpsLong);
    printf("%f,", packet.gpsAltMSL);
    printf("%f,", packet.gpsAltAGL);
    printf("%d,", packet.epochTime);
    printf("%hhd,", packet.satellites);
    printf("%hhd,", packet.gpsLock);
    printf("%d,", packet.loopCount);
    printf("%d,", packet.timestamp);
    printf("%du,", packet.cx);
    printf("%du,", packet.cy);
    printf("%f,", packet.targetGpsLat);
    printf("%f,", packet.targetGpsLong);
    printf("%du,", packet.desiredServoPos1);
    printf("%du,", packet.actualServoPos1);
    printf("%du,", packet.desiredServoPos2 );
    printf("%du,", packet.actualServoPos2);
    printf("%du,", packet.desiredServoPos3 );
    printf("%du,", packet.actualServoPos3);
    printf("%du,", packet.desiredServoPos4 );
    printf("%du,", packet.actualServoPos4);
    printf("%f,", packet.trajA);
    printf("%f,", packet.trajB);
    printf("%f,", packet.trajC);
    printf("%f\n", packet.trajD);
  }
  return 0;
}

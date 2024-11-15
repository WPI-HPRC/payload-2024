#include <Controls/EKF/EKF.h>
#include "FlightParams.hpp"
#include "SpiDriver/SdSpiDriver.h"
#include <Arduino.h>
#include <Metro.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <states/00-PreLaunch.h>
#include <states/State.h>

#include "utility.hpp"
#include <OpenMV/camera.h>
#include <ServoControls/ServoController.h>
#include <servos.h>

// #include <TeensyDebug.h>
// #pragma GCC optimize ("O0")

#include <typeinfo>

SensorFrame sensorFrame;

unsigned long previousTime = 0;
unsigned long currentTime = 0;

Sensorboard sensorBoard;
AttitudeStateEstimator *attitudeStateEstimator = new AttitudeStateEstimator();

//Payload Specific Stuff :)
struct Servos servos;
OpenMV *openMV = new OpenMV();

State *state;

float initialAltitude = 0;

#ifndef NO_SDCARD
bool sdCardInitialized = false;
File dataFile;
#endif

#ifndef NO_XBEE
XbeeProSX *xbee = new XbeeProSX(30); // CS GPIO 17, use 30?!!!! - Kai 10/29/2024
#endif

void setup()
{
    Serial.begin(9600);

#ifdef WAIT_FOR_SERIAL
    while (!Serial)
    {
        yield();
    }
#endif

    Wire.begin();
    Wire.setClock(400000);

    SPI.begin();

#ifndef NO_SDCARD
    // XXX: If using 5v only SD breakout board, make sure the first line is uncommented and the second line commented
    if (SD.sdfs.begin(31, SPI_SIXTEENTH_SPEED))
    { // REQUIRED for the non 3.3v tolerant SD breakout boards to work
        int fileIdx = 0;
        while (1)
        {
            char filename[100];
            sprintf(filename, "flightData%d.bin", fileIdx++);
            Serial.printf("Trying file `%s`\n", filename);
            if (!SD.exists(filename))
            {
                dataFile = SD.open(filename, O_WRONLY | O_CREAT);
                break;
            }
        }
        sdCardInitialized = true;
    }
    else
    {
        Serial.println("SD Init failed");
    }
#endif

    Serial.println("[Polaris] Initializing Sensor Board");
    if (sensorBoard.setup())
    {
        Serial.println("[Polaris] Sensor Setup Complete!");
    }
    else
    {
        Serial.println("[Polaris] Sensor Setup Failed!");
    }
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);

    servos = {
        .paraServo_1 = new ServoController(PARACHUTE_SERVO_1), // double check direction
        .paraServo_2 = new ServoController(PARACHUTE_SERVO_2),
        .paraServo_3 = new ServoController(PARACHUTE_SERVO_3),
        .paraServo_4 = new ServoController(PARACHUTE_SERVO_4),
        .cameraServo = new ServoController(CAMERA_SERVO),
    };

    pinMode(IR_PIN, INPUT);
    pinMode(PARACHUTE_SERVO_1_IN, INPUT);
    pinMode(PARACHUTE_SERVO_2_IN, INPUT);
    pinMode(PARACHUTE_SERVO_3_IN, INPUT);
    pinMode(PARACHUTE_SERVO_4_IN, INPUT);


    state = (State *)new PreLaunch(&sensorBoard, attitudeStateEstimator, xbee, &servos, openMV);

    state->initialize();

    currentTime = millis();
    previousTime = millis();

    #ifndef NO_XBEE
    xbee->start();
    #endif
};

void readSensors()
{
    sensorBoard.readInertialSensors();
    memcpy(&sensorFrame, &sensorBoard.Inertial_Baro_frame, sizeof(sensorBoard.Inertial_Baro_frame));
};

bool val = false;
long lastBlink = 0;

void loop()
{
    currentTime = millis();
    if (currentTime - lastBlink >= 1000)
    {
        lastBlink = currentTime;
        val = !val;
        if (sdCardInitialized)
        {
            digitalWrite(6, HIGH);
        }
        else
        {
            digitalWrite(6, val);
        }
    }

    if (currentTime - previousTime >= (1000 / LOOP_RATE))
    {
        previousTime = currentTime;
        state->loop();
    }

    // Check for state transition each loop
    State *nextState = state->nextState();

    if (nextState != nullptr)
    {
        Serial.print("State Change Detected: ");
        Serial.print(state->getId());
        Serial.print(" -> ");
        delete state;
        state = nextState;
        Serial.println(state->getId());
        state->initialize();
    };
};
#include <Arduino.h>
#include <Metro.h>
#include <Wire.h>
#include <SPI.h>

#include <SparkFun_u-blox_GNSS_v3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_LPS2X.h>

#include <states/State.h>
#include <states/Stowed.h>

#define LOOP_RATE 100

Metro timer = Metro(1000 / LOOP_RATE);

State *state = new Stowed();

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);

    timer.reset();

    state->initialize();
};

void loop()
{

    if (timer.check() == 1)
    {
        state->loop();
        State *nextState = state->nextState();
        if (nextState != nullptr)
        {
            delete state;
            state = nextState;
            state->initialize();
        }
    }
};



/*
// Variables for IMU biases (76-82)
float ac_x_error;
float ac_y_error;
float ac_z_error;
float gy_x_error;
float gy_y_error;
float gy_z_error;

// Ground level altitude compensation (84-85)
float altitude_AGL;

// Variable for measured battery voltage (112)
float vBatt = 0.0;

// chaeck if need? (119-123)
int16_t sumMainDescentVel = 0;
int16_t mainPollCount = 0;

int16_t sumDrogueDescentVel = 0;
int16_t droguePollCount = 0;

(140)
AvionicsState avionicsState = STARTUP;

(208-229)
// Defines the above ground level altitude to be the average altitude over 2000 samples
void calibrateAltitudeAGL()
{

    float altitude_error_sum = 0;

    for (int i = 0; i < AGL_CALIBRATION_ITERS; i++)
    {

        readSensors();
        altitude = pressureToAltitude(sensorPacket.Pressure);

        // Sum all readings
        altitude_error_sum = altitude_error_sum + altitude;
    }

    // Divide the sum to get the error value
    altitude_AGL = altitude_error_sum / AGL_CALIBRATION_ITERS;

    // Serial.print("altitude_AGL: ");
    // Serial.println(altitude_AGL);
}

(362-378)
// Convert pressure in [mBar] to altitude in [m]
float pressureToAltitude(float pressure_mBar)
{
    // physical parameters for model
    const float pb = 101325;   // [Pa] pressure at sea level
    const float Tb = 288.15;   // [K] temperature at seal level
    const float Lb = -0.0065;  // [K/m] standard temperature lapse rate
    const float hb = 0;        // [m] height at bottom of atmospheric layer (sea level)
    const float R = 8.31432;   // [N*m/mol*K] universal gas constant
    const float g0 = 9.80665;  // [m/s^2] Earth standard gravity
    const float M = 0.0289644; // [kg/mol] molar mass of Earth's air

    // convert pressure from [mBar] to [Pa]
    float pressure_Pa = pressure_mBar * 100;

    // compute altitude from formula
    return hb + (Tb / Lb) * (pow((pressure_Pa / pb), (-R * Lb / (g0 * M))) - 1);
}

(381-416)
// Construct the telemetry data packet. This is the struct that gets logged to the flash chip and transmitted to the ground station.
void constructTelemPacket()
{
    // Timestamp
    telemPacket.timestamp = millis() - loopStartTime;

    // State
    telemPacket.state = (uint8_t)avionicsState;

    // Battery voltage
    telemPacket.vBatt = (uint8_t)(vBatt * 20); // TODO what is 20?

    // Altitude [m]
    telemPacket.altitude = altitude;

    // Temperature
    telemPacket.temperature = sensorPacket.Temperature;

    // Airbrake actuation percent
    telemPacket.abPct = abPct;

    // Acceleration (XYZ) [m/s^2] - Scaled by 100x for transmission
    telemPacket.ac_x = (int16_t)(sensorPacket.ac_x * 100.0);
    telemPacket.ac_y = (int16_t)(sensorPacket.ac_y * 100.0);
    telemPacket.ac_z = (int16_t)(sensorPacket.ac_z * 100.0);

    // Angular rate (XYZ) [deg/s] - Scaled by 10x for transmission
    telemPacket.gy_x = (int16_t)(sensorPacket.gy_x * 10.0);
    telemPacket.gy_y = (int16_t)(sensorPacket.gy_y * 10.0);
    telemPacket.gy_z = (int16_t)(sensorPacket.gy_z * 10.0);

    // Velocity (vertical, lateral, total) [m/s]
    telemPacket.vel_vert = (int16_t)(stateStruct.vel_vert * 100.0);
    telemPacket.vel_lat = (int16_t)(stateStruct.vel_lat * 100.0);
    telemPacket.vel_total = (int16_t)(stateStruct.vel_total * 100.0);

}

(419-442)
// Read sensors and construct telemPacket
void readSensors()
{
    // Construct sensorPacket struct with raw data from inertial sensors + barometer
    sensorboard.readInertialSensors();
    memcpy(&sensorPacket, &sensorboard.Inertial_Baro_frame, sizeof(sensorboard.Inertial_Baro_frame));
    sensorPacket.ac_x -= ac_x_error;
    sensorPacket.ac_y -= ac_y_error;
    sensorPacket.ac_z -= ac_z_error;
    sensorPacket.gy_x -= gy_x_error;
    sensorPacket.gy_y -= gy_y_error;
    sensorPacket.gy_z -= gy_z_error;

    // Calculate total acceleration
    ac_total = sqrt((sensorPacket.ac_x * sensorPacket.ac_x + sensorPacket.ac_y * sensorPacket.ac_y + sensorPacket.ac_z * sensorPacket.ac_z));

    // Compute altitude from pressure
    altitude = pressureToAltitude(sensorPacket.Pressure) - altitude_AGL;

    // Read battery voltage
    vBatt = ((float)analogRead(VBATT_PIN) / (ADC_RESOLUTION / ADC_FULL_SCALE_RANGE)) * VOLTAGE_DIVIDER_RATIO;

    // Construct telemetry data packet
    constructTelemPacket();
}

(445-450)
// adds a new telemPacket to the circular buffer
void buildCircBuf()
{
    structString = String(telemPacket.timestamp) + "," + String(telemPacket.state) + "," + String(telemPacket.altitude) + "," + String(telemPacket.temperature) + "," + String(telemPacket.abPct) + "," + String(telemPacket.ac_x) + "," + String(telemPacket.ac_y) + "," + String(telemPacket.ac_z) + "," + String(telemPacket.gy_x) + "," + String(telemPacket.gy_y) + "," + String(telemPacket.gy_z) + "," + String(telemPacket.vel_vert) + "," + String(telemPacket.vel_lat) + "," + String(telemPacket.vel_total) + "," + String(telemPacket.vBatt);
    circBuf[circBufInd] = structString;  // pass in the string to the circular buffer
    circBufInd = (circBufInd + 1) % 200; // increment the index and wrap around if necessary
}

(452-459)
// writes circular buffer to flash chip
void writeCircBuf()
{
    for (int i = 0; i < 200; i++)
    {
        flash.writeStruct(circBuf[i]);
    }
}

(461-466)
// Write data (telemPacket) to flash chip
void logData()
{
    structString = String(telemPacket.timestamp) + "," + String(telemPacket.state) + "," + String(telemPacket.altitude) + "," + String(telemPacket.temperature) + "," + String(telemPacket.abPct) + "," + String(telemPacket.ac_x) + "," + String(telemPacket.ac_y) + "," + String(telemPacket.ac_z) + "," + String(telemPacket.gy_x) + "," + String(telemPacket.gy_y) + "," + String(telemPacket.gy_z) + "," + String(telemPacket.vel_vert) + "," + String(telemPacket.vel_lat) + "," + String(telemPacket.vel_total) + "," + String(telemPacket.vBatt);
    flash.writeStruct(structString);
}

(469-472)
// Transmit telemetry packet to ground station
void sendTelemetry()
{
    telemBoard.onLoop(telemPacket);
}

(648-657)
// Print to the Serial monitor the measured duration of one loop of the flight computer.
void printLoopTime()
{
    long currentTime = millis();
    loopTime = currentTime - previousTime;
    previousTime = currentTime;
    Serial.print("Loop time: ");
    Serial.print(loopTime);
    Serial.println(" ms");
}



*/
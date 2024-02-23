#include "Simulation.h"
#include "./OpenMV/camera.h"
#include <states/State.h>

Simulation::Simulation(StateEstimator * ekf) {
    this->name = "Simulation";
    this->ekf = ekf;
};

void Simulation::initialize_impl() {

};

void Simulation::loop_impl() {
    this->currentState = ekf->onLoop(sensorData);

    telemPacket.accelX = sensorData.ac_x;
    telemPacket.accelY = sensorData.ac_y;
    telemPacket.accelZ = sensorData.ac_z;

    telemPacket.gyroX = sensorData.gy_x;
    telemPacket.gyroY = sensorData.gy_y;
    telemPacket.gyroZ = sensorData.gy_z;

    telemPacket.magX = sensorData.mag_x;
    telemPacket.magY = sensorData.mag_y;
    telemPacket.magZ = sensorData.mag_z;

    telemPacket.pressure = sensorData.Pressure;
    telemPacket.altitude = pressureToAltitude(sensorData.Pressure);
    telemPacket.timestamp = this->currentTime;
    telemPacket.q = currentState(0);
    telemPacket.i = currentState(1);
    telemPacket.j = currentState(2);
    telemPacket.k = currentState(3);
    
    // This is for testing the camera, not working currently as I2C not setup.
    OpenMV camera;
    struct CameraData camdata;
    camera.readData(camdata);
    Serial.print("camdata.cx: ");
    Serial.println(camdata.cx);
    Serial.print("camdata.cy: ");
    Serial.println(camdata.cy);
    //Serial.println(this->deltaTime);
};

State *Simulation::nextState_impl() {

    return nullptr; // DO NOT EXIT STATE
};
#include "StatePrediction.h"

/**
 * @brief Construct a new State Prediction:: State Prediction object
 * 
 * @param sensorPacket current sensor packet
 */
StatePrediction::StatePrediction(Utility::SensorPacket sensorPacket, float dt) {
    this->constructMotionMatrix(sensorPacket);  
    this->dt = dt;
};

/**
 * @brief Updates motion matrix for the dynamic system at each time-step
 * 
 * @param sensorPacket 
 */
void StatePrediction::constructMotionMatrix(Utility::SensorPacket sensorPacket) {

    rho_inf = Utility::getDensityAtAlt(sensorPacket.altitude); // [kg/m^3] Density at altitude


    motionMatrix(2,2) = pow((1/4)*rho_inf*(4/3)*PI*(FlightParameters::D_p/2), 3);
    motionMatrix(0,0) = 0.5f*motionMatrix(2,2);
    motionMatrix(1,1) = 0.5f*motionMatrix(2,2);
    motionMatrix(3,3) = FlightParameters::h_cp*pow(FlightParameters::D_p,2)*motionMatrix(0,0);
    motionMatrix(4,4) = FlightParameters::h_cp*pow(FlightParameters::D_p,2)*motionMatrix(0,0);
};

Eigen::Vector<float,6> StatePrediction::predictState(Utility::SensorPacket sensorPacket) {
    this->constructMotionMatrix(sensorPacket);

    return {0,0,0,0,0,0};
};

Eigen::Vector<float, 6> StatePrediction::stepRK4() {

    currentState(0) = currentState(3);
    currentState(1) = currentState(4);
    currentState(2) = currentState(5);
};
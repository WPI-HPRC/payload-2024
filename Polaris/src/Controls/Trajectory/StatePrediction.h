/**
 * @file StatePrediction.h
 * @author Daniel Pearson (djpearson@wpi.edu)
 * @brief Class holding the functions for the RK4 Estimation of the Payload
 * @version 0.1
 * @date 2024-02-18
 * 
 * @copyright Copyright WPI HPRC (c) 2024
 * 
 */

#pragma once

#include <ArduinoEigen.h>

#include <FlightParams.hpp>
#include <utility.hpp>

class StatePrediction {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    public:

    StatePrediction(Utility::SensorPacket sensorPacket, float dt);

    private:
    // Configure motion matrix and allocate as identity
    Eigen::Matrix<float,5,5> motionMatrix = Eigen::Matrix<float,5,5>::Identity();

    void constructMotionMatrix(Utility::SensorPacket sensorPacket);

    Eigen::Vector<float, 6> predictState(Utility::SensorPacket sensorPacket);

    Eigen::Vector<float, 6> currentState = {0,0,0,0,0,0};

    Eigen::Vector<float, 6> stepRK4();

    float rho_inf = 1.225; // [kg/m^3] Density at altitude
    
    float dt = 0.025;

    const float fpa = PI/2; // Assume Horizontal Equilibrium Condition
};
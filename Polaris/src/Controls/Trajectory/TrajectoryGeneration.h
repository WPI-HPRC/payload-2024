#pragma once

#include "Arduino.h"
#include <Utility.hpp>
// #include <BasicLinearAlgebra.h>
#include <ArduinoEigen.h>

/**
 * @brief Trajectory generation class - Used to calculate the constants for a third degree spline of an estimated target trajectory for the model predictive controller
 * 
 */
class TrajectoryGeneration {
    public:

    /**
     * @brief Construct Trajectory Generation Class
     * 
     * @return TrajectoryGeneration 
     */
    TrajectoryGeneration TrajectoryGeneration();

    /**
     * @brief Calculate a target trajectory for the Model Predcitive Controller
     * 
     * TODO: Switch to EKF Location
     * TODO: Potentially include target altitude in formula
     * @param sensorPacket Current sensor packet to feed current GPS location
     * @param targetPoint Target GPS point in lat/long
     * @return BLA::Matrix<4> 
     */
    Eigen::Vector4 calculateTargetTrajectoryConstants(Utility::SensorPacket sensorPacket, Eigen::Vector2 targetPoint);

};
/**
 * @file TrajectoryGeneration.cpp
 * @author Dan Pearson (djpearson@wpi.edu)
 * @brief Trajectory generation class to feed a function to the Model Predictive Controller
 * @version 1.0
 * @date 02-15-2024
 * 
 * @copyright Copyright WPI HPRC (c) 2024
 * 
 * ASSUMPTIONS:
 * - Spherical to Flat earth projection !! NEGLECTING Z POSITION !!
 * 
 */


#include "TargetTrajectory.h"

/**
 * @brief Construct a new Trajectory Generation:: Trajectory Generation object
 * 
 */
TargetTrajectory::TargetTrajectory() {
    
};

Eigen::Vector<float,4> TargetTrajectory::calculateTargetTrajectoryConstants(Utility::SensorPacket sensorPacket, const Eigen::Vector<float,2> &targetPoint) {
    
    //Calculate Earth Centered Earth Fixed Location for LONG/LAT Point 2
    float N_earth_0 = Utility::a_earth / sqrt(1 - pow(Utility::e_earth, 2) * pow(sin(sensorPacket.gpsLat), 2));

    float X_0 = (N_earth_0 + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * cos(sensorPacket.gpsLong * DEG_TO_RAD);
    float Y_0 = (N_earth_0 + sensorPacket.gpsAltAGL) * cos(sensorPacket.gpsLat * DEG_TO_RAD) * sin(sensorPacket.gpsLong * DEG_TO_RAD);
    float Z_0 = (N_earth_0*(1-pow(Utility::e_earth,2))+sensorPacket.gpsAltAGL)*sin(sensorPacket.gpsLat);

    float targetLat = targetPoint(0);
    float targetLong = targetPoint(1);

    // Calculate Earth Centered Earth Fixed Location for LONG/LAT Point 2
    float N_earth_1 = Utility::a_earth / sqrt(1 - pow(Utility::e_earth, 2) * pow(sin(targetLat), 2));

    float X_1 = (N_earth_1 + sensorPacket.gpsAltAGL) * cos(targetLat * DEG_TO_RAD) * cos(targetLong * DEG_TO_RAD);
    float Y_1 = (N_earth_1 + sensorPacket.gpsAltAGL) * cos(targetLat * DEG_TO_RAD) * sin(targetLong * DEG_TO_RAD);
    float Z_1 = (N_earth_1*(1-pow(Utility::e_earth,2))+sensorPacket.gpsAltAGL)*sin(targetLat);

    // Utilize the least squares estimation method to fit a curve to the target trajectory

    Eigen::Vector<float,2> y_pts {Y_0, Y_1};

    /**f(x) = Ax^3 + Bx^2 + Cx + D
     * 
     * Estimate the Y value for this function for each given X Point
     * 
     * */
    Eigen::Matrix<float, 2,4> X_matrix {
        {pow(X_0, 3), pow(X_0, 2), X_0, 1},
        {pow(X_1, 3), pow(X_1, 2), X_1, 1}
    };

    // C = X \ y_pts => {A,B,C,D}
    Eigen::Vector<float,4> C = X_matrix.colPivHouseholderQr().solve(y_pts);

    return C;
};
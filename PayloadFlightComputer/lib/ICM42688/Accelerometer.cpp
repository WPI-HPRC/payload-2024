#include "Accelerometer.h"
#include <Wire.h>

Accelerometer::Accelerometer(int addr) : icm2688(Wire, addr) {}

void Accelerometer::init() {
  this->icm2688.setAccelFS(ICM42688::gpm16);
  this->icm2688.setGyroFS(ICM42688::dps250);

  this->icm2688.setAccelODR(ICM42688::odr100);
  this->icm2688.setGyroODR(ICM42688::odr100);
}

ICM_data Accelerometer::read() {
  this->icm2688.getAGT();

  return ICM_data {
    .accX = this->icm2688.accX(),
    .accY = this->icm2688.accY(),
    .accZ = this->icm2688.accZ(),
    .gyroX = this->icm2688.gyrX(),
    .gyroY = this->icm2688.gyrY(),
    .gyroZ = this->icm2688.gyrZ(),
  };
}

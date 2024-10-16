#include "Magnetometer_SB.h"
#include <SensorBoardLibraries/Config.h>


/*
    @brief Constructor for the MMC5983MA class
    @param bus The I2C bus to use
    @param address The I2C address of the Magnetometer
*/
MMC5983MA::MMC5983MA(TwoWire &bus, uint8_t address)
{
    I2C_BUS = &bus;
    I2C_Address = address;
}

/*
    @brief Writes data to a register
    @param SubAddress The register to write to
    @param data The data to write
*/
void MMC5983MA::writeRegister(uint8_t SubAddress, uint8_t data)
{
    I2C_BUS->beginTransmission(I2C_Address);
    I2C_BUS->write(SubAddress);
    I2C_BUS->write(data);
    I2C_BUS->endTransmission();
}

/*
    @brief Reads data from a register
    @param SubAddress The register to read from
    @param length The number of bytes to read
    @param data The array to store the data in
*/
void MMC5983MA::readRegister(uint8_t SubAddress, int length, uint8_t *data)
{
    I2C_BUS->beginTransmission(I2C_Address);
    I2C_BUS->write(SubAddress);
    I2C_BUS->endTransmission();
    I2C_BUS->requestFrom(I2C_Address, length);
    for (int i = 0; i < length; i++)
    {
        data[i] = I2C_BUS->read();
    }
}

/*
    @brief Computes a 18 bit value from the 3 bytes of data in the following format:
    @param HighByte The high byte of the 18 bit value [17:10]
    @param LowByte The low byte of the 18 bit value [9:2]
    @param ExtraByte 8 bits of data where: [7:6] are the 2 LSBs of the X value, [5:4] are the 2 LSBs of the Y value, [3:2] are the 2 LSBs of the Z value
    @param Axis The axis being processed - 0 for X, 1 for Y, 2 for Z
*/
// uint32_t MMC5983MA::process18BitResolution(uint8_t * data, uint8_t Axis)
// {
//     // uint32_t Value = 0;
//     // Value = (uint32_t)HighByte << 10;
//     // Value |= (uint32_t)LowByte << 2;
//     // Value |= ((uint32_t)(ExtraByte)) >> (6 - Axis * 2) & 0x03; //Shifts the 2 LSBs of the axis to the LSBs of the value
//     // return Value;
// }

/*
    @brief Checks the Product ID of the Magnetometer
    @return True if the Product ID is correct, false otherwise
*/
bool MMC5983MA::CheckProductID()
{
    uint8_t data;
    readRegister(PROD_ID, 1, &data);
    if (data == MMC_PROD_ID)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    @brief Enables the Magnetometer by writing to the control registers according to the Config.h file
*/
void MMC5983MA::sensorEnable()
{
    writeRegister(INT_CTRL_0,Register0_Set);
    writeRegister(INT_CTRL_1,Register1_Set);
    writeRegister(INT_CTRL_2,Register2_Set);
}

/*
    @brief Sets up the Magnetometer by checking the Product ID and enabling the sensor
    @return True if the setup was successful, false otherwise
*/
bool MMC5983MA::setup()
{
    // Serial.println("Initializing Magnetometer");
    if(!CheckProductID())
    {
        return false;
    }
    // Serial.println("Magnetometer ID Check Passed");
    // Serial.println("Enabling Magnetometer");
    sensorEnable();
    Serial.println("Magnetometer Enabled");
    return true;
}

/*
    @brief Reads the Magnetometer data and stores it in the Data array
    @param Data The array to store the data in
    @param StartIndex The index to start storing the data at
*/
void MMC5983MA::sensorRead(uint32_t *MagArray)
{
    uint8_t dataBuffer[7] = {0};

    readRegister(X_OUT_0, 7, dataBuffer);

    uint32_t magX, magY, magZ;

    magX = dataBuffer[0];
    magX = (magX << 8) | dataBuffer[1];
    magX = (magX << 2) | (dataBuffer[6] >> 6);

    magY = dataBuffer[2];
    magY = (magY << 8) | dataBuffer[3];
    magY = (magY << 2) | ((dataBuffer[6] >> 4) &0x03);

    magZ = dataBuffer[4];
    magZ = (magZ << 8) | dataBuffer[5];
    magZ = (magZ << 2) | ((dataBuffer[6] >> 2) & 0x03);

    MagArray[0] = magX;
    MagArray[1] = magY;
    MagArray[2] = magZ;
}

/*
    @brief Calculates the calibrated values of the Magnetometer data
    @param Raw_X The raw X value
    @param Raw_Y The raw Y value
    @param Raw_Z The raw Z value
    @param *Calibrated_X The location to store the calibrated X value
    @param *Calibrated_Y The location to store the calibrated Y value
    @param *Calibrated_Z The location to store the calibrated Z value

    // The magnetometer calibration follows the formula: Calibrated = A^-1 * (Raw - B)
    // Where A is the calibration matrix(3x3), B is the offset vector(3x1), and Raw is the raw vector(3x1)
    // The Calibration matrix is solved using the calibration in the matlab script
    // The Calibration values are stored in the Magnetometer_SB.h file
*/
void MMC5983MA::calculateCalibratedValues(uint32_t Raw_X, uint32_t Raw_Y, uint32_t Raw_Z, float *Calibrated_X, float *Calibrated_Y, float *Calibrated_Z)
{
    float X = (float)(Raw_X - _B1);
    float Y = (float)(Raw_Y - _B2);
    float Z = (float)(Raw_Z - _B3);

    *Calibrated_X = _A11 * X + _A12 * Y + _A13 * Z;
    *Calibrated_Y = _A21 * X + _A22 * Y + _A23 * Z;
    *Calibrated_Z = _A31 * X + _A32 * Y + _A33 * Z;
}
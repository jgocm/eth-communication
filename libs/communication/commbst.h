/**Communication class between PC and Robots
 * @author RoboCIn
 *
 * This class has a group of methods to be used for communication between the main PC and all the robots using the nRF24L01+ radios.
 *
 */
#ifndef COMMBST_H
#define COMMBST_H

#include "nRF24Communication/commConfig.h"
#include "nRF24Communication/commTypes.h"
#include <iostream>
#include <string.h>

class CommBst
{
public:
// Definitions
#define DEFAULT_DEVICE_IP "199.0.1.1"
#define DEFAULT_DEVICE_PORT 9600
#define DEFAULT_RECEIVE_IP "199.0.1.2"
#define DEFAULT_RECEIVE_PORT 9601
#define DEFAULT_DEVICE_NAME "/dev/NRF_USB"
#define DEFAULT_BAUDRATE B115200

    /*
     * Class constructor
     */
    CommBst();

    /*
     * Class destructor
     */
    ~CommBst();

    /**
     * Method to configure VSS-robot message type!
     * @param id
     * @param motorSpeed1
     * @param motorSpeed2
     * @param flags
     */
    void setVSSSpeed(uint8_t id, int8_t motorSpeed1, int8_t motorSpeed2, uint8_t flags);

    /**
     * Method to configure SSL-robot message type!
     * @param id
     * @param vx
     * @param vy
     * @param vw
     * @param front
     * @param chip
     * @param force
     * @param strength
     * @param dribbler
     * @param speed
     */
    void setSSLSpeed(uint8_t id, double vx, double vy, double vw, uint8_t front, uint8_t chip, uint8_t charge, double strength, uint8_t dribbler, uint speed, uint8_t command);

    void setPosition(uint8_t id, Vector v, PositionType type, double max_speed);

    void getTelemetry(RobotInfo& telemetry);
    void getOdometry(RobotInfo& odometry);
    void setConfigBst(NetworkType category);

private:
protected:
    /// Declaration of message types
    packetSpeedVSS _mVSS;
    packetSpeedSSL _mSSL;
    packetPosition _mPos;
    packetGeneric _receivePckt;

    packetTelemetry _telemetryPckt;
    packetOdometry _odometryPckt;
    packetBStConfig _bstConfig;
};

#endif // COMMBST_H

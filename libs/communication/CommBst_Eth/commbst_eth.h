#ifndef COMMBST_ETH_H
#define COMMBST_ETH_H

#include "../commbst.h"
#include "Socket.h"

class CommBst_Eth : public CommBst
{
public:
    CommBst_Eth();
    void setup(NetworkType type, char *d_ip = DEFAULT_DEVICE_IP, unsigned short d_p = DEFAULT_DEVICE_PORT, char *r_ip = DEFAULT_RECEIVE_IP, unsigned short r_p = DEFAULT_RECEIVE_PORT);
    void configReceiveChannel(bool turnOn, char *r_ip, unsigned short r_p);
    /**
     * Method to send message to SSL-robot
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
     * @param command
     */
    void sendSpeed(uint8_t id, double vx, double vy, double w, uint8_t kick, uint8_t chip, uint8_t charge, double strength, uint8_t dribbler, uint speed, uint8_t command);
    /**
     * Method to send messsage to VSS-robot
     * @param id
     * @param motorSpeed1
     * @param motorSpeed2
     * @param flags
     */
    void sendSpeed(uint8_t id, int8_t motorSpeed1, int8_t motorSpeed2, uint8_t flags);

    void sendPosition(uint8_t id, Vector v, PositionType type, double max_speed);

    void read(RobotInfo& info);

private:
    void sendConfigBst(NetworkType type);

    UDPSocket* _udpSocket;
    char* _host;
    unsigned short _port;
};

#endif // COMMBST_ETH_H

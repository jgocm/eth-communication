#include "commbst_eth.h"

CommBst_Eth::CommBst_Eth()
{
    this->_udpSocket = new UDPSocket();
}

void CommBst_Eth::setup(NetworkType type, char *d_ip, unsigned short d_p, char *r_ip, unsigned short r_p)
{
    this->_host = d_ip;
    this->_port = d_p;

    if(r_p != 0)
        configReceiveChannel(true, r_ip, r_p);

    sendConfigBst(type);
}

void CommBst_Eth::sendConfigBst(NetworkType type)
{
    this->setConfigBst(type); // setConfigBst has no QT dependencies
    //_udpSocket->writeDatagram((char *) (this->_bstConfig.encoded), sizeof(this->_bstConfig.encoded), QHostAddress(this->_host), this->_port);
    _udpSocket->SendDataGram((char *) (this->_bstConfig.encoded), sizeof(this->_bstConfig.encoded), this->_host, this->_port);

}

void CommBst_Eth::sendSpeed(uint8_t id, int8_t motorSpeed1, int8_t motorSpeed2, uint8_t flags)
{
    this->setVSSSpeed(id, motorSpeed1, motorSpeed2, flags);
    _udpSocket->SendDataGram((char *) (this->_mVSS.encoded), sizeof(this->_mVSS.encoded), this->_host, this->_port);
}

void CommBst_Eth::sendSpeed(uint8_t id, double vx, double vy, double w, uint8_t kick, uint8_t chip, uint8_t charge, double strength, uint8_t dribbler, uint speed, uint8_t command){
    this->setSSLSpeed(id,vx,vy,w,kick,chip, charge, strength, dribbler, speed, command);
    _udpSocket->SendDataGram((char *) (this->_mSSL.encoded), sizeof(this->_mSSL.encoded), this->_host, this->_port);
}

void CommBst_Eth::sendPosition(uint8_t id, Vector v, PositionType type, double max_speed){
    this->setPosition(id, v, type, max_speed);
    _udpSocket->SendDataGram((char *) (this->_mPos.encoded), sizeof(this->_mPos.encoded), this->_host, this->_port);
}

/*void CommBst_Eth::read(RobotInfo& info){
    info.id = -1;
    info.type = msgType::NONE;
    //if(_udpSocket->readDatagram((char *) this->_receivePckt.encoded, sizeof this->_receivePckt.encoded) > 0){
    if(_udpSocket->Recv((char *) this->_receivePckt.encoded, sizeof this->_receivePckt.encoded) > 0){
        if(this->_receivePckt.decoded.typeMsg == static_cast<uint8_t>(msgType::TELEMETRY)){
            this->getTelemetry(info);
        }
        else if(this->_receivePckt.decoded.typeMsg == static_cast<uint8_t>(msgType::ODOMETRY)){
            this->getOdometry(info);
        }
    }
}*/

void CommBst_Eth::configReceiveChannel(bool turnOn, char *r_ip, unsigned short r_p)
{
    if (turnOn) {
        //this->_udpSocket->bind(QHostAddress(r_ip), r_p);
        this->_udpSocket->BindLocalAddressAndPort(r_ip, r_p); //r_ip ou &r_ip?
    }
    else {
        //this->_udpSocket->close();
    }
}

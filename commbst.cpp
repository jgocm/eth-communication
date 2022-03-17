#include "commbst.h"

CommBst::CommBst()
{
    std::cout << "nrf Constructor!" << std::endl;
}

CommBst::~CommBst()
{
    std::cout << "nrf Destructor!" << std::endl;
}

void CommBst::setVSSSpeed(uint8_t id, int8_t motorSpeed1, int8_t motorSpeed2, uint8_t flags)
{
    memset(this->_mVSS.encoded, 0, VSS_SPEED_LENGTH);

    this->_mVSS.decoded.typeMsg = static_cast<uint8_t>(msgType::VSS_SPEED);
    this->_mVSS.decoded.id = id;
    this->_mVSS.decoded.leftSpeed = motorSpeed1;
    this->_mVSS.decoded.rightSpeed = motorSpeed2;
    this->_mVSS.decoded.flags = flags;
}

void CommBst::setSSLSpeed(uint8_t id, double vx, double vy, double vw, uint8_t front, uint8_t chip, uint8_t charge, double strength, uint8_t dribbler, uint speed, uint8_t command)
{
    memset(this->_mSSL.encoded, 0, SSL_SPEED_LENGTH);

    this->_mSSL.decoded.typeMsg = static_cast<uint8_t>(msgType::SSL_SPEED);
    this->_mSSL.decoded.id = id;
    this->_mSSL.decoded.vx = static_cast<int32_t>(vx * 10000);
    this->_mSSL.decoded.vy = static_cast<int32_t>(vy * 10000);
    this->_mSSL.decoded.vw = static_cast<int32_t>(vw * 10000);
    this->_mSSL.decoded.front = static_cast<uint8_t>(front);
    this->_mSSL.decoded.chip = static_cast<uint8_t>(chip);
    this->_mSSL.decoded.charge = static_cast<uint8_t>(charge);
    this->_mSSL.decoded.strength = static_cast<uint8_t>(strength * 10);
    this->_mSSL.decoded.dribbler = static_cast<uint8_t>(dribbler);
    this->_mSSL.decoded.speed = static_cast<uint8_t>(speed * 10);
    this->_mSSL.decoded.command = static_cast<uint8_t>(command);
}

/*void CommBst::setPosition(uint8_t id, Vector v, PositionType type, double max_speed) {

    memset(this->_mPos.encoded, 0, POSITION_LENGTH);

    this->_mPos.decoded.typeMsg = static_cast<uint8_t>(msgType::POSITION);
    this->_mPos.decoded.id = id;
    this->_mPos.decoded.x = v.x * 1000;
    this->_mPos.decoded.y = v.y * 1000;
    this->_mPos.decoded.w = v.w * 10000;
    this->_mPos.decoded.speed = max_speed * 100;
    this->_mPos.decoded.positionType = static_cast<uint8_t>(type);
}


void CommBst::getTelemetry(RobotInfo& telemetry)
{
    if (static_cast<msgType>(this->_receivePckt.decoded.typeMsg) == msgType::TELEMETRY){
        memcpy(this->_telemetryPckt.encoded, this->_receivePckt.encoded, TELEMETRY_LENGTH);
        telemetry.id = this->_telemetryPckt.decoded.id;
        telemetry.m.m1 = this->_telemetryPckt.decoded.m1 / 100.0;
        telemetry.m.m2 = this->_telemetryPckt.decoded.m2 / 100.0;
        telemetry.m.m3 = this->_telemetryPckt.decoded.m3 / 100.0;
        telemetry.m.m4 = this->_telemetryPckt.decoded.m4 / 100.0;
        telemetry.dribbler = this->_telemetryPckt.decoded.dribbler / 10.0;
        telemetry.ball = this->_telemetryPckt.decoded.ball;
        telemetry.battery = this->_telemetryPckt.decoded.battery / 10.0;
        telemetry.kickLoad = this->_telemetryPckt.decoded.kickLoad / 100.0;
        telemetry.type = msgType::TELEMETRY;
    }
}

void CommBst::getOdometry(RobotInfo& odometry)
{
    if (static_cast<msgType>(this->_receivePckt.decoded.typeMsg) == msgType::ODOMETRY) {
        memcpy(this->_odometryPckt.encoded, this->_receivePckt.encoded, ODOMETRY_LENGTH);
        odometry.id = this->_odometryPckt.decoded.id;
        odometry.v.x = this->_odometryPckt.decoded.x / 1000.0;
        odometry.v.y = this->_odometryPckt.decoded.y / 1000.0;
        odometry.v.w = this->_odometryPckt.decoded.w / 10000.0;
        odometry.m.m1 = this->_odometryPckt.decoded.m1 / 100.0;
        odometry.m.m2 = this->_odometryPckt.decoded.m2 / 100.0;
        odometry.m.m3 = this->_odometryPckt.decoded.m3 / 100.0;
        odometry.m.m4 = this->_odometryPckt.decoded.m4 / 100.0;
        odometry.dribbler = this->_odometryPckt.decoded.dribbler / 10.0;
        odometry.ball = this->_odometryPckt.decoded.ball;
        odometry.battery = this->_odometryPckt.decoded.battery / 10.0;
        odometry.kickLoad = this->_odometryPckt.decoded.kickLoad / 100.0;
        odometry.type = msgType::ODOMETRY;
    }
}*/

void CommBst::setConfigBst(NetworkType category)
{
    if (category == NetworkType::ssl ){
            _bstConfig.decoded.typeMsg = static_cast<uint8_t>(msgType::BST_CONFIG);
            _bstConfig.decoded.duplex = true;
            _bstConfig.decoded.team = static_cast<uint8_t>(NetworkType::ssl);
            _bstConfig.decoded.addr1 = SSL_ADDR_1;
            _bstConfig.decoded.addr2 = SSL_ADDR_2;
            _bstConfig.decoded.payload = SSL_PAYLOAD_LENGTH;
            _bstConfig.decoded.channel1 = SSL_1_BASE_SEND_CH;
            _bstConfig.decoded.channel2 = SSL_2_BASE_RECV_CH;
        }
}

#ifndef COMM_TYPES_H
#define COMM_TYPES_H

/************* AUXILIAR TYPES ************/
#include <stdint.h>
#include "commConfig.h"

enum class RadioFunction
{
  receiver,
  sender
};

/*
 * Network type / catergory configuration
 *  Attencion: Limited in 15
 */
enum class NetworkType
{
  unknown = 0,
  generic,
  ssl,
  vss,
  rl
};

/*
 * Type of the packet position.
 *  Attencion: Limited in 8
 */
enum class PositionType
{
  unknown = 0,
  source,
  destiny
};

typedef struct
{
  uint8_t payload;
  uint64_t addr[2];
  bool ack;
  uint8_t receiveChannel;
  uint8_t sendChannel;
  uint8_t pipeNum;
  bool reConfig;
  RadioFunction function;
} NetworkConfig;

typedef struct
{
  double m1 = 0;
  double m2 = 0;
  double m3 = 0;
  double m4 = 0;
} Motors;

typedef struct Vector
{
  double x = 0;
  double y = 0;
  double w = 0;

  inline Vector operator+(Vector a)
  {
    Vector b;
    b.x = x + a.x;
    b.y = y + a.y;
    b.w = w + a.w;
    return b;
  }

  inline Vector operator-(Vector a)
  {
    Vector b;
    b.x = x - a.x;
    b.y = y - a.y;
    b.w = w - a.w;
    return b;
  }

  inline Vector operator*(double a)
  {
    Vector b;
    b.x = x * a;
    b.y = y * a;
    b.w = w * a;
    return b;
  }
} Vector;

typedef struct KickFlags
{
  bool front = false;
  bool chip = false;
  bool charge = false;
  float kickStrength = 0;
  bool ball = false;
  bool dribbler = false;
  float dribblerSpeed = 0;

  KickFlags &operator=(const KickFlags &a)
  {
    front = a.front;
    chip = a.chip;
    charge = a.charge;
    kickStrength = a.kickStrength;
    ball = a.ball;
    dribbler = a.dribbler;
    dribblerSpeed = a.dribblerSpeed;
    return *this;
  }
} KickFlags;

typedef struct RobotPosition
{
  Vector v;
  PositionType type;
  double maxSpeed;

} RobotPosition;

typedef struct
{
  int id = -1;
  msgType type;
  Motors m;
  Vector v;
  double dribbler = 0;
  double kickLoad = 0;
  bool ball = false;
  double battery = 0;
} RobotInfo;

#endif // COMM_TYPES_H

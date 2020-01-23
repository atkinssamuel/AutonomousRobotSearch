#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <chrono>

class PidController
{
private:
    float Kp, Ki, Kd;
    float setPoint;
    float outputMaxLimit, outputMinLimit;

    float errorPrior, integralPrior;
    std::chrono::time_point<std::chrono::system_clock> previousTime;

    float clamp(float);

public:
    PidController(float, float, float, float, float, float);
    float step(float);
};

#endif
#include "PidController.hpp"
#include <algorithm>
#include <chrono>

PidController::PidController(float Kp, float Ki, float Kd, float setPoint, float outputMaxLimit, float outputMinLimit)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->setPoint = setPoint;
    this->outputMaxLimit = outputMaxLimit;
    this->outputMinLimit = outputMinLimit;

    this->errorPrior = 0;
    this->integralPrior = 0;

    this->previousTime = std::chrono::system_clock::now();
}

float PidController::step(float value)
{
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    float iterationTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - this->previousTime).count();
    this->previousTime = currentTime;

    float error = this->setPoint - value;
    float integral = this->integralPrior + error * iterationTime;
    float derivative = (error - this->errorPrior) / iterationTime;
    float output = this->Kp * error + this->Ki * integral + this->Kd * derivative;
    this->errorPrior = error;
    this->integralPrior = integral;

    return this->clamp(output);
}

float PidController::clamp(float value)
{
    return std::max(std::min(this->outputMaxLimit, value), this->outputMinLimit);
}
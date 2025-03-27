#include "Car.h"
#include <iostream>
#include <utility>
#include <map>

using SpeedLimit = std::pair<int, int>;

const std::map<int, SpeedLimit> GEAR_SPEED_LIMITS = {
    { -1, { 0, 20 } },
    { 0, { 0, INT_MAX } },
    { 1, { 0, 30 } },
    { 2, { 20, 50 } },
    { 3, { 30, 60 } },
    { 4, { 40, 90 } },
    { 5, { 50, 150 } },
};

bool Car::IsTurnedOn() const
{
    return m_engineIsOn;
}

Direction Car::GetDirection() const
{
    if (m_speed > 0)
    {
        return Direction::Forward;
    }

    if (m_speed < 0)
    {
        return Direction::Backward;
    }

    return Direction::StandingStill;
}

int Car::GetSpeed() const
{
    return std::abs(m_speed);
}

Gear Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    if (!m_engineIsOn)
    {
        m_engineIsOn = true;
        m_gear = Gear::NeutralGear;
        m_speed = 0;
    }

    return true;
}

bool Car::TurnOffEngine()
{
    if (m_gear == Gear::NeutralGear && m_speed == 0)
    {
        m_engineIsOn = false;
        return true;
    }

    throw std::runtime_error("Сar must be stopped and in neutral gear\n");
    return false;
}

bool IsSpeedInLimit(int curSpeed, int minSpeed, int maxSpeed)
{
    return curSpeed >= minSpeed && curSpeed <= maxSpeed;
}

bool Car::ChangeGearBasedOnSpeed(int gear)
{
    if (gear == 0)
    {
        m_gear = Gear::NeutralGear;
        return true;
    }

    if (gear == -1)
    {
        if (m_speed == 0)
        {
            m_gear = Gear::ReverseGear;
            return true;
        }
        
        std::cout << "Cannot reverse while moving\n";
        return false;
    }

    const auto [minSpeed, maxSpeed] = GEAR_SPEED_LIMITS.at(gear);
    if (IsSpeedInLimit(m_speed, minSpeed, maxSpeed))
    {
        m_gear = static_cast<Gear>(gear);
        return true;
    }

    throw std::runtime_error("Unsuitable current speed");
    return false;
}

bool Car::SetGear(int gear)
{
    if (gear < -1 || gear > 5)
    {
        throw std::runtime_error("Invalid gear\n");
        return false;
    }

    if (!m_engineIsOn)
    {
        if (gear == 0)
        {
            m_gear = Gear::NeutralGear;
            return true;
        }

        throw std::runtime_error("Cannot set gear while engine is off\n");
        return false;
    }

    if (gear == -1 && m_speed != 0)
    {
        return false;
    }

    if ((m_gear == Gear::ReverseGear && gear > 0 && m_speed != 0) ||
        (static_cast<int>(m_gear) > 0 && gear == -1 && m_speed != 0))
    {
        return false;
    }

    return ChangeGearBasedOnSpeed(gear);
}

bool Car::SetSpeed(int speed)
{
    if (speed < 0)
    {
        throw std::runtime_error("Speed cannot be negative\n");
        return false;
    }

    if (!m_engineIsOn)
    {
        throw std::runtime_error("Cannot set speed while engine is off\n");
        return false;
    }

    // поставить в мапу MAX INT и 0 для нейтралки
    auto [minSpeed, maxSpeed] = GEAR_SPEED_LIMITS.at(static_cast<int>(m_gear));
  
    if (m_gear == Gear::NeutralGear)
    {
        if (speed <= std::abs(m_speed))
        {
            m_speed = (m_speed < 0) ? -speed : speed;
            return true;
        }

        throw std::runtime_error("Cannot accelerate on neutral\n");
        return false;
    }

    // вынести в функцию условие
    if (IsSpeedInLimit(speed, minSpeed, maxSpeed))
    {
        m_speed = speed;
        if (m_gear == Gear::ReverseGear)
        {
            m_speed = -speed;
        }
        return true;
    }

    throw std::runtime_error("Speed is out of gear range\n");
    return false;
}

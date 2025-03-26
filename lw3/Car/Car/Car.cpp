#include "Car.h"
#include <iostream>
#include <utility>
#include <map>

using SpeedLimit = std::pair<int, int>;

const std::map<int, SpeedLimit> GEAR_SPEED_LIMITS = {
    { -1, { 0, 20 } },
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

    std::cout << "Ñar must be stopped and in neutral gear\n";
    return false;
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
    if (m_speed >= minSpeed && m_speed <= maxSpeed)
    {
        m_gear = static_cast<Gear>(gear);
        return true;
    }

    std::cout << "Unsuitable current speed";
    return false;
}

bool Car::SetGear(int gear)
{
    if (gear < -1 || gear > 5)
    {
        std::cout << "Invalid gear\n";
        return false;
    }

    if (!m_engineIsOn)
    {
        if (gear == 0)
        {
            m_gear = Gear::NeutralGear;
            return true;
        }

        std::cout << "Ñannot set gear while engine is off\n";
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
        std::cout << "Speed cannot be negative\n";
        return false;
    }

    if (!m_engineIsOn)
    {
        std::cout << "Cannot set speed while engine is off\n";
        return false;
    }

    auto [minSpeed, maxSpeed] = (m_gear == Gear::NeutralGear) ? 
        std::pair{ 0, std::abs(m_speed) } :
        GEAR_SPEED_LIMITS.at(static_cast<int>(m_gear));
  
    if (m_gear == Gear::NeutralGear)
    {
        if (speed <= std::abs(m_speed))
        {
            m_speed = (m_speed < 0) ? -speed : speed;
            return true;
        }

        std::cout << "Cannot accelerate on neutral\n";
        return false;
    }

    if (speed >= minSpeed && speed <= maxSpeed)
    {
        m_speed = speed;
        if (m_gear == Gear::ReverseGear)
        {
            m_speed = -speed;
        }
        return true;
    }

    std::cout << "Speed is out of gear range\n";
    return false;
}

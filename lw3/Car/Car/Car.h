#pragma once

enum class Gear
{
    ReverseGear = -1,
    NeutralGear,
    FirstGear,
    SecondGear,
    ThirdGear,
    FourthGear,
    FifthGear
};

enum class Direction
{
    Backward = -1,
    StandingStill = 0,
    Forward = 1
};

class Car
{
public:
    Car() = default;

    [[nodiscard]] bool IsTurnedOn() const;
    [[nodiscard]] Direction GetDirection() const;
    [[nodiscard]] int GetSpeed() const;
    [[nodiscard]] Gear GetGear() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);

private:
    bool ChangeGearBasedOnSpeed(int gear); 

    Gear m_gear = Gear::NeutralGear;
    bool m_engineIsOn = false;
    int m_speed = 0;
};
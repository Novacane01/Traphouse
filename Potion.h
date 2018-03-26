#pragma once
#include <string>
#include "Pickup.h"

class Player;

class Potion{
public:
	Potion(std::string, double, double);
protected:
    const std::string name;
    const double dropChance;
    const double duration;
};

class HealthPotion:public Potion{
public:
    HealthPotion() : Potion("Health Potion", 0.1, 10){}
    void Heal(Player *player);
};

class SpeedPotion:public Potion{
public:
    SpeedPotion():Potion("Speed Potion", 0.1, 20){}
    void Speed(Player *player);
};

class StaminaPotion:public Potion{
public:
    StaminaPotion():Potion("Stamina Potion", 0.1, 20){}
    void Stamina(Player *player);
};

class AttackPotion:public Potion{
public:
    AttackPotion():Potion("Attack Potion", 0.1, 20){}
    void increaseAttack(Player *player);
};

class TimePotion:public Potion{
public:
    TimePotion():Potion("Time Potion", 0.1, 20){}
    void slowTime();
};
//
// Created by Tyler Goodman on 3/22/18.
//
#include "Pickup.h"
#include "Player.h"

class Potion:Pickup {

public:
    Potion::Potion(std::string name, double dropChance, double duration):name(name), dropChance(dropChance),
    duration(duration){};
protected:
    const std::string name;
    const double dropChance;
    const double duration;
};

class HealthPotion:Potion{
public:
    HealthPotion() : Potion("Health Potion", 0.1, 10){}
    void Heal(Player *player);
};

class SpeedPotion:Potion{
public:
    SpeedPotion():Potion("Speed Potion", 0.1, 20){}
    void Speed(Player *player);
};

class StaminaPotion:Potion{
public:
    StaminaPotion():Potion("Stamina Potion", 0.1, 20){}
    void Stamina(Player *player);
};

class AttackPotion:Potion{
public:
    AttackPotion():Potion("Attack Potion", 0.1, 20){}
    void increaseAttack(Player *player);
};

class TimePotion:Potion{
public:
    TimePotion():Potion("Time Potion", 0.1, 20){}
    void slowTime();
};
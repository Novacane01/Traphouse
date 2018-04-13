#pragma once
#include <string>
#include "Player.h"

class Player;

class Potion{
public:
	Potion(std::string name, double dropchance, double duration);
	virtual void Use(Player *) = 0;
	const std::string getName() const;
	const double getDuration() const;
	const double getDropChance() const;
	void setUI();
	void displayPotionInfo(sf::RenderWindow &, Player *);

protected:
	sf::Sprite potion;
	sf::Text potionName;
	sf::Font font;
    const std::string name;
    const double dropChance;
    const double duration;
};

class HealthPotion:public Potion{
public:
    HealthPotion() : Potion("Health Potion", 0.1, 10){}
    void Use(Player *player);
};

class SpeedPotion:public Potion{
public:
    SpeedPotion():Potion("Speed Potion", 0.1, 20){}
    void Use(Player *player);
};

class StaminaPotion:public Potion{
public:
    StaminaPotion():Potion("Stamina Potion", 0.1, 20){}
    void Use(Player *player);
};

class AttackPotion:public Potion{
public:
    AttackPotion():Potion("Attack Potion", 0.1, 20){}
    void Use(Player *player);
};

class TimePotion:public Potion{
public:
    TimePotion():Potion("Time Potion", 0.1, 20){}
    void Use();
};
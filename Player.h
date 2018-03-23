#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include "Weapon.h"
#include "Potion.h"
#include <iostream>

class Player
{
public:
	 Player(std::string, int health = 100, double = 50);
	 void setName(std::string);
	 void setHp(int);
	 void setWalkSpeed(double);
	 std::string getName() const;
	 double getWalkspeed() const;
	 int getHp() const;
	 void setSprite();
	 bool setTexture(std::string);
	 sf::Sprite& getPlayer();
	 void MoveLeft(double);
	 void MoveUp(double);
	 void MoveDown(double);
	 void MoveRight(double);
	 void Update(double);
	 bool isMovingLeft = false;
	 bool isMovingRight = false;
	 bool isMovingUp = false;
	 bool isMovingDown = false;
	 void Draw(sf::RenderWindow &);
	 sf::Sprite player;
	 sf::Texture texture;
	 std::vector<Weapon> weaponInventory;
	 std::vector<Potion> potionInventory;
private:
	std::string name;
	int hp = 0;
	double walkspeed = 0;

public:
	Pickup pickups;
};
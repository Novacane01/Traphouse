#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include "Weapon.h"
#include "Potion.h"
#include <iostream>

//Player class
class Player{
public:
	friend class SpeedPotion;
	friend class AttackPotion;

	//Player
	 Player(std::string, int health = 100, double = 200);
	 void setName(std::string);
	 void setHp(int);
	 void setWalkSpeed(double);
	 std::string getName() const;
	 double getWalkspeed() const;
	 int getHp() const;
	 void setSprite();
	 bool setTexture(std::string);
	 sf::Sprite& getPlayer();

	 //Moving
	 void MoveLeft(double);
	 void MoveUp(double);
	 void MoveDown(double);
	 void MoveRight(double);
	 void Update(sf::RenderWindow &window, double);
	 bool isMovingLeft = false;
	 bool isMovingRight = false;
	 bool isMovingUp = false;
	 bool isMovingDown = false;
	 void Draw(sf::RenderWindow &);

	 //Weapons
	 std::vector<Weapon>& getWeapons();
	 Weapon& getCurrentWeapon();
	 void switchWeapons();
	 void setWeapon(Weapon &);

	 ~Player();
private:
	sf::Sprite player;
	sf::Texture texture;
	std::string name;
	std::vector<Weapon> weaponInventory;
	std::vector<Potion> potionInventory;
	int hp = 0;
	double walkspeed = 0;

public:
	Pickup pickups;
};
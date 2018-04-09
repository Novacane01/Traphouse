#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Weapon.h"
#include "Potion.h"
#include <iostream>

class Map;
//Player class
class Player{
public:
	friend class SpeedPotion;
	friend class AttackPotion;

	//Player
	 Player(std::string, int health = 100, float = 200.f);
	 void setName(std::string);
	 void setHp(int);
	 void setWalkSpeed(float);
	 std::string getName() const;
	 float getWalkspeed() const;
	 int getHp() const;
	 void setTexture(std::string);
	 sf::Sprite& getPlayer();

	 //Moving
	 void MoveLeft(float);
	 void MoveUp(float);
	 void MoveDown(float);
	 void MoveRight(float);
	 void Update(sf::RenderWindow &window, float, Map *);
	 bool isMovingLeft = false;
	 bool isMovingRight = false;
	 bool isMovingUp = false;
	 bool isMovingDown = false;
	 void Draw(sf::RenderWindow &);
	 //Raycasting
	 sf::RectangleShape rayUp;
	 sf::RectangleShape rayDown;
	 sf::RectangleShape rayLeft;
	 sf::RectangleShape rayRight;

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
	float walkspeed = 0;
	bool invulnerable;

public:
	Pickup pickups;
};
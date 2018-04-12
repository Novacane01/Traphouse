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
	 Player(std::string, float health = 100.f, float walkspeed= 200.f, float stamina = 500.f);
	 void setName(std::string);
	 void setHp(float);
	 void setMaxStamina(float);
	 void setCurrentStamina(float);
	 void setWalkSpeed(float);
	 const std::string getName() const;
	 float getWalkspeed() const;
	 float getHp() const;
	 float getMaxStamina() const;
	 float getCurrentStamina() const;
	 void setTexture(std::string);
	 sf::Sprite& getPlayer();
	 bool isDead() const;

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
	 bool bIsSprinting;
	 bool canSprint;

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

	 //UI
	 void setUI();
	 void displayPlayerInfo(sf::RenderWindow &);
	 ~Player();
private:
	sf::Sprite player;
	sf::Texture texture;
	std::string name;
	std::vector<Weapon> weaponInventory;
	std::vector<Potion> potionInventory;
	float hp = 0.f;
	float walkspeed = 0.f;
	float maxStamina = 0.f;
	float currentStamina = 0.f;
	bool invulnerable;
	bool bIsDead;

private:
	sf::RectangleShape healthBar;
	sf::RectangleShape staminaBar;
	sf::Text playerName;
	sf::Text hpNum;
	sf::Font font;
public:
	Pickup pickups;
};
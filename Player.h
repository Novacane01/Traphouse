#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Weapon.h"
#include "Potion.h"
#include <iostream>
#include <map>
#include <string>


//Player class
class Player{
public:
	//Player
	 Player(std::string, float health = 100.f, float defaultwalkspeed= 200.f, float stamina = 500.f);
	 //Setters
	 void setName(std::string);
	 void setCurrentHp(float);
	 void setMaxStamina(float);
	 void setCurrentStamina(float);
	 void setCurrentWalkSpeed(float);
	 void setTexture(std::string);
	 void setScore(int);
	 //Getters
	 const std::string getName() const;
	 float getCurrentWalkspeed() const;
	 float getDefaultWalkspeed() const;
	 float getMaxHp() const;
	 float getCurrentHp() const;
	 float getMaxStamina() const;
	 float getCurrentStamina() const;
	 sf::Sprite& getPlayer();
	 bool isDead() const;
	 int getScore();

	 //Moving
	 void MoveLeft(float);
	 void MoveUp(float);
	 void MoveDown(float);
	 void MoveRight(float);
	 void Update(sf::RenderWindow &window, float);
	 bool isMovingLeft = false;
	 bool isMovingRight = false;
	 bool isMovingUp = false;
	 bool isMovingDown = false;
	 bool canMoveLeft = false;
	 bool canMoveRight = false;
	 bool canMoveUp = false;
	 bool canMoveDown = false;
	 void Draw(sf::RenderWindow &);
	 bool bIsSprinting;
	 bool bCanSprint;
	 //Disables
	 bool slowed = false, stunned = false, poisoned = false;
	 sf::Clock poisonTimer;
	 //Buffs
	 bool empowered, triggerhappy, energized, stopwatch/*<-Subject to change*/; //Attack buff, Speed buff, Stamina buff, Time buff (respectively)

	 sf::Clock disableTimer;
	 std::vector<std::pair<std::string, float>> disables;
	 sf::Clock buffTimer;
	 std::vector<std::pair<std::string, float>> buffs;

	 //Weapons
	 std::vector<Weapon>& getWeapons();
	 Weapon& getCurrentWeapon();
	 void switchWeapons();
	 void setWeapon(Weapon &);
	 bool bCanShoot;
	 sf::Clock shootTimer;

	 //Potions
	 std::vector<Potion *>& getPotions();
	 Potion* getCurrentPotion();
	 void switchPotions();

	 //UI
	 void setUI();
	 void displayPlayerInfo(sf::RenderWindow &);
	 ~Player();

private:
	sf::Sprite player;
	sf::Texture texture;
	std::string name;
	std::vector<Weapon> weaponInventory;
	std::vector<Potion *> potionInventory;
	const float maxHp = 0.f;
	float currentHp = 0.f;
	const float defaultWalkspeed = 0.f;
	float currentWalkspeed = 0.f;
	float maxStamina = 0.f;
	float currentStamina = 0.f;
	bool invulnerable;
	bool bIsDead;
	float staminaUsage = .5f;
    int score = 0;

	//UI
	sf::RectangleShape healthBar;
	sf::RectangleShape staminaBar;
	sf::Text playerName;
	sf::Text hpNum;
	sf::Font font;
	sf::Text playerScore;
	std::vector<sf::RectangleShape> potionSlots;

};
#pragma once
#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include <string>
#include <cmath>

class Player;

//Weapon Class
class Weapon
{
public:
	friend class Enemy;
	Weapon& operator= (const Weapon& x) {
		return *this;
	}
	Weapon(std::string, float, int, float, float);
	Weapon(std::string, int maxAmmo, int currentMax, int currentClip, int maxClip, float damage, float attackSpeed, float dropChance);
	void Update(sf::RenderWindow &, Player *, float);
	void Draw(sf::RenderWindow &);
	void setCurrentMax(int);
	void setCurrentClip(int);
	void setMaxClip(int);
	void setAttackSpeed(float);
	void setDamage(float);
	std::string getName() const;
	int getMaxAmmo() const;
	int getCurrentMax() const;
	int getCurrentClip() const;
	int getMaxClip() const;
	float getDamage() const;
	float getAttackSpeed() const;
	float getDropChance()const;
	void displayWeaponInfo(sf::RenderWindow &);
	void Shoot(Player *, sf::RenderWindow &window);
	void Reload(Player *);
	void setUI();
	~Weapon();
private:
	struct Bullet {
		sf::Clock deleteTime;
		sf::Vector2f direction;
		float velocity = 1000.f;
		sf::CircleShape bullet;
	};
	const std::string name;
	const int maxAmmo = 0;
	const int range = 0;
	int currentMax = 0;
	int currentClip = 0;
	int maxClip = 0;
	float damage = 0.f;
	float attackSpeed = 0.f;
	const float dropChance = 0;
	std::vector<Bullet> bullets;
	sf::Sprite weapon;
	sf::Texture texture;
	sf::Clock attackTimer;
private:
	sf::Text ammoCount;
	sf::Font font;
	std::vector<sf::RectangleShape> ammoBlocks;
};

#pragma once
#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include <string>
#include <cmath>

class Player;
class Bullet;

//Weapon Class
class Weapon
{
public:
	friend class Enemy;
	Weapon& operator= (const Weapon& x) {
		return *this;
	}
	Weapon(std::string, float, int, float, float);
	Weapon(std::string, int, int, int, float, float, float);
	void Update(sf::RenderWindow &, Player *, float);
	void Draw(sf::RenderWindow &);
	void setCurrentMax(int);
	void setCurrentClip(int);
	void setAttackSpeed(float);
	void setDamage(float);
	std::string getName() const;
	int getMaxAmmo() const;
	int getCurrentMax() const;
	int getCurrentClip() const;
	float getDamage() const;
	float getAttackSpeed() const;
	float getDropChance()const;
	void Shoot(Player *,sf::RenderWindow &window);
	~Weapon();
private:
	const std::string name;
	const int maxAmmo = 0;
	const int range = 0;
	int currentMax = 0;
	int currentClip = 0;
	float damage = 0.f;
	float attackSpeed = 0.f;
	const float dropChance = 0;
	std::vector<Bullet> bullets;
	sf::Sprite weapon;
	sf::Texture texture;
};

//Bullet Class
class Bullet {
public:
	Bullet(Player *);
	void Update(sf::RenderWindow &, float);
	void Draw(sf::RenderWindow &);
	sf::CircleShape getBullet() const;
	void setDirection(sf::Vector2f &);
	float damage = 0.f;
	void setVelocity(float);
	float getVelocity() const;
private:
	sf::Vector2f direction;
	float velocity = 1000.f;
	sf::CircleShape bullet;
};
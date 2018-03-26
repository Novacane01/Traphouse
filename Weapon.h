#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Player;
class Bullet;

class Weapon
{
public:
	Weapon& operator= (const Weapon& x) {
		return *this;
	}
	Weapon(std::string, int, int, double, double);
	Weapon(std::string, int, int, int, double, double, double);
	void Update(sf::RenderWindow &, Player *, double);
	void Draw(sf::RenderWindow &);
	void setCurrentMax(int);
	void setCurrentClip(int);
	void setAttackSpeed(double);
	void setDamage(double);
	std::string getName() const;
	int getMaxAmmo() const;
	int getCurrentMax() const;
	int getCurrentClip() const;
	double getDamage() const;
	double getAttackSpeed() const;
	double getDropChance()const;
	void Shoot(Player *,sf::RenderWindow &window);
	~Weapon();
private:
	const std::string name;
	const int maxAmmo = 0;
	const int range = 0;
	int currentMax = 0;
	int currentClip = 0;
	double damage = 0;
	double attackSpeed = 0;
	const double dropChance = 0;
	std::vector<Bullet> bullets;
	sf::Sprite weapon;
	sf::Texture texture;
};

class Bullet {
public:
	Bullet(Player *);
	void Update(double);
	void Draw(sf::RenderWindow &);
	void setDirection(sf::Vector2f);
	void setVelocity(double);
	double getVelocity() const;
private:
	sf::Vector2f direction;
	double velocity = 1000;
	sf::CircleShape bullet;
};
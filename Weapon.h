#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <cmath>
#include <thread>

class Player;

//Weapon Class
class Weapon
{
private:
	struct Bullet {
		sf::Clock deleteTime;
		sf::Vector2f direction;
		float velocity = 2000.f;
		sf::CircleShape bullet;
		float damage = 0.f;
	};
public:
	friend class Enemy;
	Weapon& operator= (const Weapon& x) {
		return *this;
	}
	Weapon();
	Weapon(std::string type,std::string name, float, int, float, float);
	Weapon(std::string type, std::string name, int maxAmmo, int currentMax, int currentClip, int maxClip, float damage, float attackSpeed,
		float reloadTime,float deviation, float dropChance, std::string shootFX);
	void Update(sf::RenderWindow &, Player *, float);
	void Draw(sf::RenderWindow &);
	//Setters
	void setCurrentMax(int);
	void setCurrentClip(int);
	void setMaxClip(int);
	void setAttackSpeed(float);
	void setDamage(float);
	void setReloadTime(float);
	Bullet createBullet(Player *, sf::RenderWindow &window);
	//Getters
	std::string getType() const;
	std::string getName() const;
	int getMaxAmmo() const;
	int getCurrentMax() const;
	int getCurrentClip() const;
	int getMaxClip() const;
	float getDamage() const;
	float getAttackSpeed() const;
	float getDropChance()const;
	//Misc.
	void displayWeaponInfo(sf::RenderWindow &);
	void Shoot(Player *, sf::RenderWindow &window);
	void Reload(Player *);
	void canReload(Player *);
	void setUI();
	//Audio
	void playAudio(sf::SoundBuffer *);
	~Weapon();

	//Audio
	void loadBuffer(sf::SoundBuffer &, std::string);
	bool bIsReloading;
	bool bCanReload = true;

	static std::map<std::string,Weapon *> weaponList;

private:
	static bool gunsLoaded;
	//Weapon Properties
	const std::string type;
	const std::string name;
	const int maxAmmo = 0;
	const int range = 0;
	const float deviation = 0.f;
	int currentMax = 0;
	int currentClip = 0;
	int maxClip = 0;
	float damage = 0.f;
	float attackSpeed = 0.f;
	const float dropChance = 0;
	float reloadTime = 0.f;
	sf::SoundBuffer FXgunshot;
	sf::SoundBuffer FXreload;
	//
	std::vector<Bullet> bullets;
	sf::Sprite weapon;
	sf::Texture texture;
	sf::Clock reloadTimer;

//UI
private:
	sf::Text gunName;
	sf::Text ammoCount;
	sf::Font font;
	std::vector<sf::RectangleShape> ammoBlocks;
};

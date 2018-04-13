#pragma once
#include "SFML/Graphics.hpp"

class Player;
class Enemy
{
public:
	Enemy& operator= (const Enemy& x) {
		return *this;
	}
	Enemy(std::string, int, float, float);
    void setHp(int);
	void setWalkspeed(float);
	void setAttack(float);
	float getAttack() const;
	void setTexture(std::string);
	void Spawn();
	std::string getName() const;
 	float getWalkspeed() const;
	int getHp() const;
 	sf::Sprite getEnemy() const;
	bool isDead();
 	void Update(Player *,float);
	static void Spawn(Player *, int, int);
	void setDirection(sf::Vector2f &);
	~Enemy();
	
private:
	sf::Vector2f direction;
	bool dead;
	sf::Sprite enemy;
	sf::Texture texture;
	const std::string name;
	int hp = 0;
	float walkspeed = 0.f;
	float attack = 0.f;
	sf::Vector2f spawnlocation;
};

class Skeleton:public Enemy {
public:
	Skeleton();
	void boneWhack(Player *);
	void boneThrow(Player *);
	void walkAnim();
	void Update(Player *, float);
private:
};


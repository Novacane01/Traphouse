#include "GameManager.h"

class Enemy
{
public:
	Enemy();
    void setHp(int);
	void setWalkspeed(double);
	void Spawn();
	std::string getName() const;
 	int getWalkspeed();
	int getHp() const;
	int getAttack() const;
 	sf::Sprite getEnemy() const;
 	void Update(double);
	~Enemy();
private:
	int hp = 0;
	double walkspeed = 0;
	int attack = 0;
	sf::Vector2f spawnlocation;
};


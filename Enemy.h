#pragma once
#include "SFML\Graphics.hpp"

class Player;
class Enemy
{
public:
	Enemy& operator= (const Enemy&) {
		return *this;
	}
	Enemy(std::string, int, float, float, float);
	//Setters
    void setHp(int);
	void setWalkspeed(float);
	void setAttack(float);
	void setTexture(sf::Sprite &, sf::Texture &, std::string);
	void setDirection(sf::Vector2f &);
	void setAttackSpeed(float);
	//Getters
	static std::vector<Enemy *> & getEnemies();
	sf::Vector2f getDirection() const;
	std::string getName() const;
	float getAttackSpeed() const;
	float getAttack() const;
 	float getWalkspeed() const;
	int getHp() const;
 	sf::Sprite getEnemy() const;
	//Booleans
	bool isDead()const;
	void isHit(Player *);
	//Misc.
	virtual void Update(Player *, float) = 0;
	virtual void Draw(sf::RenderWindow &) = 0;
	static void Spawn(Enemy *);
	static void Destroy(std::vector<Enemy *>::iterator &);
	~Enemy();
	
private:
	static std::vector<Enemy *> enemies;
	sf::Vector2f direction;
	bool bIsDead;
	const std::string name;
	int hp = 0;
	float walkspeed = 0.f;
	float attack = 0.f;
	float attackSpeed = 0.f;
	sf::Vector2f spawnlocation;

protected:
	sf::Sprite enemy;
	sf::Texture texture;
};

class Skeleton:public Enemy {
public:
	Skeleton();
	void boneWhack(Player *);
	void boneThrow(Player *);
	void walkAnim();
	void Update(Player *, float);
	void Draw(sf::RenderWindow &);
private:
	sf::Clock attackTimer;
	sf::Clock animationTimer;
	sf::IntRect rectSourceSprite;
	struct Bone {
		sf::Sprite bone;
		sf::Texture texture;
		sf::Vector2f direction;
		sf::Vector2f position;
		float velocity = 250.f;
		sf::Clock deleteTimer;
	}bone;
	std::vector<Bone> bones;
};


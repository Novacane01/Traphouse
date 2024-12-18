#pragma once
#include <SFML/Graphics.hpp>
#include "LinkedMap.h"

class Player;
class Enemy
{
public:
	enum class animationState {WALKING, IDLE, MELEE, RANGED, DEAD } state;
	enum class behaviour { AGGRESSIVE, PASSIVE }mode;

	Enemy& operator= (const Enemy&) {
		return *this;
	}
	Enemy(std::string, int, float, float, float);
	int scoreValue;

	//Setters
    void setHp(int);
	void setWalkspeed(float);
	void setAttack(float);
	void setTexture(sf::Sprite &, sf::Texture &, std::string);
	void setAttackSpeed(float);
	void setDirection(sf::Vector2f);
	void setPosition(LinkedMap::room*);
	//Getters
	static std::vector<Enemy *> &getEnemies();
	sf::Vector2f getDirection() const;
	std::string getName() const;
	float getAttackSpeed() const;
	float getAttack() const;
 	float getWalkspeed() const;
	int getHp() const;
 	sf::Sprite* getEnemy();
	sf::Vector2f getUDirection(sf::Vector2f &);
	//Booleans
	bool isDead()const;
	void isHit(Player *);
	//Drawing
	//Misc.
	static std::vector<Enemy *> enemies;
	virtual void Update(Player *, float) = 0;
	virtual void Draw(sf::RenderWindow &) = 0;
	virtual void Animate(Player *) = 0;

	static void Spawn(Enemy *,LinkedMap::room *);

	static void Destroy(std::vector<Enemy *>::iterator);
	~Enemy();
	
private:

	sf::Vector2f direction;
	const std::string name;
	int hp = 0;
	float walkspeed = 0.f;
	float attack = 0.f;
	float attackSpeed = 0.f;
	sf::Vector2f spawnlocation;

	int colour;

protected:
	sf::Sprite enemy;
	//Animation
	sf::Clock attackTimer;
	sf::Clock animationTimer;
	sf::Clock deathTimer;

	sf::IntRect AttackRect;
	sf::IntRect WalkRect;
	sf::IntRect DeathRect;
	sf::IntRect RangedRect;

	sf::Texture attackTexture;
	sf::Texture	walkTexture;
	sf::Texture	deathTexture;
	sf::Texture rangedTexture;
	LinkedMap::room* room;

	bool bIsDead;
};

class Skeleton:public Enemy {
public:
	Skeleton(std::string name = "Skeleton", float hp = 100.f, float attack = 10.f, float walkspeed = 100.f, float attackspeed = 2.f, std::string type = "Regular");
	void boneWhack(Player *);
	void boneThrow(Player *);
	void Update(Player *, float);
	void Draw(sf::RenderWindow &);
	void Animate(Player *);
private:
	struct Bone {
		sf::Sprite bone;
		sf::Texture texture;
		sf::Vector2f direction;
		float velocity = 250.f;
		sf::Clock deleteTimer;
	}bone;
	std::vector<Bone> bones;
	const std::string type;
};

class Spider :public Enemy {
public:
	Spider(std::string name = "Spider", float hp = 30.f, float attack = 2.f, float walkspeed = 200.f, float attackspeed = 2.f);
	void webShot(Player *);
	void Bite(Player *);
	void Update(Player *, float);
	void Animate(Player *);
	void Draw(sf::RenderWindow &);
private:
	struct Web {
		sf::Sprite web;
		sf::Texture texture;
		sf::Vector2f direction;
		float velocity = 750.f;
		sf::Clock deleteTimer;
	}web;
	std::vector<Web> webs;
};

class Troll :public Enemy {
public:
    Troll(std::string name = "Troll", float hp = 500.f, float attack = 30, float walkspeed = 25.f, float attackspeed = 3.f);
    void groundSmash(Player *);
    void melee(Player *);
    void Update(Player *, float);
    void Animate(Player *);
    void Draw(sf::RenderWindow &);
private:

};

class Demon:public Enemy {
public:
    Demon(std::string name = "Demon", float hp = 1000.f, float attack = 25.f, float walkspeed = 150.f, float attackspeed = 2.f);
    void swipe(Player *);
    void fireball(Player *);
    void Update(Player *, float);
    void Draw(sf::RenderWindow &);
    void Animate(Player *);
    void spawnMinions(LinkedMap::room *linkedMap);

private:
    int spawnClock;
    int numSpawned;
    struct Flameball {
        sf::Sprite flameball;
        sf::Texture texture;
        sf::Vector2f direction;
		sf::IntRect flameballRect = sf::IntRect(0,0,15,19);
        float velocity = 450.f;
        sf::Clock deleteTimer;
    }flameball;
    std::vector<Flameball> flameballs;
};
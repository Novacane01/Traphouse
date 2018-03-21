#include "SFML\\Graphics.hpp"

class Player
{
public:
	 Player();
	 void setName(std::string);
	 void setLevel(int);
	 void setHp(int);
	 void setAttack(int);
	 void setWalkspeed(double);
	 void setLevel(int);
	 void LevelUp();
	 std::string getName();
	 int getLevel();
	 int getWalkspeed();
	 int getHp();
	 int getAttack();
	 sf::Sprite() getPlayer();
	 void Update(double);
	~Player();
	
private:
	const std::string name;
	sf::Spirte player;
	sf::Texture texture;
	int level 0;
	int hp = 0;
	int attack = 0;
	double walkspeed = 0;
};
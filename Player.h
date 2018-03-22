#include "GameManager.h"

class Player
{
public:
	 Player(std::string, int, int, double);
	 void setName(std::string);
	 void setHp(int);
	 void setAttack(int);
	 void setWalkSpeed(double);
	 std::string getName() const;
	 double getWalkspeed() const;
	 int getHp() const;
	 int getAttack() const;
	 void setSprite(sf::Texture &);
	 bool setTexture(std::string);
	 sf::Sprite getPlayer() const;
	 void Update(double);
	~Player();
	
private:
	std::string name;
	sf::Sprite player;
	sf::Texture texture;
	int hp = 0;
	int attack = 0;
	double walkspeed = 0;
};
#include "Pickup.h"

class Weapon:Pickup
{
public:
	Weapon(std::string, int, int, double, sf::Texture &);
	void Update(double);
	void setAmmo(int);
	void setName(std::string);
	std::string getName() const;
	int getAmmo() const;
	void setAttackSpeed(double);
	double getAttackSpeed() const;
	~Weapon();
private:
	double attackspeed = 0;
	int ammo = 0;
	int damage = 0;
	const std::string name;
	sf::Sprite weapon;
	sf::Texture texture;
};
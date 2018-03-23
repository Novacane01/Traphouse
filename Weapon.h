#include "Pickup.h"

class Weapon:Pickup
{
public:
	Weapon(std::string, int, int, int, double, double, double);
	void Update(double);
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
private:
	const std::string name;
	const int maxAmmo = 0;
	int currentMax = 0;
	int currentClip = 0;
	double damage = 0;
	double attackSpeed = 0;
	const double dropChance = 0;
	sf::Sprite weapon;
	sf::Texture texture;
#include "GameManager.h"
#include "Weapon.h"

class Pickup
{
public:
	Pickup();
	static Weapon defaultPistol;
	static Weapon heavyPistol;
	static Weapon boltSniper;
	static Weapon semiAuto;
	static Weapon shotGun;
	static Weapon assaultRifle;
	static Weapon miniGun;
	static Weapon subMachine;
	~Pickup();
private:
};
#pragma once
#include "Weapon.h"

class Pickup
{
public:
	Pickup();
	Weapon defaultKnife;
	Weapon defaultPistol;
	Weapon heavyPistol;
	Weapon boltSniper;
	Weapon semiAuto;
	Weapon shotgun;
	Weapon assaultRifle;
	Weapon minigun;
	Weapon semiSniper;
	Weapon submachine;
	void initialize();
private:
	
};
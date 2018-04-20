//#include "stdafx.h"
#include "Chest.h"

Chest::Chest() {
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.f,1.f);
	float n = dis(gen);
	if (n < .45f) {
		fillChestWeapons();
	}
	else if(n<.9f){
		fillChestPotions();
	}
	else {
		fillChestWeapons();
		fillChestPotions();
	}
	std::cout << "Chest size: " <<weaponContents.size()+potionContents.size()<< std::endl;
}

void Chest::Open(Player *player) {
	if (weaponContents.size() == 1) {
		player->getWeapons().push_back(*weaponContents[0]);
		std::cout << weaponContents[0]->getName() << " added" << std::endl;
	}
	if (potionContents.size() == 1) {
		player->getPotions().push_back(potionContents[0]);
		std::cout << potionContents[0]->getName() << " added" << std::endl;
	}
}

std::vector<Weapon *>& Chest::getWeaponContents() {
	return weaponContents;
}

std::vector<Potion *>& Chest::getPotionContents() {
	return potionContents;
}

void Chest::fillChestWeapons() {
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.f, 1.f);
	float r = dis(gen);
	int i = 0;
	for(std::map<std::string,Weapon *>::iterator it = Weapon::weaponList.begin();it!=Weapon::weaponList.end();it++) {
		if (r -= it->second->getDropChance()) {
			weaponContents.push_back(it->second);
		}
	};
}

void Chest::fillChestPotions() {
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.f, 1.f);
	float r = dis(gen);
	if (r < .2f) {
		potionContents.push_back(new HealthPotion());
	}
	else if (r < .4f) {
		potionContents.push_back(new StaminaPotion());
	}
	else if (r < .6f) {
		potionContents.push_back(new SpeedPotion());
	}
	else if (r<.8f) {
		potionContents.push_back(new AttackPotion());
	}
	else {
		potionContents.push_back(new TimePotion());
	}
}

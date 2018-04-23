#include "stdafx.h"
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
	if(!opened) {
		opened = true;
		if (weaponContents.size() == 1) {
			if(player->getWeapons().size()>1){
				player->getWeapons()[1] = *weaponContents[0];
			}
			else {
				player->getWeapons().push_back(*weaponContents[0]);
			}
			std::cout << weaponContents[0]->getName() << " added" << std::endl;
		}
		if (potionContents.size() == 1) {
			player->getPotions().push_back(potionContents[0]);
			std::cout << potionContents[0]->getName() << " added" << std::endl;
		}
		if (closedTexture.loadFromFile("Sprites/Map/openchest.png")) {
			chest.setTexture(closedTexture);
		}
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
	for(std::map<std::string,Weapon *>::iterator it = Weapon::weaponList.begin();it!=Weapon::weaponList.end()&&r>=0;it++) {
		r -= it->second->getDropChance();
		if (r<=0) {
			weaponContents.push_back(it->second);
		}
	};
}

sf::Sprite Chest::getChestSprite(){
    return chest;
}

void Chest::setData(float x, float y){
	if (openTexture.loadFromFile("Sprites/Map/chest.png")) {
		chest.setTexture(openTexture);
		chest.setOrigin(chest.getGlobalBounds().width / 2, chest.getGlobalBounds().height / 2);
		chest.setPosition(x, y);
	}
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

bool Chest::getIsOpen(){
    return opened;
}


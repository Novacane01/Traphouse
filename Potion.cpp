#include "stdafx.h"
#include "Potion.h"

Potion::Potion(std::string name, double dropChance, double duration) :name(name), dropChance(dropChance),
duration(duration) {
	setUI();
};

//Returns potion name
const std::string Potion::getName() const {
	return name;
}

//Returns potion duration
const double Potion::getDuration() const {
	return duration;
}

//Returns potion drop chance
const double Potion::getDropChance() const{
	return dropChance;
}

void Potion::displayPotionInfo(sf::RenderWindow &window, Player *player) {
	for (unsigned i = 0; i < player->getPotions().size();i++) {
		window.draw(player->getPotions()[i]->potion);
	}
}
void Potion::setUI() {
	if (!font.loadFromFile("Fonts\\light_pixel-7.ttf")) {
		std::cout << "Could not load font from file" << std::endl;
	}

}

void HealthPotion::Use(Player *player) {
    player->setCurrentHp(player->getMaxHp());
}

void SpeedPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Speed", 20.f));
}

void StaminaPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Stamina", 20.f));
}

void AttackPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Attack", 20.f));
}

void TimePotion::Use() {

}


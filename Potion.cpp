#include "Potion.h"
#include "Player.h"

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

sf::Sprite Potion::getPotionSprite(){
	return potion;
}


void Potion::setUI() {
	if (!font.loadFromFile("Fonts/light_pixel-7.ttf")) {
		std::cout << "Could not load font from file" << std::endl;
	}
	if(name == "Speed Potion"){
		if(potionTexture.loadFromFile("Sprites/Potions/speed.png")){
			potion.setTexture(potionTexture);
		}
		potion.setOrigin(potion.getGlobalBounds().width/2,potion.getGlobalBounds().height/2);
	}
	if(name == "Health Potion"){
		if(potionTexture.loadFromFile("Sprites/Potions/Health.png")){
			potion.setTexture(potionTexture);
		}
		potion.setOrigin(potion.getGlobalBounds().width/2,potion.getGlobalBounds().height/2);
	}
	if(name == "Stamina Potion"){
		if(potionTexture.loadFromFile("Sprites/Potions/stamina.png")){
			potion.setTexture(potionTexture);
		}
		potion.setOrigin(potion.getGlobalBounds().width/2,potion.getGlobalBounds().height/2);
	}
	if(name == "Time Potion"){
		if(potionTexture.loadFromFile("Sprites/Potions/time.png")){
			potion.setTexture(potionTexture);
		}
		potion.setOrigin(potion.getGlobalBounds().width/2,potion.getGlobalBounds().height/2);
	}
	if(name == "Attack Potion"){
		if(potionTexture.loadFromFile("Sprites/Potions/attack.png")){
			potion.setTexture(potionTexture);
		}
		potion.setOrigin(potion.getGlobalBounds().width/2,potion.getGlobalBounds().height/2);
	}

}

//Fully restores player Hp
void HealthPotion::Use(Player *player) {
    player->setCurrentHp(player->getMaxHp());
}

//Increases player movement speed and attackspeed
void SpeedPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Speed", 20.f));
}

//Sets stamina usage to 0
void StaminaPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Stamina", 20.f));
}

//Increase weapon damage
void AttackPotion::Use(Player *player) {
	player->buffs.push_back(std::pair <std::string, float>("Attack", 20.f));
}

//Slows down movespeed and attackspeed of all enemies
void TimePotion::Use(Player *player) {
	player->buffs.push_back(std::pair<std::string, float>("Time", 10.f));
}


#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include <exception>
#include <cmath>

//Weapon(Melee) Constructor
Weapon::Weapon(std::string meleeName, float damage, int range, float attackspeed, float dropChance):name(meleeName),range(range),dropChance(dropChance) {
	setDamage(damage);
	setAttackSpeed(attackspeed);
}

//Weapon(Ranged) Construtor
Weapon::Weapon(std::string gunName, int MaxAmmo, int currentMax, int currentClip, int maxClip, float damage,
float attackspeed, float DropChance):name(gunName),maxAmmo(MaxAmmo),dropChance(DropChance){
    setCurrentClip(currentClip);
    setCurrentMax(currentMax);
    setDamage(damage);
    setAttackSpeed(attackspeed);
	setMaxClip(maxClip);
}

//Shoots bullet
void Weapon::Shoot(Player *player,sf::RenderWindow &window) {
	if (player->getCurrentWeapon().getCurrentClip() > 0) {
		//Instantiating bullet
		Bullet b;
		b.bullet.setRadius(2.5f);
		b.bullet.setPosition(player->getPlayer().getPosition());

		//Setting accuracy
		sf::Vector2f WorldCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f dVector = WorldCoords - player->getPlayer().getPosition();
		float newX1 = dVector.x*cos(5 * 3.14f / 180) - dVector.y*sin(5 * 3.14f / 180);
		float newY1 = dVector.x*sin(5 * 3.14f / 180) + dVector.y*cos(5 * 3.14f / 180);
		float newX2 = dVector.x*cos(-5 * 3.14f / 180) - dVector.y*sin(-5 * 3.14f / 180);
		float newY2 = dVector.x*sin(-5 * 3.14f / 180) + dVector.y*cos(-5 * 3.14f / 180);
		float n = ((newX2 - newX1) * ((float)rand() / RAND_MAX)) + newX1;
		float n2 = ((newY2 - newY1) * ((float)rand() / RAND_MAX)) + newY1;
		sf::Vector2f newDir = sf::Vector2f(n, n2);
		float mag = sqrt(pow(newDir.x, 2) + pow(newDir.y, 2));
		b.direction = sf::Vector2f(newDir.x / mag, newDir.y / mag);
		bullets.push_back(b);

		//Subtracting from current ammo
		player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getCurrentClip() - 1);
	}
	else if (player->getCurrentWeapon().getCurrentClip()==0&&player->getCurrentWeapon().getCurrentMax()>0) {
		Reload(player);
	}
	else {
		std::cout << "Out of ammo" << std::endl;
	}
}

//Reloads current weapon
void Weapon::Reload(Player *player) {
	if (player->getCurrentWeapon().getCurrentClip() == player->getCurrentWeapon().getMaxClip()) {
		std::cout << "Clip Full" << std::endl;
	}
	else {
		player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getMaxClip());
		player->getCurrentWeapon().setCurrentMax(player->getCurrentWeapon().getCurrentMax() - player->getCurrentWeapon().getMaxClip());
		std::cout << "Reloading" << std::endl;
	}
}

//Returns weapon max clip
int Weapon::getMaxClip() const {
	return maxClip;
}

//Updates weapon position
void Weapon::Update(sf::RenderWindow &window, Player *player,float dt){
	for (unsigned i = 0;i < bullets.size();i++) {
		bullets[i].bullet.move(bullets[i].direction.x*dt*bullets[i].velocity, bullets[i].direction.y*dt*bullets[i].velocity);
		if (bullets[i].deleteTime.getElapsedTime().asSeconds() > 3) {
			std::cout << "Deleting bullet" << std::endl;
			bullets.erase(bullets.begin() + i);
		}
	}
	//weapon.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	Draw(window);
}

//Draws weapon to screen
void Weapon::Draw(sf::RenderWindow &window) {
	window.draw(weapon);
	for (unsigned i = 0;i < bullets.size();i++) {
		window.draw(bullets[i].bullet);
	}
}

//Sets current clip of weapon
void Weapon::setCurrentClip(int currentClip) {
    this->currentClip = currentClip;
}

//Sets current max clip of weapon
void Weapon::setCurrentMax(int currentMax) {
    this->currentMax = currentMax;
}

//Sets max clip of weapon
void Weapon::setMaxClip(int maxClip) {
	this->maxClip = maxClip;
}

//Sets weapon damage
void Weapon::setDamage(float damage) {
    this->damage = damage;
}

//Sets weapon attackspeed
void Weapon::setAttackSpeed(float attackSpeed) {
    this->attackSpeed = attackSpeed;
	
}

//Returns weapon name
std::string Weapon::getName() const{
    return name;
}

//Returns weapon's max ammo
int Weapon::getMaxAmmo() const{
    return maxAmmo;
}

//Returns weapon's current ammo
int Weapon::getCurrentMax() const{
    return currentMax;
}

//Returns weapon's current clip
int Weapon::getCurrentClip() const{
    return currentClip;
}

//Returns weapon's damage
float Weapon::getDamage() const{
    return damage;
}

//Returns weapons' attackspeed
float Weapon::getAttackSpeed() const{
    return attackSpeed;
}

//Returns weapon's drop chance
float Weapon::getDropChance() const {
    return dropChance;
}

//Weapon Deconstructor
Weapon::~Weapon() {

}
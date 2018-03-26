#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"

//Weapon(Melee) Constructor
Weapon::Weapon(std::string meleeName, int damage, int range, double attackspeed, double dropChance):name(meleeName),range(range),dropChance(dropChance) {
	setDamage(damage);
	setAttackSpeed(attackspeed);
}

//Weapon(Ranged) Construtor
Weapon::Weapon(std::string gunName, int MaxAmmo, int currentMax, int currentClip, double damage,
double attackspeed, double DropChance):name(gunName),maxAmmo(MaxAmmo),dropChance(DropChance){
    setCurrentClip(currentClip);
    setCurrentMax(currentMax);
    setDamage(damage);
    setAttackSpeed(attackspeed);
}

//Shoots bullet
void Weapon::Shoot(Player *player,sf::RenderWindow &window) {
	std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
	std::cout << player->getPlayer().getPosition().x << " " << player->getPlayer().getPosition().y << std::endl;
	Bullet b(player);
	b.setDirection((sf::Vector2f)sf::Mouse::getPosition(window)-player->getPlayer().getPosition());
	bullets.push_back(b);
}

//Updates weapon position
void Weapon::Update(sf::RenderWindow &window, Player *player,double dt){
	for (unsigned i = 0;i < bullets.size();i++) {
		bullets[i].Update(dt);
		bullets[i].Draw(window);
	}
	//weapon.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	Draw(window);
}

//Draws weapon to screen
void Weapon::Draw(sf::RenderWindow &window) {
	window.draw(weapon);
}

//Sets current clip of weapon
void Weapon::setCurrentClip(int currentClip) {
    this->currentClip = currentClip;
}

//Sets max clip of weapon
void Weapon::setCurrentMax(int currentMax) {
    this->currentMax = currentMax;
}

//Sets weapon damage
void Weapon::setDamage(double damage) {
    this->damage = damage;
}

//Sets weapon attackspeed
void Weapon::setAttackSpeed(double attackSpeed) {
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
double Weapon::getDamage() const{
    return damage;
}

//Returns weapons' attackspeed
double Weapon::getAttackSpeed() const{
    return attackSpeed;
}

//Returns weapon's drop chance
double Weapon::getDropChance() const {
    return dropChance;
}

//Weapon Deconstructor
Weapon::~Weapon() {

}



//Bullet Constructor
Bullet::Bullet(Player *player) {
	bullet.setRadius(2.5);
	bullet.setFillColor(sf::Color::White);
	bullet.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
}

void Bullet::setDirection(sf::Vector2f dVector) {
	sf::Vector2f uVector;
	double mag = sqrt(pow(dVector.x, 2) + pow(dVector.y, 2));
	uVector.x = dVector.x / mag;
	uVector.y = dVector.y / mag;
	direction = uVector;
}

//Updates bullet's position
void Bullet::Update(double dt) {
	bullet.setPosition(bullet.getPosition().x +(velocity*dt*direction.x), bullet.getPosition().y + (velocity*dt*direction.y));
}

//Draws bullet to screen
void Bullet::Draw(sf::RenderWindow &window) {
	window.draw(bullet);
}



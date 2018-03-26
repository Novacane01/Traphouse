//
// Created by Tyler Goodman on 3/22/18.
//

#include "Weapon.h"

Weapon::Weapon(std::string meleeName, int damage, int range, double attackspeed, double dropChance):name(meleeName),range(range),dropChance(dropChance) {
	setDamage(damage);
	setAttackSpeed(attackspeed);
}

Weapon::Weapon(std::string gunName, int MaxAmmo, int currentMax, int currentClip, double damage,
double attackspeed, double DropChance):name(gunName),maxAmmo(MaxAmmo),dropChance(DropChance){
    setCurrentClip(currentClip);
    setCurrentMax(currentMax);
    setDamage(damage);
    setAttackSpeed(attackspeed);
}

void Weapon::Update(double){

}

void Weapon::setCurrentClip(int currentClip) {
    this->currentClip = currentClip;
}

void Weapon::setCurrentMax(int currentMax) {
    this->currentMax = currentMax;
}

void Weapon::setDamage(double damage) {
    this->damage = damage;
}

void Weapon::setAttackSpeed(double attackSpeed) {
    this->attackSpeed = attackSpeed;
}

std::string Weapon::getName() const{
    return name;
}

int Weapon::getMaxAmmo() const{
    return maxAmmo;
}

int Weapon::getCurrentMax() const{
    return currentMax;
}

int Weapon::getCurrentClip() const{
    return currentClip;
}

double Weapon::getDamage() const{
    return damage;
}

double Weapon::getAttackSpeed() const{
    return attackSpeed;
}

double Weapon::getDropChance() const {
    return dropChance;
}

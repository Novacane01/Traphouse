//
// Created by Tyler Goodman on 3/22/18.
//
#include "Weapon.h"

Weapon::Weapon(std::string name, int maxAmmo, int currentMax, int currentClip, double damage,
               double attackspeed, double dropChance):name(name),maxAmmo(maxAmmo),
                                                      dropChance(dropChance){

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

void Weapon::setAttackSpeed(double) {
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

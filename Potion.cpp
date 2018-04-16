//#include "stdafx.h"
#include "Potion.h"
#include "Player.h"

Potion::Potion(std::string name, double dropChance, double duration) :name(name), dropChance(dropChance),
duration(duration) {};

void HealthPotion::Heal(Player *player) {
    player->setCurrentHp(player->getMaxHp());
}

void SpeedPotion::boostSpeed(Player *player) {
    player->setWalkSpeed(1.5f * player->getWalkspeed());
    for(Weapon i:player->weaponInventory){
        i.setAttackSpeed(1.5f * i.getAttackSpeed());
    }
}

void StaminaPotion::increaseStamina(Player *player) {

}

void AttackPotion::increaseAttack(Player *player) {
    for(Weapon i:player->weaponInventory){
        i.setDamage(1.5f * i.getDamage());
    }
}

void TimePotion::slowTime() {

}


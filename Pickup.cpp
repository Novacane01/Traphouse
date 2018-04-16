//#include "stdafx.h"
#include "Pickup.h"

Pickup::Pickup():defaultKnife("Melee","Knife", 100000.f, 2, .5f, 0.f),defaultPistol("Pistol","M1911", 88, 88, 8, 8, 10.f, 0.25f,1.f, 2.5f, 0.f),
heavyPistol("Pistol", "Desert Eagle", 35, 35, 7, 7, 50.f, .5f, 2.f, 2.f, 0.15f), boltSniper("Bolt Sniper", "L96A1", 15, 15, 5, 5, 100.f, 2.f, 4.f, 0.f,0.02f),
semiAuto("SemiAuto", "M14", 60, 60, 10, 10, 25.f, .4f, 2.f,1.f, 0.05f), shotgun("Shotgun","KSG", 30, 30, 6, 6, 20.f, 1.f, 0.f, 5.f, 0.05f), assaultRifle("Assault Rifle","AK47", 90, 90, 30, 30, 30.f, .1f,2.f,5.f, .04f),
minigun("Minigun","Minigun", 180, 180, 180, 180, 20.f, .05f,5.f,7.5f, .02f),semiSniper("Semi Sniper","Barrett .50 Cal", 30, 30, 10, 10, 80.f, .5f,4.f ,0.f, .02f),
submachine("Submachine Gun","MP40", 96, 96, 32, 32, 20.f, .4f,2.f,2.5f, .1f){}
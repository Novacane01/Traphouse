
#include "Pickup.h"

Pickup::Pickup():defaultKnife("Knife", 100000.f, 2, .5f, 0.f),defaultPistol("M1911", 88, 88, 8, 10.f, 0.25f, 0.f),
heavyPistol("Desert Eagle", 35, 35, 7.f, 50, .5f, 0.15f), boltSniper("L96A1", 15, 15, 5, 100.f, 2.f, 0.02f),
semiAuto("M14", 60, 60, 10, 25.f, .4f, 0.05f), shotgun("KSG", 30, 30, 6, 20.f, 1.f, 0.05f), assaultRifle("AK47", 90, 90, 30, 30.f, .1f, .04f),
minigun("Minigun", 180, 180, 180, 20.f, .05f, .02f),semiSniper("Barrett .50 Cal", 30, 30, 10, 80.f, .5f, .02f),
submachine("MP40", 96, 96, 32, 20.f, .4f, .1f){}
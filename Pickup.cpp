
#include "Pickup.h"

Pickup::Pickup():defaultKnife("Knife", 100000, 2, 1 / 2, 0),defaultPistol("M1911", 88, 88, 8, 10, 0.25, 0),
heavyPistol("Desert Eagle", 35, 35, 7, 50, .5, 0.15), boltSniper("L96A1", 15, 15, 5, 100, 2, 0.02),
semiAuto("M14", 60, 60, 10, 25, .4, 0.05), shotgun("KSG", 30, 30, 6, 20, 1, 0.05), assaultRifle("AK47", 90, 90, 30, 30, .1, .04),
minigun("Minigun", 180, 180, 180, 20, .05, .02),semiSniper("Barrett .50 Cal", 30, 30, 10, 80, .5, .02),
submachine("MP40", 96, 96, 32, 20, .4, .1){}
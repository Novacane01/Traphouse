//
// Created by Kayton Fletcher on 4/11/18.
//
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "ctime"
#include "cstdlib"
#include <random>

#ifndef TRAPHOUSE_ROOM_H
#define TRAPHOUSE_ROOM_H



class linkedMap {

public:

    struct room{
        std::string name;
        bool bIsVisited;
        bool playerInside;
        bool isCleared();
        int neighbors;
        room* neighbor1;
        room* neighbor2;
        room* next;
        room* previous;
        sf::RectangleShape floor;
    };

    room* head;
    room* current;
    room* temp;
    room* temp2;

    int size = 0;

public:

    linkedMap();
    int addRooms(int rooms, int roomsUsed, room* current);
    room getCurrentRoom();
    bool isVisited(Player *player);
    void printMap(room* current, sf::RenderWindow &window);

};



#endif //TRAPHOUSE_ROOM_H

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



class LinkedMap {

private:

    struct room{
        std::string name;
        bool bIsVisited;
        bool playerIsInside;
        bool isCleared();
        int neighbors;
        room* neighbor2;
        room* neighbor3;
        room* neighbor1;
        room* previous;
        sf::RectangleShape floor;
    };

    struct hallway{
        room* entrace;
        room* exit;
        sf::RectangleShape floor;
    };


    room* temp;

    int count = 0;


    bool isRoomUp(room* current);
    bool isRoomDown(room* current);
    bool isRoomRight(room* current);
    bool isRoomLeft(room* current);

    LinkedMap::room* createUpRoom(LinkedMap::room* current);
    LinkedMap::room* createDownRoom(LinkedMap::room* current);
    LinkedMap::room* createRightRoom(LinkedMap::room* current);
    LinkedMap::room* createLeftRoom(LinkedMap::room* current);

public:

    LinkedMap();
    room* head;
    bool doesIntersect(LinkedMap::room* current);
    int checkForNeighbors();
    void addRooms(int rooms, room* current);




    void displayMap(room* current, sf::RenderWindow &window);
    void printRoomNames(room* current);



    LinkedMap::room* getCurrentRoom(Player *player);

};



#endif //TRAPHOUSE_ROOM_H

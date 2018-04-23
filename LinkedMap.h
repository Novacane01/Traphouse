#pragma once
#include "SFML/Graphics.hpp"
#include "ctime"
#include "cstdlib"
#include <random>
#include <iostream>
#include "Player.h"
#include "Chest.h"

class Player;
class LinkedMap {
public:
	struct hallway{
		sf::RectangleShape floor;
	};
	struct room {
		std::string name;
		bool bIsVisited;
		bool playerIsInside;
		bool isCleared = false;
		int neighbors = 0;
		room* neighbor1;
		room* neighbor2;
		room* neighbor3;
		room* previous;
		sf::RectangleShape floor;
		LinkedMap::hallway* hallway;
	};

	const int hallwayWidth = 150;
	LinkedMap(int);
	room* head;

	bool doesIntersect(LinkedMap::room* current);
	void addRooms(int rooms,room* current, sf::RenderWindow &);
	void displayMap(room* current, sf::RenderWindow &window);
	void displayCurrentRoom(sf::RenderWindow &window);
	void printRoomNames(room* current);
    LinkedMap::room* getCurrentRoom();
    LinkedMap::room* getHead();
    LinkedMap::room* getLevelUpRoom();
    void findCurrentRoom(LinkedMap::room*, Player* player);

    //Gets room on map that will contain staircase to level up
    void findStairRoom(room* current);
    //Spawns staircase in level up room
    void placeStairs();
    bool displayStairs(sf::RenderWindow &window, Player* player);
    void placeLevelUpText();
	void findChestRoom(room* current);
	void placeChests();
	void placeChestText();
	bool displayChest1(sf::RenderWindow &window, Player* player);
	bool displayChest2(sf::RenderWindow &window, Player* player);
	LinkedMap::room* getChestRoom1();
	LinkedMap::room* getChestRoom2();
	Chest* getChest1();
	Chest* getChest2();

private:
    //list of all rectangle shapes added to check for intersections as rooms are made
    std::vector<sf::RectangleShape> positions;
    sf::Sprite stairs;

    room* current = nullptr;
    room* levelUpRoom = nullptr;
	room* chestRoom = nullptr;
	room* chestRoom2 = nullptr;

	Chest* chest1;
	Chest* chest2;

	//counts
    int roomsToAdd;
	int count = 0; //helps show rooms added
	int endRoomCount = 0; //number of rooms with no neighbors = number of map branches

	//Text, Textures and Fonts
    sf::Texture stairTexture;
    sf::Texture chestTexture;
    sf::Text levelUpText;
    sf::Text chestText;
    sf::Font font;



	bool createRoom(LinkedMap::room* current, std::string, sf::RenderWindow &);
};




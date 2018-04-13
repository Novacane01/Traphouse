//
// Created by Kayton Fletcher on 4/11/18.
//

#include "linkedMap.h"


linkedMap::linkedMap() {

    head = new room;
    head->playerInside = true;
    head->bIsVisited = true;
    head->floor.setPosition(0,0);
    head->floor.setSize(sf::Vector2f(50,50));
    head->floor.setOrigin(25,25);
    head->floor.setFillColor(sf::Color::Red);
    head->next = nullptr;
    head->neighbor1 = nullptr;
    head->neighbor2 = nullptr;
    head->previous = nullptr;
    head->name = "HEAD";

    current = head;
}

int count = 2;

int linkedMap::addRooms(int rooms, int roomsUsed, room* current){
    std::cout << roomsUsed << " ";
    std::cout << rooms << " " << std::endl;

    if(rooms == 0 || rooms == 1){
        return roomsUsed;
    }




    int neighbors = rand() % 3 + 1;

    if(neighbors > rooms){
        neighbors = rooms;
    }

    current->neighbors = neighbors;

    if(neighbors == 3){
        rooms --;
        roomsUsed ++;

        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);



        temp->name = "room " + std::to_string(count++);

        current->next = temp;

        int roomsAdded = rand() % rooms;

        roomsUsed = addRooms(roomsAdded, roomsUsed, current->next);

        rooms -= roomsAdded;

        if(rooms == 0 ){
            return roomsUsed;
        }

        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);

        temp->name = "room " + std::to_string(count++);

        current->neighbor1 = temp;

        roomsAdded = rand() % rooms;

        roomsUsed = addRooms(roomsAdded, roomsUsed, current->neighbor1);

        rooms -= roomsAdded;

        if(rooms == 0 ){
            return roomsUsed;

        }

        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);

        temp->name = "room " + std::to_string(count++);


        current->neighbor2 = temp;



        roomsUsed = addRooms(rooms, roomsUsed, current->neighbor2);
        rooms = 0;

        if(rooms == 0 ){
            return roomsUsed;

        }
    }
    if(neighbors == 2){
        rooms --;
        roomsUsed ++;

        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);


        temp->name = "room " + std::to_string(count++);

        current->next = temp;

        int roomsAdded = rand() % rooms;

        roomsUsed = addRooms(roomsAdded, roomsUsed, current->next);

        rooms -= roomsAdded;

        rooms --;
        roomsUsed ++;

        if(rooms == 0 ){
            return roomsUsed;

        }


        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);

        temp->name = "room " + std::to_string(count++);

        current->neighbor1 = temp;

        roomsUsed = addRooms(rooms, roomsUsed, current->neighbor1);

        rooms = 0;

        if(rooms == 0 ){
            return roomsUsed;

        }

    }

    if(neighbors == 1){
        rooms --;
        roomsUsed++;

        temp = new room;
        //sets 3 branches to null and previous branch to current
        temp->next = nullptr;
        temp->neighbor1 = nullptr;
        temp->neighbor2 = nullptr;
        temp->previous = current;

        //Gives information about size, color and placement of room
        temp->playerInside = false;
        temp->bIsVisited = false;
        temp->floor.setSize(sf::Vector2f(50,50));
        temp->floor.setFillColor(sf::Color::Green);
        temp->floor.setPosition(current->floor.getOrigin().x + 50 + temp->floor.getOrigin().x, current->floor.getOrigin().y + 50 + temp->floor.getOrigin().y);

        temp->name = "room " + std::to_string(count++);

        current->next = temp;

        if(rooms == 0 ){
            return roomsUsed;

        } else{
            roomsUsed = addRooms(rooms, roomsUsed, current->next);
            rooms = 0;
        }

    }

    return roomsUsed;

}

void linkedMap::printMap(room* current, sf::RenderWindow &window){

    if(current->neighbor1!= nullptr){
        window.draw(current->neighbor1->floor);


        if(current->neighbor1->neighbors>0){
            printMap(current->neighbor1, window);
        }
    }
    if(current->neighbor2!= nullptr){
        window.draw(current->neighbor2->floor);
        if(current->neighbor2->neighbors>0){
            printMap(current->neighbor2, window);
        }
    }
    if(current->next!= nullptr){
        window.draw(current->next->floor);
        if(current->next->neighbors>0){
            printMap(current->next, window);
        }
    }


}

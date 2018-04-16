//
// Created by Kayton Fletcher on 4/11/18.
//

#include "LinkedMap.h"


LinkedMap::LinkedMap() {

    srand(time(0));

    head = new room;
    head->playerIsInside = true;
    head->bIsVisited = true;

    count++;
    head->floor.setSize(sf::Vector2f(500,500));

    head->floor.setOrigin(head->floor.getSize().x / 2, head->floor.getSize().y / 2);
    head->floor.setPosition(0,0);

    head->floor.setFillColor(sf::Color::Red);
    head->neighbor1 = nullptr;
    head->neighbor2 = nullptr;
    head->neighbor3 = nullptr;
    head->previous = nullptr;
    head->name = "HEAD";

}

bool LinkedMap::doesIntersect(LinkedMap::room* current){

    bool intersects = false;

    float bottomBound = temp->floor.getPosition().y + (temp->floor.getSize().y)/2;
    float upperBound = temp->floor.getPosition().y - (temp->floor.getSize().y)/2;
    float rightBound = temp->floor.getPosition().x + (temp->floor.getSize().x)/2;
    float leftBound = temp->floor.getPosition().x - (temp->floor.getSize().x)/2;

    float currentBottomBound = current->floor.getPosition().y + (current->floor.getSize().y)/2;
    float currentUpperBound = current->floor.getPosition().y - (current->floor.getSize().y)/2;
    float currentRightBound = current->floor.getPosition().x + (current->floor.getSize().x)/2;
    float currentLeftBound = current->floor.getPosition().x - (current->floor.getSize().x)/2;

    //for inside upper bounds
    if((upperBound > currentUpperBound && upperBound < currentBottomBound) &&
            //Checks if right bounds are inside                                     //Checks if left bounds are inside
            ((rightBound < currentRightBound && rightBound > currentLeftBound) || (leftBound > currentLeftBound && leftBound < currentRightBound)))
    {
        intersects = true;
    }

    //for inside lower bounds
    if((bottomBound > currentUpperBound && bottomBound < currentBottomBound) &&
       //Checks if right bounds are inside                                     //Checks if left bounds are inside
       ((rightBound < currentRightBound && rightBound > currentLeftBound) || (leftBound > currentLeftBound && leftBound < currentRightBound)))
    {
        intersects = true;
    }

    return intersects;
}

bool LinkedMap::isRoomUp(LinkedMap::room* current){
    bool bIsRoomUp = false;

    if(current->neighbor2!= nullptr){

        if(doesIntersect(current))
        {
           bIsRoomUp = true;
            return bIsRoomUp;
        }

        if(current->neighbor2->neighbors>0){
            return isRoomUp(current->neighbor2);

        }
    }
    if(current->neighbor3!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomUp = true;
            return bIsRoomUp;
        }

        if(current->neighbor3->neighbors>0){
            return isRoomUp(current->neighbor3);
        }
    }
    if(current->neighbor1!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomUp = true;
            return bIsRoomUp;
        }

        if(current->neighbor1->neighbors>0){
            return isRoomUp(current->neighbor1);
        }
    }
    return bIsRoomUp;
}

bool LinkedMap::isRoomDown(LinkedMap::room* current){
    bool bIsRoomDown = false;
    if(current->neighbor2!= nullptr){

        if(doesIntersect(current))
        {
            bIsRoomDown = true;
            return bIsRoomDown;
        }

        if(current->neighbor2->neighbors>0){

            return isRoomDown(current->neighbor2);
        }
    }
    if(current->neighbor3!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomDown = true;
            return bIsRoomDown;
        }

        if(current->neighbor3->neighbors>0){

            return isRoomDown(current->neighbor3);
        }
    }
    if(current->neighbor1!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomDown = true;
            return bIsRoomDown;
        }

        if(current->neighbor1->neighbors>0){
            return isRoomDown(current->neighbor1);
        }
    }

    return bIsRoomDown;

}

bool LinkedMap::isRoomRight(LinkedMap::room* current){
    bool bIsRoomRight = false;

    if(current->neighbor2!= nullptr){

        if(doesIntersect(current))
        {
            bIsRoomRight = true;
            return bIsRoomRight;
        }

        if(current->neighbor2->neighbors>0){

            return isRoomRight(current->neighbor2);

        }
    }
    if(current->neighbor3!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomRight = true;
            return bIsRoomRight;
        }

        if(current->neighbor3->neighbors>0){
            return isRoomRight(current->neighbor3);
        }
    }
    if(current->neighbor1!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomRight = true;
            return bIsRoomRight;
        }

        if(current->neighbor1->neighbors>0){
            return isRoomRight(current->neighbor1);
        }
    }

    return bIsRoomRight;


}

bool LinkedMap::isRoomLeft(LinkedMap::room* current){

    bool bIsRoomLeft = false;

    if(current->neighbor2!= nullptr){

        if(doesIntersect(current))
        {
            bIsRoomLeft = true;
        }

        if(current->neighbor2->neighbors>0){

            return isRoomLeft(current->neighbor2);

        }
    }
    if(current->neighbor3!= nullptr){
        if(doesIntersect(current))
        {
            bIsRoomLeft = true;
        }

        if(current->neighbor3->neighbors>0){
            return isRoomLeft(current->neighbor3);
        }
    }
    if(current->neighbor1!= nullptr){
        if(doesIntersect(current))
        {
            return bIsRoomLeft = true;
        }

        if(current->neighbor1->neighbors>0){
            return isRoomLeft(current->neighbor1);
        }
    }

    return bIsRoomLeft;
}

int LinkedMap::checkForNeighbors(){
    int neighbors;
    return neighbors;
}

LinkedMap::room* LinkedMap::createUpRoom(LinkedMap::room* current){

    LinkedMap::room* temp = new room;
    //sets 3 branches to null and previous branch to current
    temp->neighbor1 = nullptr;
    temp->neighbor2 = nullptr;
    temp->neighbor3 = nullptr;
    temp->previous = current;

    //Gives information about size, color and placement of room
    temp->playerIsInside = false;
    temp->bIsVisited = false;
    temp->floor.setSize(sf::Vector2f(150,150));
    temp->floor.setFillColor(sf::Color::White);
    temp->floor.setOrigin(temp->floor.getSize().x /2 , temp->floor.getSize().y / 2);
    temp->floor.setPosition(current->floor.getPosition().x,-(current->floor.getPosition().y + 600));

    temp->name = "room " + std::to_string(count);

    return temp;
}

LinkedMap::room* LinkedMap::createDownRoom(LinkedMap::room* current){

    LinkedMap::room* temp = new room;
    //sets 3 branches to null and previous branch to current
    temp->neighbor1 = nullptr;
    temp->neighbor2 = nullptr;
    temp->neighbor3 = nullptr;
    temp->previous = current;

    //Gives information about size, color and placement of room
    temp->playerIsInside = false;
    temp->bIsVisited = false;
    temp->floor.setSize(sf::Vector2f(225,225));
    temp->floor.setFillColor(sf::Color::Green);
    temp->floor.setOrigin(temp->floor.getSize().x /2 , temp->floor.getSize().y / 2);
    temp->floor.setPosition(current->floor.getPosition().x,current->floor.getPosition().y + 600);

    temp->name = "room " + std::to_string(count);

 return temp;   
}

LinkedMap::room* LinkedMap::createRightRoom(LinkedMap::room* current){

    LinkedMap::room* temp = new room;
    //sets 3 branches to null and previous branch to current
    temp->neighbor1 = nullptr;
    temp->neighbor2 = nullptr;
    temp->neighbor3 = nullptr;
    temp->previous = current;

    //Gives information about size, color and placement of room
    temp->playerIsInside = false;
    temp->bIsVisited = false;
    temp->floor.setSize(sf::Vector2f(200,200));
    temp->floor.setFillColor(sf::Color::Blue);
    temp->floor.setOrigin(temp->floor.getSize().x /2 , temp->floor.getSize().y / 2);
    temp->floor.setPosition((current->floor.getPosition().x + 600),current->floor.getPosition().y);
    temp->name = "room " + std::to_string(count);


    return temp;
}

LinkedMap::room* LinkedMap::createLeftRoom(LinkedMap::room* current){

    LinkedMap::room* temp = new room;
    //sets 3 branches to null and previous branch to current
    temp->neighbor1 = nullptr;
    temp->neighbor2 = nullptr;
    temp->neighbor3 = nullptr;
    temp->previous = current;

    //Gives information about size, color and placement of room
    temp->playerIsInside = false;
    temp->bIsVisited = false;
    temp->floor.setSize(sf::Vector2f(176,176));
    temp->floor.setFillColor(sf::Color::Magenta);
    temp->floor.setOrigin(temp->floor.getSize().x /2 , temp->floor.getSize().y / 2);
    temp->floor.setPosition(-(current->floor.getPosition().x + 600), current->floor.getPosition().y);

    temp->name = "room " + std::to_string(count);


    return temp;
}

void LinkedMap::addRooms(int rooms, room* current){


    if(rooms == 0 || rooms == 1 ){
        return;
    }
    bool bIsRoomUp = false;
    bool bIsRoomDown = false;
    bool bIsRoomLeft = false;
    bool bIsRoomRight = false;


    int neighbors = rand() % 3 + 1;

    int tempNeighbors = 4;

    temp = createDownRoom(current);

    bIsRoomDown = isRoomDown(head);

    if(bIsRoomDown){
        tempNeighbors--;
    }

    temp = createRightRoom(current);

    bIsRoomRight = isRoomRight(head);

    if(bIsRoomRight){
        tempNeighbors--;
    }

    temp = createLeftRoom(current);

    bIsRoomLeft = isRoomLeft(head);

    if(bIsRoomLeft){
        tempNeighbors--;
    }
    temp = createUpRoom(current);

    bIsRoomUp = isRoomUp(head);

    if(bIsRoomUp){
        tempNeighbors--;
    }

    if(neighbors > rooms){
        neighbors = rooms;
    }

    if(tempNeighbors < neighbors){
        neighbors = tempNeighbors;
    }

    current->neighbors = neighbors;

    if(neighbors == 3){

        rooms -= 3;
        int roomsAdded;

        //neighbor1 room
        if(!bIsRoomUp){

            count++;
            current->neighbor1 = createUpRoom(current);

            if(rooms > 0) {
                roomsAdded = rand() % rooms;
                addRooms(roomsAdded, current->neighbor1);
                rooms -= roomsAdded;
            }

            //neighbor2 room
            if(!bIsRoomDown) {

                count++;
                current->neighbor2 = createDownRoom(current);

                if(rooms > 0) {
                    roomsAdded = rand() % rooms;
                    addRooms(roomsAdded, current->neighbor2);
                    rooms -= roomsAdded;
                }

                //neighbor3 room
                if(!bIsRoomRight){

                    count++;
                    current->neighbor3 = createRightRoom(current);
                    addRooms(rooms, current->neighbor3);

                    rooms = 0;

                    return;


                    //neighbor 3 room
                } else if(!bIsRoomLeft){

                    count++;
                    current->neighbor3 = createLeftRoom(current);

                    addRooms(rooms, current->neighbor3);

                    rooms = 0;

                    return;

                }

            //neighbor2 room
            } else if(!bIsRoomRight) {

                count++;
                current->neighbor2 = createRightRoom(current);

                if(rooms > 0) {
                    roomsAdded = rand() % rooms;
                    addRooms(roomsAdded, current->neighbor2);
                    rooms -= roomsAdded;
                }

                if(!bIsRoomLeft) {

                    count++;
                    current->neighbor3 = createLeftRoom(current);

                    if(rooms == 0){
                        return;
                    }

                    addRooms(rooms, current->neighbor3);

                    rooms = 0;

                    return;
                }

                //neighbor2 room
            } else if(!bIsRoomLeft) {
                std::cout<< "THIS SHOULDNT HAPPEN";

            }

        //neighbor1 room
        } else if(!bIsRoomDown){

            count++;
            current->neighbor1 = createDownRoom(current);

            if(rooms > 0) {
                roomsAdded = rand() % rooms;
                addRooms(roomsAdded, current->neighbor1);
                rooms -= roomsAdded;
            }
            //neighbor2 room
            if(!bIsRoomRight) {

                count++;
                current->neighbor2 = createRightRoom(current);

                if(rooms > 0) {
                    roomsAdded = rand() % rooms;
                    addRooms(roomsAdded, current->neighbor2);
                    rooms -= roomsAdded;
                }

                //neighbor3 room
                if(!bIsRoomLeft) {

                    count++;
                    current->neighbor3 = createLeftRoom(current);

                    addRooms(rooms, current->neighbor3);
                    rooms = 0;

                    return;
                }

            //neighbor2 room
            } else if(!bIsRoomLeft) {
                std::cout<< "THIS SHOULDNT HAPPEN";
            }
        //neighbor1 room
        } else if(!bIsRoomRight){
            std::cout<< "THIS SHOULDNT HAPPEN";
        //neighbor1 Room
        } else if(!bIsRoomLeft){
            std::cout<< "THIS SHOULDNT HAPPEN";
        }

        return;
    }

    if(neighbors == 2) {

        rooms -= 2;
        int roomsAdded;
        //neighbor1 room
        if (!bIsRoomLeft) {

            count++;
            current->neighbor1 = createLeftRoom(current);

            if(rooms > 0) {
                roomsAdded = rand() % rooms;
                addRooms(roomsAdded, current->neighbor1);
                rooms -= roomsAdded;
            }

            //neighbor2 room
            if (!bIsRoomDown) {
                count++;

                current->neighbor2 = createDownRoom(current);

                addRooms(rooms, current->neighbor2);
                rooms = 0;
                return;

                //neighbor2 room
            } else if (!bIsRoomUp) {
                count++;
                current->neighbor2 = createUpRoom(current);

                addRooms(rooms, current->neighbor2);
                rooms = 0;
                return;

                //neighbor2 room
            } else if (!bIsRoomRight) {

                count++;
                current->neighbor2 = createRightRoom(current);
                addRooms(rooms, current->neighbor2);

                rooms = 0;
                return;
            }

            //neighbor1 room
        } else if (!bIsRoomDown) {
            count++;
            current->neighbor1 = createDownRoom(current);

            if(rooms > 0) {
                int roomsAdded = rand() % rooms;
                addRooms(roomsAdded, current->neighbor1);
                rooms -= roomsAdded;
            }

            //neighbor2 room
            if (!bIsRoomUp) {
                count++;

                current->neighbor2 = createUpRoom(current);

                addRooms(rooms, current->neighbor2);

                rooms = 0;
                return;

                //neighbor2 room
            } else if (!bIsRoomRight) {
                count++;
                current->neighbor2 = createRightRoom(current);

                addRooms(rooms, current->neighbor2);
                rooms = 0;

                return;
            }

            //neighbor1 room
        } else if (!bIsRoomUp) {
            count++;
            current->neighbor1 = createUpRoom(current);

            if(rooms > 0) {
                int roomsAdded = rand() % rooms;
                addRooms(roomsAdded, current->neighbor1);
                rooms -= roomsAdded;
            }

            //neighbor2 room
            if (!bIsRoomRight) {
                count++;
                current->neighbor2 = createRightRoom(current);

                addRooms(rooms, current->neighbor2);

                rooms = 0;
                return;
            }

        } else if (!bIsRoomRight) {
            std::cout << "THIS SHOULDNT HAPPEN";
        }
    }

    if(neighbors == 1){
        count++;
        rooms--;

        if(!bIsRoomRight){

            current->neighbor1 = createRightRoom(current);

        } else if(!bIsRoomUp){

            current->neighbor1 = createUpRoom(current);


        } else if(!bIsRoomDown){

            current->neighbor1 = createDownRoom(current);


        } else if(!bIsRoomLeft){

            current->neighbor1 = createLeftRoom(current);

        }

        addRooms(rooms, current->neighbor1);

        rooms = 0;
        return;

    }
}

LinkedMap::room* LinkedMap::getCurrentRoom(Player* player) {


}

void LinkedMap::displayMap(room* current, sf::RenderWindow &window){

    if(current->neighbor2!= nullptr){

        window.draw(current->neighbor2->floor);

        if(current->neighbor2->neighbors>0){
            displayMap(current->neighbor2, window);
        }
    }
    if(current->neighbor3!= nullptr){

        window.draw(current->neighbor3->floor);

        if(current->neighbor3->neighbors>0){
            displayMap(current->neighbor3, window);
        }
    }
    if(current->neighbor1!= nullptr){
        window.draw(current->neighbor1->floor);

        if(current->neighbor1->neighbors>0){
            displayMap(current->neighbor1, window);
        }
    }
}

void LinkedMap::printRoomNames(room* current){

    if(current->neighbor2!= nullptr){
        std::cout << current->neighbor2->name << std::endl;

        if(current->neighbor2->neighbors>0){
            printRoomNames(current->neighbor2);
        }
    }

    if(current->neighbor3!= nullptr){
        std::cout << current->neighbor3->name << std::endl;
        if(current->neighbor3->neighbors>0){
            printRoomNames(current->neighbor3);
        }
    }

    if(current->neighbor1!= nullptr){

        std::cout << current->neighbor1->name << std::endl;

        if(current->neighbor1->neighbors>0){
            printRoomNames(current->neighbor1);
        }
    }

}
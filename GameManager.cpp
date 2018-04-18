//#include "stdafx.h"
#include "GameManager.h"
#include "Chest.h"
#include <unistd.h>
unsigned WINDOW_LENGTH, WINDOW_WIDTH;
//Game Manager Constructor
GameManager::GameManager(int width, int length) {
	setWindowLength(length);
	setWindowWidth(width);
	if (!font.loadFromFile("Fonts/light_pixel-7.ttf")) {
		std::cout << "Could not load file" << std::endl;
	}
}

//Sets window length
void GameManager::setWindowLength(int value) {
	WINDOW_LENGTH = value;
}

//Sets window width
void GameManager::setWindowWidth(int value) {
	WINDOW_WIDTH = value;
}

//Starts The Game
void GameManager::Start() {

	
	//Creates Window with size WINDOW_WITDTH x WINDOW_LENGTH
	static sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH), "Traphouse");


    //creates randomized map
    LinkedMap lmap(17);
	lmap.addRooms(17,lmap.head, window);
	lmap.printRoomNames(lmap.head);

	window.setKeyRepeatEnabled(false); //Disables repeated keypresses
	window.setVerticalSyncEnabled(false); //Limits refresh rate to monitor

    //Initializes clock to record frames per second
	sf::Clock FPSclock;
	sf::Clock clickInterval;


	//Creates player object
	Player* player = createPlayer(window);

    //sets center of window at 0,0
    sf::View roomView;
    roomView.setCenter(0,0);
    window.setView(roomView);

	//Creates bounded Map rectangle object
	Floor *map = new Floor;

	//Spawning monsters
	//Enemy::Spawn(new Skeleton());
	//Enemy::Spawn(new Spider());



    //Main loop
	while (window.isOpen()) {
		float deltaTime = FPSclock.restart().asSeconds();
		//Records window events such as mouse movement, mouse clicks, and key strokes
		sf::Event event;
		while (window.pollEvent(event)) {
			if (clickInterval.getElapsedTime().asSeconds() > ((player->triggerhappy)?player->getCurrentWeapon().getAttackSpeed()/2.f:player->getCurrentWeapon().getAttackSpeed())) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					player->getCurrentWeapon().Shoot(player, window);
					clickInterval.restart();
				}
			}
			if (event.type == event.Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					player->isMovingUp = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					player->isMovingLeft = true;
				
				}
				if (event.key.code == sf::Keyboard::S) {
					player->isMovingDown = true;
					
				}
				if (event.key.code == sf::Keyboard::D) {
					player->isMovingRight = true;
					
				}
				if (event.key.code == sf::Keyboard::R&&player->getCurrentWeapon().getCurrentClip()<player->getCurrentWeapon().getMaxClip()) {
					player->getCurrentWeapon().bIsReloading = true;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					player->bIsSprinting = true;
				}
				if (event.key.code == sf::Keyboard::Escape) {
					Pause(window);
				}
                if(event.key.code == sf::Keyboard::M){
				    DisplayMap(window, player, &lmap);
                }
				if (event.key.code == sf::Keyboard::X) {
					if (player->getPotions().size() > 0) {
						player->getCurrentPotion()->Use(player);
						std::cout << player->getCurrentPotion()->getName() << " used" << std::endl;
						player->getPotions().erase(player->getPotions().begin());
					}
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					player->isMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					player->isMovingLeft = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					player->isMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					player->isMovingRight = false;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					player->bIsSprinting = false;
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				player->switchWeapons();
			}
		}

		window.clear(); //Clears window
		map->Draw(window); //Draws map

		//Draws Enemmies to screen
		for (unsigned i = 0; i < Enemy::getEnemies().size();i++) {
			Enemy::getEnemies()[i]->Update(player, deltaTime);
			Enemy::getEnemies()[i]->Draw(window);
			if (Enemy::getEnemies()[i]->isDead()) {
				Enemy::Destroy(Enemy::getEnemies().begin()+i);
			}
		}
		player->Update(window, deltaTime); //Updates player position
		player->Draw(window); //Draws player to screen
		for (unsigned i = 0;i < player->getWeapons().size();i++) {
			player->getWeapons()[i].Update(window, player, deltaTime); //Updates weapons and bullets
		}
		player->getCurrentWeapon().displayWeaponInfo(window);
		lmap.displayMap(lmap.head, window);
		window.display(); //Displays all drawn objects
		if (player->isDead()) {
			GameOver();
		}
	}
}




Player* GameManager::createPlayer(sf::RenderWindow &window) {
	window.setKeyRepeatEnabled(true);
	bool created = false;

	//Creates textbox
	sf::RectangleShape textBox(sf::Vector2f(250, 50));
	textBox.setPosition(WINDOW_WIDTH / 2.f - textBox.getSize().x/2.f, WINDOW_LENGTH / 2.f - textBox.getSize().y/2.f);
	textBox.setFillColor(sf::Color::Transparent);
	textBox.setOutlineColor(sf::Color::Red);
	textBox.setOutlineThickness(2);

	sf::Text text; //Creates text object for name to be drawn to screen
	text.setFont(font);
	text.setPosition(textBox.getPosition().x + textBox.getSize().x / 2.f, textBox.getPosition().y + textBox.getSize().y / 5.f);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::White);

	sf::Text namePrompt; //Creates text object for user prompt
	namePrompt.setFont(font);
	namePrompt.setString("Enter your name:");
	namePrompt.setPosition(WINDOW_WIDTH/2-namePrompt.getCharacterSize()*5.4f, textBox.getPosition().y - (textBox.getSize().y*1.5f));
	namePrompt.setFillColor(sf::Color::White);

	std::string name; //Player name

	
	//Draw Loop
	while (window.isOpen()&&!created) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace&&name.size()>0) {
					name = name.substr(0, name.size() - 1);
					text.setString(name);
					text.setPosition(text.getPosition().x + (textBox.getSize().x / (text.getCharacterSize()*1.15f)), text.getPosition().y);
				}
				if (name.size() > 0 && event.key.code == sf::Keyboard::Return) {
					created = true;
					break;
				}
			}
			if (event.type == sf::Event::TextEntered&&(char)event.text.unicode!='\b'&&name.size()<10) {
				name += (char)event.text.unicode;
				text.setString(name);
				text.setPosition(text.getPosition().x - (textBox.getSize().x/ (text.getCharacterSize()*1.15f)), text.getPosition().y);
			}
		}
		window.clear();
		window.draw(text);
		window.draw(namePrompt);
		window.draw(textBox);
		window.display();
	}

	window.setKeyRepeatEnabled(false);

	//Creating player
	Player *player = new Player(name);
	return player;
}

//Game Manager Destructor
GameManager::~GameManager() {

}

void GameManager::GameOver() {
	std::cout << "You have died" << std::endl;
	Enemy::getEnemies().clear();
	Start();
}

void GameManager::Pause(sf::RenderWindow &window) {
	sf::Event event;
	sf::Text resumeButton;
	resumeButton.setFont(font);
	resumeButton.setCharacterSize(48);
	resumeButton.setString("Resume");
	resumeButton.setOrigin(resumeButton.getGlobalBounds().width/2, resumeButton.getGlobalBounds().height/2);
	resumeButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y - 200);

    //Adds quit button to menu screen
    sf::Text exitButton;
    exitButton.setFont(font);
    exitButton.setCharacterSize(48);
    exitButton.setString("Quit");
    exitButton.setOrigin(exitButton.getGlobalBounds().width/2, exitButton.getGlobalBounds().height/2);
    exitButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y);

	while (window.isOpen()) {
		//Activates buttons if pressed, respectively
	    if(resumeButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
	        resumeButton.setCharacterSize(58);//enlarges text when mouse is hovering over
            resumeButton.setOrigin(resumeButton.getGlobalBounds().width/2, resumeButton.getGlobalBounds().height/2);
            resumeButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y - 200);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
	    		return;
            }
        } else{
	        resumeButton.setCharacterSize(48);
            resumeButton.setOrigin(resumeButton.getGlobalBounds().width/2, resumeButton.getGlobalBounds().height/2);
	        resumeButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y - 200);
	    }
	    if(exitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            exitButton.setCharacterSize(58); //enlarges text when mouse is hovering over
            exitButton.setOrigin(exitButton.getGlobalBounds().width/2, exitButton.getGlobalBounds().height/2);
            exitButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                window.close();
            }
        } else {
            exitButton.setCharacterSize(48);
            exitButton.setOrigin(exitButton.getGlobalBounds().width/2, exitButton.getGlobalBounds().height/2);
            exitButton.setPosition(window.getView().getCenter().x,window.getView().getCenter().y);
        }
        while (window.pollEvent(event)) {
			if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Escape){
					usleep(10000);
					return;
				}
			}
	    	if (event.type == event.Closed) {
				usleep(10000);
                window.close();
            }
		}
		window.clear();
		window.draw(resumeButton);
		window.draw(exitButton);
        window.display();
	}
}

void GameManager::DisplayMap(sf::RenderWindow &window, Player* player, LinkedMap* linkedMap){
    sf::Event event;
    sf::View mapView;
    sf::View roomView;
    bool windowMoving = false;
    sf::Vector2f oldMousePos;
    sf::Vector2f newMousePos;
    sf::Vector2f diffPosition;


    roomView = window.getView();
	//Shows large portion of map
	mapView.setSize(10000,10000);
    //Centers view of map around player
    mapView.setCenter(player->getPlayer().getPosition().x,player->getPlayer().getPosition().y);
    window.setView(mapView);

    while(window.isOpen())
    {

    	while (window.pollEvent(event)) {

        	/*
        	 * Methods For changing window location by clicking and dragging mouse
        	 */
    	    if(event.type == sf::Event::MouseButtonPressed){
				if(event.mouseButton.button == 0){
					oldMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					windowMoving = true;
				}
			} else if(event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == 0){
					windowMoving = false;
				}

			} else if(event.type == sf::Event::MouseMoved){
				if(windowMoving){
					newMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					diffPosition = oldMousePos - newMousePos;
					mapView.setCenter(mapView.getCenter() + diffPosition);
					window.setView(mapView);

					//Sets old position = new position, based on new window, for the next time the mouse is moved
					oldMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				}
			}

			if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::M){
                    window.setView(roomView);
                    return;
                }
            }
            if (event.type == event.Closed) {
                window.close();
            }
        }
        window.clear();
        linkedMap->displayMap(linkedMap->head,window);
        player->Draw(window);
        window.display();

    }

}
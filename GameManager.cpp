
#include "GameManager.h"
#include "Chest.h"

unsigned WINDOW_LENGTH, WINDOW_WIDTH;
//Game Manager Constructor
GameManager::GameManager(int width, int length) {
	setWindowLength(length);
	setWindowWidth(width);
	if (!font.loadFromFile("Fonts/light_pixel-7.ttf")) {
		std::cout << "Could not load file" << std::endl;
	}
	Weapon();
	level = 1;

	//Creates Window with size WINDOW_WITDTH x WINDOW_LENGTH
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH), "TrapHouse");

	//Starts loading screen
	LoadingScreen();
	//sets size and shape of health, stamina and name for player
	if (player != nullptr) {
		player->setUI();
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
bool GameManager::Start() {
	if (player != nullptr) {
		int numOfRooms = rand() % 5 + 8;
		//Creates randomized map
		LinkedMap* lmap = new LinkedMap(numOfRooms, level);
		lmap->addRooms(numOfRooms, lmap->getHead(), window);
		lmap->findStairRoom(lmap->getHead()); //sets an end room to level up room
		lmap->placeStairs();
		lmap->placeLevelUpText();
		lmap->findChestRoom(lmap->getHead());
		lmap->placeChests();
		lmap->placeChestText();

		window.setFramerateLimit(120);
		window.setKeyRepeatEnabled(false); //Disables repeated keypresses
		window.setVerticalSyncEnabled(false); //Limits refresh rate to monitor

		sf::Text levelText;
		levelText.setString("Level " + std::to_string(level));
		levelText.setCharacterSize(25);
		levelText.setFont(font);
		levelText.setOrigin(levelText.getGlobalBounds().width / 2, levelText.getGlobalBounds().height / 2);

		//Initializes clock to record frames per second
		sf::Clock FPSclock;
		sf::Clock clickInterval;

		sf::Music music;
		if (!music.openFromFile("Music/GameBGM.wav")) {
			std::cout << "Could not open sound file" << std::endl;
		}
		music.play();
		music.setVolume(50);
		music.setLoop(true);
		//Sets center of window at (0,0)

		roomView.setCenter(910, 540);
		window.setView(roomView);

		//Creates bounded Map rectangle object
		bool centered = false;

		lmap->findCurrentRoom(lmap->head, player);

		//sets text in top left for current level
		levelText.setString("Level " + std::to_string(level));

		//Main loop
		while (window.isOpen()) {

			float deltaTime = FPSclock.restart().asSeconds();
			//Records window events such as mouse movement, mouse clicks, and key strokes
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
					return false;
				}
				if (event.mouseButton.button == sf::Mouse::Left&&event.type == sf::Event::MouseButtonPressed) {
					player->bCanShoot = true;
				}
				if (event.mouseButton.button == sf::Mouse::Left&&event.type == sf::Event::MouseButtonReleased) {
					player->bCanShoot = false;
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
					if (event.key.code == sf::Keyboard::M) {
						inFunction = true;
						DisplayMap(player, lmap);
						while (window.pollEvent(event)) {

						}
					}
					if (event.key.code == sf::Keyboard::R &&
						player->getCurrentWeapon().getCurrentClip() < player->getCurrentWeapon().getMaxClip()) {
						player->getCurrentWeapon().bIsReloading = true;
						player->getCurrentWeapon().playAudioFire();
					}
					if (event.key.code == sf::Keyboard::LShift) {
						player->bIsSprinting = true;
					}
					if (event.key.code == sf::Keyboard::Escape) {
						inFunction = true;
						paused = true;
						music.pause();
						Pause();
						music.play();
						while (window.pollEvent(event)) {

						}
					}
                    if (event.key.code == sf::Keyboard::X) {
                        if (player->getPotions().size() > 0) {
                            player->getCurrentPotion()->Use(player);
                            std::cout << player->getCurrentPotion()->getName() << " used" << std::endl;
                            for (int i = 0; i < player->getPotions().size(); i++) {
                                if (player->getCurrentPotion() == player->getPotions()[i]) {
                                    player->getPotions().erase(player->getPotions().begin() + i);
                                    if (i == 0) {
                                        player->setCurrentPotion(player->getPotions()[0]);
                                    } else {
                                        player->setCurrentPotion(player->getPotions()[i - 1]);
                                    }
                                }
                            }
                        } else {
                            player->setCurrentPotion(nullptr);
                        }
                    }
                    if (event.key.code == sf::Keyboard::Q) {
                        if (player->getPotions().size() > 1) {
                            for (int i = 0; i < player->getPotions().size(); i++) {
                                if (player->getCurrentPotion() == player->getPotions()[i]) {
                                    if (i > 0) {
                                        player->setCurrentPotion(player->getPotions()[i - 1]);
                                    }
                                }
                            }
                        }
                    }
                    if (event.key.code == sf::Keyboard::E) {
                        if (player->getPotions().size() > 1) {
                            for (int i = 0; i < player->getPotions().size() - 1; i++) {
                                if (player->getCurrentPotion() == player->getPotions()[i]) {
                                    if (player->getPotions()[i + 1] != nullptr) {
                                        player->setCurrentPotion(player->getPotions()[i + 1]);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (event.key.code == sf::Keyboard::F) {
						if (lmap->displayStairs(window, player)) {
							if(!isDemonSpawned){
								isDemonSpawned = true;
								if(lmap->getCurrentRoom() == lmap->getLevelUpRoom()){
									Enemy::Spawn(new Demon("Demon", 500 + ((level - 1) * 10), 2 + (level - 1)), lmap->getCurrentRoom());
								}
							}
							if(Enemy::getEnemies().size() == 0){

								music.stop();
								levelUp(lmap);
								return false;
							}
						}
						if (lmap->displayChest1(window, player, chestIsLookedAt)) {


							lmap->getChest1()->Open(player);
							chestIsLookedAt = true;

							displayChestTime.restart();
						} else{
							chestIsLookedAt = false;
						}
						if (lmap->displayChest2(window, player, chestIsLookedAt)) {
							lmap->getChest2()->Open(player);
							chestIsLookedAt2 = true;
							displayChestTime.restart();
						}else{
							chestIsLookedAt2 = false;
						}
					} if(event.key.code == sf::Keyboard::Y && chestIsLookedAt && !lmap->getChest1()->getIsOpen()){
						lmap->getChest1()->takeGun(player);
						chestIsLookedAt = false;
						displayChestTime.restart();

					}if(event.key.code == sf::Keyboard::N && chestIsLookedAt && !lmap->getChest1()->getIsOpen()){
						lmap->getChest1()->leaveGun(player);
					}if(event.key.code == sf::Keyboard::Y && chestIsLookedAt2 && !lmap->getChest2()->getIsOpen()) {
						lmap->getChest2()->takeGun(player);
						chestIsLookedAt2 = false;
						displayChestTime.restart();
					} if(event.key.code == sf::Keyboard::N && chestIsLookedAt2 && !lmap->getChest2()->getIsOpen()){
						lmap->getChest2()->leaveGun(player);
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
			if (lmap->chest1->sound.getStatus() == sf::Sound::Playing||lmap->chest2->sound.getStatus() == sf::Sound::Playing) {
				music.pause();
			}
			else if(music.getStatus() == sf::Music::Paused) {
				music.play();
				music.setVolume(50);
			}
			//If not in current room (Between rooms/In hallways)
			if (!lmap->getCurrentRoom()->playerIsInside) {
				lmap->findCurrentRoom(lmap->head, player);
				roomView.setCenter(player->getPlayer().getPosition());
				window.setView(roomView);
				centered = false;

				//if room is not cleared and map is not already centered, centers map and spawns enemies, only called once per room
			}
			else if (!centered && !lmap->getCurrentRoom()->isCleared && lmap->getCurrentRoom() != lmap->getChestRoom1() && lmap->getCurrentRoom() != lmap->getChestRoom2() && lmap->getCurrentRoom() != lmap->getHead() && lmap->getCurrentRoom() != lmap->getLevelUpRoom()) {
				centered = true;
				inFunction = true;
				changeView(lmap, deltaTime);
				spawnEnemies(lmap);
				while (window.pollEvent(event)) {

				}

				//if room is cleared and player is inside, locks window view to players position until unvisited room is found
			}
			else if (lmap->getCurrentRoom()->isCleared) {
				lmap->findCurrentRoom(lmap->head, player);
				roomView.setCenter(player->getPlayer().getPosition());
				window.setView(roomView);
				centered = false;
			}
			else if (Enemy::getEnemies().size() == 0) { //If all enemies have been killed, room is cleared;
				lmap->getCurrentRoom()->isCleared = true;
			}






			lmap->doesCollide(player);
			window.clear(); //Clears window

			lmap->displayCurrentRoom(lmap->getHead(), window, lmap->getCurrentRoom()->isCleared); //Draws Map

			if (lmap->getCurrentRoom() == lmap->getLevelUpRoom()) {
				lmap->displayStairs(window, player);
			}
			if (lmap->getCurrentRoom() == lmap->getChestRoom1()) {
				lmap->displayChest1(window, player, chestIsLookedAt);
			}
			if (lmap->getCurrentRoom() == lmap->getChestRoom2()) {
				lmap->displayChest2(window, player, chestIsLookedAt2);
			}
			player->displayPlayerInfo(window); //Draws player info: health, stamina, name


			levelText.setPosition(window.getView().getCenter().x + window.getView().getSize().x / 2 - 180, window.getView().getCenter().y - window.getView().getSize().y / 2 + 100);
			window.draw(levelText);


			if (!inFunction) {
				//Draws Enemmies to screen
				for (unsigned i = 0; i < Enemy::getEnemies().size(); i++) {
					Enemy::getEnemies()[i]->Update(player, deltaTime);
					Enemy::getEnemies()[i]->Draw(window);
					if (Enemy::getEnemies()[i]->isDead()) {
						Enemy::Destroy(Enemy::getEnemies().begin() + i);
					}
				}
				player->Update(window, deltaTime); //Updates player position
			}
			player->Draw(window); //Draws player to screen
			for (unsigned i = 0; i < player->getWeapons().size(); i++) {
				player->getWeapons()[i].Update(window, player, deltaTime); //Updates weapons and bullets
			}
			player->getCurrentWeapon().displayWeaponInfo(window); //draws gun name, bullets and ammo

			if(!lmap->getChest1()->getIsOpen() && chestIsLookedAt && lmap->getCurrentRoom() == lmap->getChestRoom1()) {
				lmap->getChest1()->choicePrompt.setPosition(player->getPlayer().getPosition());
				window.draw(lmap->getChest1()->choicePrompt);
			}
			if(lmap->getCurrentRoom() != lmap->getChestRoom1()){
				chestIsLookedAt = false;
			}
			if(lmap->getCurrentRoom() != lmap->getChestRoom2()){
				chestIsLookedAt2 = false;
			}

			if(!lmap->getChest2()->getIsOpen() && chestIsLookedAt2 && lmap->getCurrentRoom() == lmap->getChestRoom2()) {
				lmap->getChest2()->choicePrompt.setPosition(player->getPlayer().getPosition().x,player->getPlayer().getPosition().y - 50);
				window.draw(lmap->getChest2()->choicePrompt);
			}

            if (displayChestTime.getElapsedTime().asSeconds() < 4.f) {
                lmap->displayChestUI(player, window);
            }

			window.display(); //Displays all drawn objects

			if (player->isDead()) {
				music.stop();
				return GameOver(deltaTime);
			}
			if (inFunction) {
				inFunction = false;
				while (window.pollEvent(event)) {

				}
				player->isMovingUp = false;
				player->isMovingDown = false;
				player->isMovingLeft = false;
				player->isMovingRight = false;
				player->bCanRegenStamina = false;
				player->bIsSprinting = false;
			}
		}
	}
	return false;
}

void GameManager::changeView(LinkedMap *lmap, float dt) {
	sf::View viewMotion = roomView;
	sf::Vector2f direction;

	//bounds rectangle for determining intersection between view and room center, for slow transition to room center before enemies spawning
	sf::RectangleShape bounds;
	bounds.setSize(sf::Vector2f(20, 20));
	bounds.setOrigin(bounds.getSize().x / 2, bounds.getSize().y / 2);
	bounds.setPosition(lmap->getCurrentRoom()->floor.getPosition());

	sf::RectangleShape vectorSquare;

	vectorSquare.setSize(sf::Vector2f(10, 10));
	vectorSquare.setOrigin(10, 10);

	//gets vector from player to room center, and normalizes it
	direction = (lmap->getCurrentRoom()->floor.getPosition() - player->getPlayer().getPosition());
	float mag = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	direction.x = direction.x / mag;
	direction.y = direction.y / mag;

	//until view center intersects room center, increment view by normalized vector
	while (!bounds.getGlobalBounds().intersects(vectorSquare.getGlobalBounds())) {
		window.clear();
		vectorSquare.setPosition(window.getView().getCenter());
		viewMotion.move(direction*(dt * 1000));

		window.setView(viewMotion);
		lmap->displayCurrentRoom(lmap->getHead(), window, lmap->getCurrentRoom()->isCleared);
		window.display();
	}
	roomView.setCenter(lmap->getCurrentRoom()->floor.getPosition());
	window.setView(roomView);
	sf::Vector2f playerDir = roomView.getCenter() - player->getPlayer().getPosition();
	mag = sqrt(pow(playerDir.x, 2) + pow(playerDir.y, 2));
	sf::Vector2f playerDirU = sf::Vector2f(playerDir.x / mag, playerDir.y / mag);
	player->getPlayer().move(75*playerDirU.x,75*playerDirU.y);
}

Player* GameManager::createPlayer() {
	window.setKeyRepeatEnabled(true);
	bool created = false;

	//Creates textbox
	sf::RectangleShape textBox(sf::Vector2f(250, 50));
	textBox.setOrigin(textBox.getSize().x/2,textBox.getSize().y/2);
	textBox.setPosition(window.getView().getCenter().x , window.getView().getCenter().y);
	textBox.setFillColor(sf::Color::Transparent);
	textBox.setOutlineColor(sf::Color::Red);
	textBox.setOutlineThickness(2);

	sf::Text text; //Creates text object for name to be drawn to screen
	text.setFont(font);
	text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
	text.setPosition(textBox.getPosition().x, textBox.getPosition().y -16);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::White);

	sf::Text namePrompt; //Creates text object for user prompt
	namePrompt.setFont(font);
	namePrompt.setString("Enter your name:");
    namePrompt.setOrigin(namePrompt.getGlobalBounds().width/2, namePrompt.getGlobalBounds().height/2);
	namePrompt.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 100);
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
			if (event.type == event.Closed) {
                window.close();
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
	return new Player(name);
}

bool GameManager::GameOver(float dt) {
	std::cout << "You have died" << std::endl;
	Enemy::getEnemies().clear();

	sf::Event event;
	sf::Text restartButton;
	restartButton.setFont(font);
	restartButton.setCharacterSize(48);
	restartButton.setString("Restart");
	restartButton.setOrigin(restartButton.getGlobalBounds().width / 2, restartButton.getGlobalBounds().height / 2);
	restartButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 100);

	//Adds quit button to menu screen
	sf::Text exitButton;
	exitButton.setFont(font);
	exitButton.setCharacterSize(48);
	exitButton.setString("Quit");
	exitButton.setOrigin(exitButton.getGlobalBounds().width / 2, exitButton.getGlobalBounds().height / 2);
	exitButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 100);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setCharacterSize(80);
	gameOverText.setString("Game Over");
	gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2, gameOverText.getGlobalBounds().height / 2);
	gameOverText.setPosition(window.getView().getCenter().x - window.getView().getSize().x,
							 window.getView().getCenter().y - 350);

	sf::RectangleShape fade;
	fade.setSize(window.getView().getSize());
	fade.setFillColor(sf::Color(0, 0, 0, 1));
	fade.setOrigin(fade.getSize().x / 2, fade.getSize().y / 2);
	fade.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);

	//Fades into GameOver
	for (int i = 2; i < 250; i++) {
		window.draw(fade);
		window.display();
		fade.setFillColor(sf::Color(0, 0, 0, i));
	}
	while (gameOverText.getPosition().x < window.getView().getCenter().x) {
		gameOverText.move(200*dt,0);
		window.clear();
		window.draw(fade);
		window.draw(gameOverText);
		window.display();
	}
	while (window.isOpen()) {
		//Activates buttons if pressed, respectively
		if (restartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			restartButton.setCharacterSize(58);//enlarges text when mouse is hovering over
			restartButton.setOrigin(restartButton.getGlobalBounds().width / 2,
									restartButton.getGlobalBounds().height / 2);
			restartButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 100);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return true;
			}
		} else {
			restartButton.setCharacterSize(48);
			restartButton.setOrigin(restartButton.getGlobalBounds().width / 2,
									restartButton.getGlobalBounds().height / 2);
			restartButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 100);
		}
		if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			exitButton.setCharacterSize(58); //enlarges text when mouse is hovering over
			exitButton.setOrigin(exitButton.getGlobalBounds().width / 2, exitButton.getGlobalBounds().height / 2);
			exitButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 100);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return false;
			}
		} else {
			exitButton.setCharacterSize(48);
			exitButton.setOrigin(exitButton.getGlobalBounds().width / 2, exitButton.getGlobalBounds().height / 2);
			exitButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 100);
		}
		while (window.pollEvent(event)) {

			if (event.type == event.Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(fade);
		window.draw(gameOverText);
		window.draw(restartButton);
		window.draw(exitButton);
		window.display();
	}

	return true;
}

void GameManager::LoadingScreen() {
	sf::Music music;
	if (!music.openFromFile("Music/LoadingScreen.wav")) {
		std::cout << "Could not open music file"<<std::endl;
		return;
	}
	music.play();
	music.setLoop(true);
	sf::Text title;
	sf::Text playButton;
	title.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 300);
	title.setFont(font);
	title.setString("TrapHouse");
	playButton.setCharacterSize(50);
	playButton.setFont(font);
	playButton.setString("Play");
	
	float x = 0;
	sf::Clock deltaTime;
	while (window.isOpen()) {
		x += .001f;
		title.move(0, sin(x)/100);
		title.setCharacterSize(150);
		title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
				playButton.setCharacterSize(60);
				playButton.setOrigin(playButton.getGlobalBounds().width / 2, playButton.getGlobalBounds().height / 2);
				playButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					player = createPlayer();
					return;
				}
			}
			else {
				playButton.setCharacterSize(50);
				playButton.setOrigin(playButton.getGlobalBounds().width / 2, playButton.getGlobalBounds().height / 2);
				playButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
			}
		}
		window.clear();
		window.draw(title);
		window.draw(playButton);
		window.display();
	}
}

void GameManager::levelUp(LinkedMap* lmap){
	delete(lmap);
	level++;
	player->getPlayer().setPosition(0,0);
	Start();
}

void GameManager::Pause() {
	sf::Music music;
	if (!music.openFromFile("Music/PauseMusic.wav")) {
		std::cout << "Could not open music file" << std::endl;
	}
	music.play();
	music.setLoop(true);
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
				    return;
				}
			}
	    	if (event.type == event.Closed) {
			    window.close();
            }
		}
		window.clear();
		window.draw(resumeButton);
		window.draw(exitButton);
        window.display();
	}
}

void GameManager::DisplayMap(Player* player, LinkedMap* linkedMap) {
	sf::Event event;
	sf::View mapView;
	sf::View roomView;
	bool windowMoving = false;
	sf::Vector2f oldMousePos;
	sf::Vector2f newMousePos;
	sf::Vector2f diffPosition;


	roomView = window.getView();
	//Shows large portion of map
	mapView.setSize(8000, 8000);
	//Centers view of map around player
	mapView.setCenter(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	window.setView(mapView);

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			/*
			 * Methods For changing window location by clicking and dragging mouse
			 */
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == 0) {
					oldMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					windowMoving = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == 0) {
					windowMoving = false;
				}

			}
			else if (event.type == sf::Event::MouseMoved) {
				if (windowMoving) {
					newMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					diffPosition = oldMousePos - newMousePos;
					mapView.setCenter(mapView.getCenter() + diffPosition);
					window.setView(mapView);

					//Sets old position = new position, based on new window, for the next time the mouse is moved
					oldMousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::M) {
					window.setView(roomView);
					return;
				}
			}
			if (event.type == event.Closed) {
				window.close();
			}
		}
		window.clear();
		linkedMap->displayMap(linkedMap->head, window);
		player->Draw(window);
		window.display();
	}
}


void GameManager::spawnEnemies(LinkedMap* linkedMap) {

	int numOfEnemies;


    //Spawning monsters
    numOfEnemies = rand() % 3 + level;

  for (int i = 0; i < numOfEnemies; i++) {
        Enemy::Spawn(new Skeleton("Skeleton", 64 + ((level - 1) * 20), 10 + ((level - 1) * 2)),
                     linkedMap->getCurrentRoom());
    }

    numOfEnemies = rand() % 5 + level;
    for (int i = 0; i < numOfEnemies; i++) {
        Enemy::Spawn(new Spider("Spider", 25 + ((level - 1) * 10), 2 + (level - 1)), linkedMap->getCurrentRoom());
    }

    numOfEnemies = rand() % 2 + (level - 1);
    for (int i = 0; i < numOfEnemies; i++) {
        Enemy::Spawn(new Troll("Troll", 300 + ((level - 1) * 20), 10 + ((level - 1) * 2)), linkedMap->getCurrentRoom());
    }
}

void GameManager::restrictMovement() {
	player->isMovingDown = false;
	player->isMovingUp = false;
	player->isMovingLeft = false;
	player->isMovingRight = false;
	player->bIsSprinting = false;
}
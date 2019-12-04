#include "PauseScreen.h"

PauseScreen::PauseScreen(sf::Font &font)
{
	resume.setFont(font);
	resume.setCharacterSize(48);
	resume.setString("Resume");
	resume.setOrigin(resume.getGlobalBounds().width / 2, resume.getGlobalBounds().height / 2);
	//resume.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 200);

	//Adds quit button to menu screen
	exit.setFont(font);
	exit.setCharacterSize(48);
	exit.setString("Quit");
	exit.setOrigin(exit.getGlobalBounds().width / 2, exit.getGlobalBounds().height / 2);
	//exit.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
}

void PauseScreen::draw(sf::RenderWindow &window)
{
	sf::Music music;
	if (!music.openFromFile("Music/PauseMusic.wav"))
	{
		std::cout << "Could not open music file" << std::endl;
	}
	music.play();
	music.setLoop(true);

	resume.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 200);
	exit.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return;
				}
			}
			else if (event.type == event.Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				//Activates buttons if pressed, respectively
				if (resume.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				{
					resume.setCharacterSize(58); //enlarges text when mouse is hovering over
					resume.setOrigin(resume.getGlobalBounds().width / 2, resume.getGlobalBounds().height / 2);
					resume.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 200);
				}
				else if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				{
					exit.setCharacterSize(58); //enlarges text when mouse is hovering over
					exit.setOrigin(exit.getGlobalBounds().width / 2, exit.getGlobalBounds().height / 2);
					exit.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
				}
				else
				{
					resume.setCharacterSize(48);
					resume.setOrigin(resume.getGlobalBounds().width / 2, resume.getGlobalBounds().height / 2);
					resume.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 200);
					exit.setCharacterSize(48);
					exit.setOrigin(exit.getGlobalBounds().width / 2, exit.getGlobalBounds().height / 2);
					exit.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (resume.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				{
					return;
				}
				else if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				{
					window.close();
				}
			}
		}
		window.clear();
		window.draw(resume);
		window.draw(exit);
		window.display();
	}
}

#include "CreatePlayerScreen.h"

CreatePlayerScreen::CreatePlayerScreen(sf::Font& font) : textBox(sf::Vector2f(250, 50))
{
    textBox.setOrigin(textBox.getSize().x / 2, textBox.getSize().y / 2);
	textBox.setFillColor(sf::Color::Transparent);
	textBox.setOutlineColor(sf::Color::Red);
	textBox.setOutlineThickness(2);

    nameInput.setFont(font);
	nameInput.setOrigin(nameInput.getGlobalBounds().width / 2, nameInput.getGlobalBounds().height / 2);
	nameInput.setCharacterSize(25);
	nameInput.setFillColor(sf::Color::White);

	namePrompt.setFont(font);
	namePrompt.setString("Enter your name:");
	namePrompt.setOrigin(namePrompt.getGlobalBounds().width / 2, namePrompt.getGlobalBounds().height / 2);
	namePrompt.setFillColor(sf::Color::White);
}

std::string CreatePlayerScreen::draw(sf::RenderWindow &window)
{
	window.setKeyRepeatEnabled(true);

	textBox.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
	nameInput.setPosition(textBox.getPosition().x, textBox.getPosition().y - 16);
	namePrompt.setPosition(window.getView().getCenter().x - 100, window.getView().getCenter().y - 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace && playerName.size() > 0)
				{
					playerName = playerName.substr(0, playerName.size() - 1);
					nameInput.setString(playerName);
					nameInput.setPosition(nameInput.getPosition().x + (textBox.getSize().x / (nameInput.getCharacterSize() * 1.15f)), nameInput.getPosition().y);
				}
				if (playerName.size() > 0 && event.key.code == sf::Keyboard::Return)
				{
					window.setKeyRepeatEnabled(false);
					return playerName;
				}
			}
			if (event.type == sf::Event::TextEntered && (char)event.text.unicode != '\b' && playerName.size() < 10)
			{
				playerName += (char)event.text.unicode;
				nameInput.setString(playerName);
				nameInput.setPosition(nameInput.getPosition().x - (textBox.getSize().x / (nameInput.getCharacterSize() * 1.15f)), nameInput.getPosition().y);
			}
			if (event.type == event.Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(nameInput);
		window.draw(namePrompt);
		window.draw(textBox);
		window.display();
	}
}

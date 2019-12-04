#include "StartScreen.h"

StartScreen::StartScreen(sf::Font& font)
{   
    title.setFont(font);
    title.setString("TrapHouse");
    playButton.setCharacterSize(50);
    playButton.setFont(font);
    playButton.setString("Play");
}

void StartScreen::draw(sf::RenderWindow &window)
{
    sf::Music music;
    if (!music.openFromFile("Music/LoadingScreen.wav"))
    {
        std::cout << "Could not open music file" << std::endl;
    }
    title.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 300);
    music.play();
    music.setLoop(true);

    float x = 0;
    while (window.isOpen())
    {
        x += .001f;
        title.move(0, sin(x) / 100);
        title.setCharacterSize(150);
        title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                playButton.setCharacterSize(60);
                playButton.setOrigin(playButton.getGlobalBounds().width / 2, playButton.getGlobalBounds().height / 2);
                playButton.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    return;
                }
            }
            else
            {
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

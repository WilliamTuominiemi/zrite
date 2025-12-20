#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <functional>

#include "button.h"

void playSound(sf::Sound *sound)
{
    sound->play();
}

void pauseSound(sf::Sound *sound)
{
    sound->pause();
}

int main()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../sound.wav"))
        return -1;

    sf::Sound sound;

    sound.setBuffer(buffer);

    const int WIDTH = 350;
    const int HEIGHT = 150;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Audio player");
    window.setFramerateLimit(60);

    std::vector<Button> buttons;

    sf::Font font;
    font.loadFromFile("/mnt/c/Windows/Fonts/arial.ttf");

    Button playButton(50.f, 50.f, 100.f, 50.f, sf::Color::White, "Play", font,
                      [&sound]()
                      {
                          sound.play();
                      });
    Button pauseButton(200.f, 50.f, 100.f, 50.f, sf::Color::White, "Pause", font,
                       [&sound]()
                       { sound.pause(); });

    buttons.emplace_back(playButton);
    buttons.emplace_back(pauseButton);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (auto &button : buttons)
                {
                    button.handleClick(mousePos);
                }
            }
        }

        window.clear(sf::Color::Black);

        for (auto &button : buttons)
        {
            button.render(&window);
        }

        window.display();
    }

    return 0;
}

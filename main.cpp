#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <functional>

class Button
{
private:
    sf::RectangleShape ref;
    sf::Text textRef;
    float x;
    float y;
    float width;
    float height;
    sf::Color color;
    std::function<void()> onClick;

public:
    Button(float x, float y, float width, float height, sf::Color color, std::string text, sf::Font &font, std::function<void()> callback)
        : onClick(callback)
    {
        ref.setSize(sf::Vector2f(width, height));
        ref.setPosition(x, y);
        ref.setFillColor(color);

        textRef.setFont(font);
        textRef.setString(text);
        textRef.setCharacterSize(24);
        textRef.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = textRef.getLocalBounds();
        textRef.setOrigin(textBounds.left + textBounds.width / 2.0f,
                          textBounds.top + textBounds.height / 2.0f);
        textRef.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    sf::RectangleShape get()
    {
        return ref;
    }

    void render(sf::RenderWindow *window)
    {
        window->draw(ref);
        window->draw(textRef);
    }

    bool contains(sf::Vector2i mousePos) const
    {
        return ref.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void handleClick(sf::Vector2i mousePos)
    {
        if (contains(mousePos))
        {
            onClick();
        }
    }
};

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

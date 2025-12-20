#include <SFML/Graphics.hpp>
#include <functional>

#pragma once
#ifndef BUTTON_H
#define BUTTON_H

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
    Button(float x, float y, float width, float height, sf::Color color, std::string text, sf::Font &font, std::function<void()> callback);
    sf::RectangleShape get();
    void render(sf::RenderWindow *window);
    bool contains(sf::Vector2i mousePos) const;
    void handleClick(sf::Vector2i mousePos);
};
#endif
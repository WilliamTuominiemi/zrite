#include "button.h"

Button::Button(float x, float y, float width, float height, sf::Color color, std::string text, sf::Font &font, std::function<void()> callback)
    : x(x), y(y), width(width), height(height), color(color), onClick(callback)
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

sf::RectangleShape Button::get()
{
    return ref;
}

void Button::render(sf::RenderWindow *window)
{
    window->draw(ref);
    window->draw(textRef);
}

bool Button::contains(sf::Vector2i mousePos) const
{
    return ref.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::handleClick(sf::Vector2i mousePos)
{
    if (contains(mousePos))
    {
        onClick();
    }
}
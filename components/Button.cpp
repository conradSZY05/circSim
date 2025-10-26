#include "Button.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

Button::Button(sf::Vector2f parentPosition, sf::Vector2f position)
{
    this->parentPosition = parentPosition;
    this->position = position;

    this->button.setRadius(4.f);
    this->button.setPosition(parentPosition + position);
    this->button.setFillColor(sf::Color::White);
    this->button.setOutlineColor(sf::Color::Black);
    this->button.setOutlineThickness(1.f);
}

void Button::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

    this->isHover = false;
    this->isPressed = false;

    if(button.getGlobalBounds().contains(mousePosView))
    {
        this->isHover = true;

        if(event.type == sf::Event::MouseButtonReleased)
        {
            this->isPressed = true;
        }
    }

    if(isHover)
    {
        // could change the colour here, do some stuff to the size
        button.setPosition(parentPosition.x + position.x - 1.f, parentPosition.y + position.y - 1.f);
        button.setRadius(5.f);
    }
    else
    {
        // use normal colour and normal size
        button.setPosition(parentPosition + position);
        button.setRadius(4.f);
    }

}
void Button::draw(sf::RenderWindow& window)
{
    window.draw(this->button);
}
void Button::changePosition(sf::Vector2f newParentPosition)
{
    parentPosition = newParentPosition;
    this->button.setPosition(newParentPosition + position);
}
bool Button::getIsHover() { return isHover; }
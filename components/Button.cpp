#include "Button.hpp"
#include "../ResourceManager.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../colors.cpp"

Button::Button(sf::Vector2f parentPosition, sf::Vector2f position)
{
    this->parentPosition = parentPosition;
    this->position = position;
}
int Button::nextID = 1;
int Button::getID() { return id; }
void Button::draw(sf::RenderWindow& window) {}
void Button::getButtonStatus(sf::RenderWindow& window, sf::Event& event) {}
void Button::changePosition(sf::Vector2f newParentPosition) {}
bool Button::getIsHover() { return isHover; }
void Button::setCallback(std::function<void()> cb) { callback = std::move(cb); }
void Button::trigger() { if(callback) callback(); }
bool Button::getIsConnected() { return isConnected; }
bool Button::getIsConnecting() { return isConnecting; }
void Button::connect() { isConnected = true; }
void Button::disconnect() { isConnected  = false; }
sf::Vector2f Button::getPosition() { return parentPosition + position; }


CircleButton::CircleButton(sf::Vector2f parentPosition, sf::Vector2f position)
: Button(parentPosition, position)
{
    this->id = nextID++;
    this->isConnected = false;
    this->isConnecting = false;
    this->button.setRadius(4.f);
    this->radius = 4.f;
    this->button.setPosition(parentPosition + position);
    this->button.setFillColor(White);
    this->button.setOutlineColor(Black);
    this->button.setOutlineThickness(1.f);
}
void CircleButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

    this->isHover = false;
    this->isPressed = false;

    if(button.getGlobalBounds().contains(mousePosView)) {
        this->isHover = true;

        if(event.type == sf::Event::MouseButtonPressed) {
            this->isPressed = true;
            this->isConnecting = !this->isConnecting;
            trigger();
        }
    }

    if(isConnecting) {
        button.setFillColor(Black);
    } else {
        button.setFillColor(White);
    }

    if(isHover) {
        // could change the colour here, do some stuff to the size
        button.setPosition(parentPosition.x + position.x - 1.f, parentPosition.y + position.y - 1.f);
        button.setRadius(5.f);
    } else {
        // use normal colour and normal size
        button.setPosition(parentPosition + position);
        button.setRadius(4.f);
    }
}
void CircleButton::draw(sf::RenderWindow& window)
{
    window.draw(this->button);
}
void CircleButton::changePosition(sf::Vector2f newParentPosition)
{
    parentPosition = newParentPosition;
    this->button.setPosition(newParentPosition + position);
}
sf::Vector2f CircleButton::getPosition() { return parentPosition + position + sf::Vector2f(radius, radius); } // override here to return centre of the circle instead of the top left corner


RectangleButton::RectangleButton(sf::Vector2f parentPosition, sf::Vector2f position, float xSze, float ySze)
: Button(parentPosition, position),
xSize(xSze),
ySize(ySze)
{
    this->button.setSize(sf::Vector2f{ xSize, ySize });
    this->button.setPosition(parentPosition + position);
    this->button.setFillColor(LightGray);
    this->button.setOutlineColor(White);
    this->button.setOutlineThickness(0.5f);
}
void RectangleButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

    this->isHover = false;
    this->isPressed = false;

    if(button.getGlobalBounds().contains(mousePosView)) {
        this->isHover = true;

        if(event.type == sf::Event::MouseButtonPressed) {
            this->isPressed = true;
            trigger();
        }
    }

    if(isHover) {
        // could change the colour here, do some stuff to the size
        button.setPosition(parentPosition.x + position.x - 1.f, parentPosition.y + position.y - 1.f);
        button.setSize(sf::Vector2f{ xSize+2.f, ySize+2.f });
    } else {
        // use normal colour and normal size
        button.setPosition(parentPosition + position);
        button.setSize(sf::Vector2f{ xSize, ySize });
    }
}
void RectangleButton::draw(sf::RenderWindow& window)
{
    window.draw(this->button);
    window.draw(this->text);
}
void RectangleButton::changePosition(sf::Vector2f newParentPosition)
{
    parentPosition = newParentPosition;
    this->button.setPosition(newParentPosition + position);
}





TextButton::TextButton(sf::Vector2f parentPosition, sf::Vector2f position, std::string str, int ind, float xSze, float ySze)
: RectangleButton(parentPosition, position, xSze, ySze)
{
    sf::Font* font = ResourceManager::getFont("./models/Fonts/W95FA.otf");
    this->text.setFont(*font);
    this->text.setString(str);
    this->text.setCharacterSize(15);
    this->text.setPosition(parentPosition + position);
    this->text.setFillColor(Black);
}



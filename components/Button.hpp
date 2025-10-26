#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Button 
{
    public:
        Button(sf::Vector2f parentPosition, sf::Vector2f position);
        virtual ~Button() = default;
        void draw(sf::RenderWindow& window);
        void getButtonStatus(sf::RenderWindow& window, sf::Event& event);
        void changePosition(sf::Vector2f newParentPosition);
        bool getIsHover();


    protected:
        sf::CircleShape button;
        sf::Vector2f parentPosition, position; // position is just an offset of parentPosition
        bool isHover, isPressed, isConnected;
};

class InputButton : public Button 
{
    public:
        InputButton(sf::Vector2f parentPosition, sf::Vector2f position)
        : Button(parentPosition, position) {};
};

class OutputButton : public Button
{
    public:
        OutputButton(sf::Vector2f parentPosition, sf::Vector2f position)
        : Button(parentPosition, position) {};
}; 
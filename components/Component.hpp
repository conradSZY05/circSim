#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "Button.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class Component
{
    public:
        Component(sf::Vector2f mousePos); //mousePos is initial setpos location
        virtual ~Component() = default; //virtual destructor

        virtual void changePosition(sf::Vector2f mousePos);
        virtual sf::Sprite& getComponent(); 
        virtual void update(); 
        sf::Vector2f getPos();
        void draw(sf::RenderWindow& window);
        void handleMouseEvent(sf::RenderWindow& window, sf::Event event, sf::Vector2f mousePos, bool gridSnapping); // interaction stuff
        void setMoving(bool moving);
        void setMouseClickedOffset(sf::Vector2f mousePos);

    protected:
        virtual void setType(sf::Vector2f mousePos); //take dropdown string as parameter here
        virtual void initButtons();

    protected:
        sf::Vector2f position, mouseClickedOffset;
        sf::Sprite spr;
        std::vector<std::unique_ptr<Button>> buttons;
        bool isMoving;
};
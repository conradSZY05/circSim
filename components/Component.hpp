#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "Button.hpp"
#include <memory>
#include <vector>

class Component
{
    public:
        Component(sf::Vector2f mousePos); //mousePos is initial setpos location
        virtual ~Component() = default; //virtual destructor

        virtual void changePosition(sf::Vector2f mousePos);
        virtual sf::Sprite& getComponent(); 
        virtual void update() {}; //allows children to override
        sf::Vector2f getPos();

    protected:
        virtual void setType(sf::Vector2f mousePos); //take dropdown string as parameter here
        virtual void initButtons();

    protected:
        sf::Vector2f position;
        sf::Sprite type;
        std::vector<std::unique_ptr<Button>> buttons;
};
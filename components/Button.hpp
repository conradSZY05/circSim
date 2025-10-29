#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

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
        InputButton(sf::Vector2f parentPosition, sf::Vector2f position);
    
};

class OutputButton : public Button
{
    public:
        OutputButton(sf::Vector2f parentPosition, sf::Vector2f position);
}; 

class TextButton : public Button
{
    public:
        TextButton(sf::Vector2f parentPosition, sf::Vector2f position, std::string str, int ind);
        void setCallback(std::function<void()> cb);
        void trigger();
        void handleEvent(sf::Event& event);

    private:
        std::function<void()> callback;
        std::string text;
        int index;

};
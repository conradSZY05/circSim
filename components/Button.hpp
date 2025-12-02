#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

enum class ButtonType { Input, Output, Unknown };

class Button 
{
    public:
        Button(sf::Vector2f parentPosition, sf::Vector2f position);
        virtual ~Button() = default;
        virtual void draw(sf::RenderWindow& window);
        virtual void getButtonStatus(sf::RenderWindow& window, sf::Event& event);
        virtual void changePosition(sf::Vector2f newParentPosition);
        virtual ButtonType getType() const { return ButtonType::Unknown; }
        bool getIsHover();
        bool getIsConnecting();
        void connect();
        void disconnect();
        int getID();
        virtual sf::Vector2f getPosition();

        void setCallback(std::function<void()> cb);
        void trigger();


    protected:
        sf::Vector2f parentPosition, position; // position is just an offset of parentPosition
        bool isHover, isPressed, isConnecting;
        std::function<void()> callback;
        sf::Text text;

        static int nextID;
        int id;
};

class CircleButton : public Button
{
    public: 
        CircleButton(sf::Vector2f parentPosition, sf::Vector2f position);
        void draw(sf::RenderWindow& window) override;
        void getButtonStatus(sf::RenderWindow& window, sf::Event& event) override;
        void changePosition(sf::Vector2f newParentPosition) override;
        sf::Vector2f getPosition() override;
        


    protected:
        sf::CircleShape button;
        float radius;

};

class RectangleButton : public Button 
{
    public:
        RectangleButton(sf::Vector2f parentPosition, sf::Vector2f position, float xSze, float ySze);
        void draw(sf::RenderWindow& window) override;
        void getButtonStatus(sf::RenderWindow& window, sf::Event& event) override;
        void changePosition(sf::Vector2f newParentPosition) override;


    protected:
        sf::RectangleShape button;
        float xSize, ySize;
};

class InputButton : public CircleButton
{
    public:
        InputButton(sf::Vector2f parentPosition, sf::Vector2f position)
        : CircleButton(parentPosition, position) {}

        ButtonType getType() const override { return ButtonType::Input; }

    
};

class OutputButton : public CircleButton
{
    public:
        OutputButton(sf::Vector2f parentPosition, sf::Vector2f position)
        : CircleButton(parentPosition, position) {}

        ButtonType getType() const override { return ButtonType::Output; }

}; 

class TextButton : public RectangleButton
{
    public:
        TextButton(sf::Vector2f parentPosition, sf::Vector2f position, std::string str, int ind, float xSze, float ySze);

};
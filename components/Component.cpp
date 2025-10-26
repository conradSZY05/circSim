#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>



Component::Component(sf::Vector2f mousePos)
: position(mousePos)
, mouseClickedOffset(0.f, 0.f)
, spr()
, isMoving(false)
{
    // initialise
    spr.setPosition(mousePos);
    
}
void Component::setType(sf::Vector2f mousePos) //should return a vertex array but for now just a circleshape
{
    //std::cout << mousePos.x << ", " << mousePos.y << "\n";
    //should take dropdown menu as paramater here but for now just add a circle
    //using the dropdown menu paramter chosen
    //exture.loadFromFile("./models/and.png");
    //type.setTexture(texture);
    //type.setTextureRect({{0, 0}, {100, 60}});
    //type.setPosition(mousePos);

}
void Component::changePosition(sf::Vector2f mousePos)
{
    position = mousePos;
    spr.setPosition(mousePos); //draggina dn dropping
    // change button positions
    for(auto& b : buttons)
    {
        b->changePosition(mousePos);
    }
}
sf::Sprite& Component::getComponent() { return spr; }
sf::Vector2f Component::getPos() { return position; }
void Component::initButtons() {};
void Component::update() {};
void Component::draw(sf::RenderWindow& window)
{
    window.draw(this->spr);
    for(auto& btn : this->buttons) 
    {
        //check mouse over button
        btn->draw(window);
    }

}
void Component::handleMouseEvent(sf::RenderWindow& window, sf::Event event, sf::Vector2f mousePos)
{
    for(auto& b : buttons)
    {
        b->getButtonStatus(window, event);
    }
    if(isMoving) 
    {
        this->changePosition(mousePos - this->mouseClickedOffset);
    }
    else
    {
        // dropping
    }
}
void Component::setMoving(bool moving) { isMoving = moving; };
void Component::setMouseClickedOffset(sf::Vector2f mousePos)
{
    this->mouseClickedOffset = mousePos - this->position;
}
bool Component::interactingWithButton()
{
    bool hover = false;
    for(auto& b : buttons)
    {
        if(b->getIsHover())
            hover = true;
    }
    return hover;
}
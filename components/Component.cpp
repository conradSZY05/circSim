#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>



Component::Component(sf::Vector2f mousePos)
:type()
{
    // initialise
    
    
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
    type.setPosition(mousePos); //draggina dn dropping
}
sf::Sprite& Component::getComponent() { return type; }
sf::Vector2f Component::getPos() { return position; }
void Component::initButtons() {};
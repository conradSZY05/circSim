#include "AndGate.hpp"
#include "Button.hpp"
#include "../ResourceManager.hpp"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <iostream>

AndGate::AndGate(sf::Vector2f mousePos):Component(mousePos)
{
    setType(mousePos);
    //initButtons();
}
void AndGate::setType(sf::Vector2f mousePos)
{
    std::cout << "and gate loaded";
    sf::Texture* texture = ResourceManager::getTexture("./models/and.png");
    type.setTexture(*texture);
    type.setPosition(mousePos);

    // scale to a reasonable size
    float desiredWidth = 67.f;
    float scaleX = desiredWidth / texture->getSize().x;
    float scaleY = scaleX; // keep aspect ratio
    type.setScale(scaleX, scaleY);
}
void AndGate::update()
{
    //add AND logic
}
void AndGate::initButtons()
{

    buttons.push_back(std::make_unique<InputButton>(position, sf::Vector2f{0.f, 10.f}));

}
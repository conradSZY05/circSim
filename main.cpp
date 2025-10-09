#include <SFML/Graphics.hpp>
#include <iostream>

//class headers
#include "Component.hpp"
#include "Simulator.hpp"



int main()
{
    Simulator simulator;
    simulator.run();


    return 0;
}

AndGate::AndGate(sf::Vector2f mousePos):Component(mousePos)
{
    setType(mousePos);
}
void AndGate::setType(sf::Vector2f mousePos)
{
    //std::cout << "and gate loaded";
    texture.loadFromFile("./models/and.png");
    type.setTexture(texture);
    type.setPosition(mousePos);

    // scale to a reasonable size
    float desiredWidth = 67.f;
    float scaleX = desiredWidth / texture.getSize().x;
    float scaleY = scaleX; // keep aspect ratio
    type.setScale(scaleX, scaleY);
}
void AndGate::update()
{
    //add AND logic
}

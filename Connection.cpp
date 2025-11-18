#include "Connection.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>

#include "colors.cpp"


Connection::Connection(int one, int two)
{
    this->conone = one;
    this->contwo = two;
}

void Connection::draw(sf::RenderWindow& window, std::vector<std::unique_ptr<Component>>& components)
{
    // find the points of the buttons in this connection
    sf::Vector2f point1, point2;
    for(auto& component : components) {
        for(auto& btn : component->getButtons()) {
            if(btn->getID() == this->conone)
                point1 = btn->getPosition();
            else if(btn->getID() == this->contwo) 
                point2 = btn->getPosition();
        }
    }

    // need to implement A star 
    sf::VertexArray line(sf::Lines, 4);
    line[0].position = point1;
    line[0].color = Red;
    line[1].position = sf::Vector2f(point1.x, point2.y);
    line[1].color = Red;
    line[2] = line[1];
    line[3].position = point2;
    line[3].color = Red;

    window.draw(line);
}
sf::VertexArray Connection::generateConnectionVertex() 
{

    return sf::VertexArray();
}
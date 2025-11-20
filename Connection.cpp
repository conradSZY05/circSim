#include "Connection.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "colors.cpp"

Connection::Connection(int one, int two) 
: resistance(0.f),
current(0.f)
{
    this->conone = one;
    this->contwo = two;
}
void Connection::drawToMouse(sf::RenderWindow& window, sf::Vector2f mousePos)
{
    connectionPoints[connectionPoints.size() - 1] = mousePos;
}
void Connection::addNewPoint(sf::Vector2f newPoint)
{
    connectionPoints.push_back(newPoint);
}
void Connection::draw(sf::RenderWindow& window)
{
    sf::VertexArray line(sf::Lines, connectionPoints.size());
    for(int i = 0; i < connectionPoints.size(); ++i) {
        line[i].position = connectionPoints[i];
        line[i].color = Red;
    }
    window.draw(line);
}
void Connection::update(std::vector<std::unique_ptr<Component>>& components)
{
    sf::Vector2f point1, point2;
    for(auto& cmp : components) {
        for(auto& btn : cmp->getButtons()) {
            
        }
    }
}
bool Connection::isPending() { return conone != -1 && contwo == -1; }
int Connection::getConOne() { return conone; }
int Connection::getConTwo() { return contwo; }
void Connection::setConnectionIDs(int one, int two) 
{
    this->conone = one;
    this->contwo = two;
}
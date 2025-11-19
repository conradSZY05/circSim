#include "Connection.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "colors.cpp"


Connection::Connection(int one, int two)
{
    this->conone = one;
    this->contwo = two;
}
Connection::Connection(int one)
{
    this->conone = one;
    this->contwo = -1;
}
Connection::Connection()
{
    this->conone = -1;
    this->contwo = -1;
}
void Connection::drawToMouse(sf::RenderWindow& window, sf::Vector2f mousePos)
{
    sf::VertexArray lineToMouse;
    lineToMouse[0].position = connectionPoints[connectionPoints.size()-1];
    lineToMouse[0].color = Red;
    lineToMouse[1].position = mousePos;
    lineToMouse[1].color = Red;

    window.draw(lineToMouse);
}
void Connection::addNewPoint(sf::Vector2f newPoint)
{
    connectionPoints.push_back(newPoint);
}
void Connection::draw(sf::RenderWindow& window, std::vector<std::unique_ptr<Component>>& components)
{
    int count = 0;
    sf::VertexArray line;
    for(auto& pos : connectionPoints) {
        line[count].position = pos;
        line[count].color = current != 0 ? Green : Red;
        count++;
    }

    window.draw(line);
}
void Connection::update(std::vector<std::unique_ptr<Component>>& components, sf::Vector2f mousePos)
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
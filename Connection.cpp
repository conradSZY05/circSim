#include "Connection.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

#include "colors.cpp"


// ISSUE HERE IS THAT NOT ALL BUTTONS ARE CENTERED AT THE NEAREST TENTH, SO NEED TO USE RADIUS HERE TO FIX THE MOUSE SNAPPING
sf::Vector2f roundToNearestTenth(sf::Vector2f pos) { return sf::Vector2f{  
                                                            10.f * std::round(pos.x / 10.f),
                                                            10.f * std::round(pos.y / 10.f)}; }

Connection::Connection(int one, int two) 
: resistance(0.f),
current(0.f)
{
    this->conone = one;
    this->contwo = two;
    connectionPoints.clear();
}
void Connection::drawToMouse(sf::Vector2f mousePos)
{
    connectionPoints[connectionPoints.size() - 1] = roundToNearestTenth(mousePos);
}
void Connection::addNewPoint(sf::Vector2f newPoint)
{
    connectionPoints.push_back(roundToNearestTenth(newPoint));
}
void Connection::draw(sf::RenderWindow& window)
{
    sf::VertexArray line(sf::Lines, connectionPoints.size());
    for(size_t i = 0; i < connectionPoints.size(); ++i) {
        line[i].position = roundToNearestTenth(connectionPoints[i]);
        line[i].color = Red;
    }
    window.draw(line);
}
void Connection::update(std::vector<std::unique_ptr<Component>>& components)
{
    sf::Vector2f point1, point2;
    for(auto& cmp : components) {
        for(auto& btn : cmp->getButtons()) {
            int indexToUpdate = -1;
            if(btn->getID() == conone)
                indexToUpdate = 0;
            else if(btn->getID() == contwo)
                indexToUpdate = connectionPoints.size() - 1;



            if(indexToUpdate != -1)
                connectionPoints[indexToUpdate] = btn->getPosition();
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
void Connection::reset()
{
    this->isValid = false;
    this->connectionPoints.clear();
    this->conone = -1;
    this->contwo = -1;
    this->current = 0.f;
    this->resistance = 0.f;
}
void Connection::setIsValid(bool valid) { isValid = valid; }
bool Connection::getIsValid() { return isValid; }
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
Connection::Connection(int one)
{
    this->conone = one;
    this->contwo = -1;
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
void Connection::update(std::vector<std::unique_ptr<Component>>& components)
{
    sf::Vector2f point1, point2;
    for(auto& cmp : components) {
        
    }
}
bool Connection::isPending() { return contwo == -1; }
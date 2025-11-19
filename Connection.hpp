#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "components/Component.hpp"

class Connection 
{ // REMEMBER PASS COMPONENTS AS REFERENCE TO CLASS FUNC
    public:
        Connection(int one, int two);
        Connection(int one);
        void draw(sf::RenderWindow& window, std::vector<std::unique_ptr<Component>>& components); 
        void update(std::vector<std::unique_ptr<Component>>& components);
        bool isPending();

    private:
        std::vector<sf::Vector2f> connectionPoints;
        int conone;
        int contwo;
        float current;
        float resistance; // ?? not sure about this, maybe have each connection have its own predetermined resistance i think it might make calculating currents easier
};
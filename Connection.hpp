#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "components/Component.hpp"

class Connection 
{ // REMEMBER PASS COMPONENTS AS REFERENCE TO CLASS FUNC
    public:
        Connection(int one, int two);
        void draw(sf::RenderWindow& window); 
        void update(std::vector<std::unique_ptr<Component>>& components);
        void addNewPoint(sf::Vector2f newPoint);
        void drawToMouse(sf::Vector2f mousePos);
        bool isPending();
        int getConOne();
        int getConTwo();
        void setConnectionIDs(int one, int two);
        void reset();
        void setIsValid(bool valid);
        bool getIsValid();

    private:
        bool isValid;
        std::vector<sf::Vector2f> connectionPoints;
        int conone;
        int contwo;
        float current;
        float resistance; // ?? not sure about this, maybe have each connection have its own predetermined resistance i think it might make calculating currents easier
};
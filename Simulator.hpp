#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <memory>
#include <vector>
#include "Connection.hpp"
#include "components/Button.hpp"
#include "components/Component.hpp"


class DropdownMenu;

class Simulator
{
    public:
        Simulator();
        ~Simulator();
        void run();
        void add(std::unique_ptr<Component>);

    private:
        void processEvents(); //handle sfml inputs
        void update(); //update simulation logic
        void render(); //draw everything

        //event handling
        void handleMouseInput(sf::Event event, sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed);
        void handleKeyboardInput(sf::Keyboard::Key key, bool pressed); 

        void openNewMenu(sf::Vector2f mousePos);

        void drawConnectionToMouse(sf::Vector2f mousePos);

    private:
        bool gridSnapping;

        bool makingConnection;
        bool isMoving;
        sf::RenderWindow mWindow;
        sf::View view;

        float currentZoom;
        bool draggingWindow;
        sf::Vector2i lastPixelPos;

        std::vector<std::unique_ptr<Component>> components;
        std::unique_ptr<DropdownMenu> activeMenu;
        Component* selectedComponent = nullptr; //dragging and dropping and selecting stuff
        
        Connection pendingConnection;
        std::vector<std::unique_ptr<Connection>> connections;
};
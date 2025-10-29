#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "components/Component.hpp"
#include "components/DropdownMenu.hpp"

class Simulator
{
    public:
        Simulator();
        void run();
        void add(std::unique_ptr<Component>);

    private:
        void processEvents(); //handle sfml inputs
        void update(); //update simulation logic
        void render(); //draw everything

        //event handling
        void handleMouseInput(sf::Event event, sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed);
        void handleKeyboardInput(sf::Keyboard::Key key, bool pressed); 

    private:
        bool gridSnapping;
        bool isMoving;
        sf::RenderWindow mWindow;
        sf::View view;

        float currentZoom;
        bool draggingWindow;
        sf::Vector2i lastPixelPos;

        std::vector<std::unique_ptr<Component>> components;
        std::vector<std::unique_ptr<DropdownMenu>> activeMenus;
        Component* selectedComponent = nullptr; //dragging and dropping and selecting stuff
};
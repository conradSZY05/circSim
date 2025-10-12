#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Component.hpp"

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
        void handleMouseInput(sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed);
        void handleKeyboardInput(sf::Keyboard::Key key, bool pressed); 

    private:
        sf::RenderWindow mWindow;
        std::vector<std::unique_ptr<Component>> components;
        Component* selectedComponent = nullptr; //dragging and dropping and selecting stuff
};
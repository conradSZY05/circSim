#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Button.hpp"

class MenuItem;

class DropdownMenu 
{
    public:
        DropdownMenu();
        void draw(sf::RenderWindow &window);
        void getSelection();

    private:
        std::vector<std::unique_ptr<MenuItem>> buttons;
        
};

class MenuItem 
{
    public:
        MenuItem();
        TextButton button;
        DropdownMenu* subMenu;

};
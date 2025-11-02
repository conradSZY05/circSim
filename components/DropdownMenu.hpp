#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "Button.hpp"

class MenuItem;

class DropdownMenu 
{
    public:
        DropdownMenu(sf::Vector2f mousePos, int size);
        ~DropdownMenu() = default;

        void draw(sf::RenderWindow &window);
        void getSelection();
        void addNewButton(MenuItem menuItem);
        void update(std::vector<std::unique_ptr<DropdownMenu>>& activeMenus, sf::RenderWindow& window, sf::Event& event);
        void close();
        sf::RectangleShape getContainer();

    private:
        bool wantsToClose() const;

    private:
        std::vector<std::unique_ptr<MenuItem>> buttons;
        sf::Vector2f position;
        sf::RectangleShape container;
        bool isVisible;
        float width, height;
};

class MenuItem 
{
    public:
        MenuItem(sf::Vector2f parentPosition, sf::Vector2f position, std::string text, int ind, float xSze, float ySze);
        TextButton textButton;
        DropdownMenu* subMenu;

};
#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <list>
#include <memory>
#include "Button.hpp"

class Simulator;

class MenuItem;

class DropdownMenu 
{
    public:
        using CallbackMap = std::unordered_map<std::string, std::function<void()>>;

        DropdownMenu(Simulator& simulator, 
                    sf::Vector2f mousePos, 
                    const std::vector<std::string>& menuItems,
                    const CallbackMap& callbacks);
        ~DropdownMenu() = default;

        void draw(sf::RenderWindow &window);
        void getSelection();
        void addNewButton(MenuItem menuItem);
        void update(sf::RenderWindow& window, sf::Event& event);
        void close();
        bool containsMouse(sf::Vector2f mousePos);
        bool wantsToClose() const;

    private:
        std::vector<std::unique_ptr<MenuItem>> buttons;
        sf::Vector2f position;
        sf::RectangleShape container;
        bool isVisible;
        float width, height;
        std::unique_ptr<DropdownMenu> activeSubMenu; // points to submenu in MenuItem or nullptr
};

class MenuItem 
{
    public:
        MenuItem(sf::Vector2f parentPosition, sf::Vector2f position, std::string text, int ind, float xSze, float ySze);
        TextButton textButton;
        DropdownMenu* subMenu;
};
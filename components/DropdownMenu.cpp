#include "DropdownMenu.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "AndGate.hpp"
#include "../colors.cpp"
#include "../Simulator.hpp"


DropdownMenu::DropdownMenu(Simulator& simulator, 
                        sf::Vector2f mousePos, 
                        const std::vector<std::string>& menuItems,
                        const CallbackMap& callbacks)
: position(mousePos),
isVisible(true),
width(152.f),
height(22.f * menuItems.size() + 2.f)
{
    this->container.setSize(sf::Vector2f{ width, height });

    this->container.setPosition(mousePos);
    this->container.setFillColor(LightGray);

    for(size_t i = 0; i < menuItems.size(); i++) {
        sf::Vector2f menuPosition{};
        if(i == 0)
            menuPosition = sf::Vector2f{ 1.f, 2.f };
        else
            menuPosition = sf::Vector2f{ 1.f, 2.f + i*2.f+i*20.f };

        auto item = std::make_unique<MenuItem>(position, menuPosition, menuItems[i], static_cast<int>(i), width-2.f, 20.f);
    
        if(auto it = callbacks.find(menuItems[i]); it != callbacks.end()) 
        {
            item->textButton.setCallback([this, func = it->second]() {
                func();
                this->close();
            });
        }
        buttons.push_back(std::move(item));
    }
}
bool DropdownMenu::wantsToClose() const
{
    return !isVisible;
}
void DropdownMenu::draw(sf::RenderWindow& window)
{
    window.draw(this->container);
    for(auto& tb : buttons) {
        tb->textButton.draw(window);
    }
}
void DropdownMenu::update(sf::RenderWindow& window, sf::Event& event)
{
    for(auto& b : buttons) {
        b->textButton.getButtonStatus(window, event); 
    }
}
void DropdownMenu::close() { isVisible = false; }
bool DropdownMenu::containsMouse(sf::Vector2f mousePos)
{
    return container.getGlobalBounds().contains(mousePos)
            || (activeSubMenu && activeSubMenu->containsMouse(mousePos));
}


MenuItem::MenuItem(sf::Vector2f parentPosition, sf::Vector2f position, std::string text, int ind, float xSze, float ySze)
: textButton(parentPosition, position, text, ind, xSze, ySze)
{

}

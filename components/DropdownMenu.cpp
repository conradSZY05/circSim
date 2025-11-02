#include "DropdownMenu.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "../colors.cpp"


DropdownMenu::DropdownMenu(sf::Vector2f mousePos, int size)
: position(mousePos),
isVisible(true),
width(102.f),
height(22.f * size + 2.f)
{
    this->container.setSize(sf::Vector2f{ width, height });

    this->container.setPosition(mousePos);
    this->container.setFillColor(LightGray);

    for(int i = 0; i < size; i++)
    {
        sf::Vector2f menuPosition{};
        if(i == 0)
            menuPosition = sf::Vector2f{ 1.f, 2.f };
        else
            menuPosition = sf::Vector2f{ 1.f, 2.f + i*2.f+i*20.f };
        // should probably take a vector of strings as a parameter here to set the text
        buttons.push_back(std::make_unique<MenuItem>(position, menuPosition, " ", i, width - 2.f, 20.f));
    }
}
sf::RectangleShape DropdownMenu::getContainer() { return container; }
bool DropdownMenu::wantsToClose() const
{
    return !isVisible;
}
void DropdownMenu::addNewButton(MenuItem menuItem)
{

}
void DropdownMenu::draw(sf::RenderWindow& window)
{
    window.draw(this->container);
    for(auto& tb : buttons)
    {
        tb->textButton.draw(window);
    }
}
void DropdownMenu::update(std::vector<std::unique_ptr<DropdownMenu>>& activeMenus, sf::RenderWindow& window, sf::Event& event)
{
    for(auto& b : buttons)
    {
        b->textButton.getButtonStatus(window, event);
    }
    
    activeMenus.erase(std::remove_if(activeMenus.begin(), activeMenus.end(),
                            [](auto& m){ return m->wantsToClose(); }),
                        activeMenus.end());
}
void DropdownMenu::close() { isVisible = false; }


MenuItem::MenuItem(sf::Vector2f parentPosition, sf::Vector2f position, std::string text, int ind, float xSze, float ySze)
: textButton(parentPosition, position, text, ind, xSze, ySze)
{

}
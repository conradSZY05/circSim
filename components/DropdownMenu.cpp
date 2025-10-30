#include "DropdownMenu.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>


DropdownMenu::DropdownMenu(sf::Vector2f mousePos, int size)
: position(mousePos),
isVisible(true)
{
    float xSize = 50.f * size;
    float ySize = 20.f * size;
    this->container.setSize(sf::Vector2f{ xSize, ySize });

    this->container.setPosition(mousePos);
    this->container.setFillColor(sf::Color::Yellow);
    this->container.setOutlineColor(sf::Color::Black);
    this->container.setOutlineThickness(2.f);

    for(int i = 0; i < size; i++)
    {
        sf::Vector2f menuPosition{ 0.f, i*20.f};
        // should probably take a vector of strings as a parameter here to set the text
        buttons.push_back(std::make_unique<MenuItem>(position, menuPosition, " ", i, xSize, ySize));
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
void DropdownMenu::update(std::vector<std::unique_ptr<DropdownMenu>>& activeMenus)
{
    activeMenus.erase(std::remove_if(activeMenus.begin(), activeMenus.end(),
                            [](auto& m){ return m->wantsToClose(); }),
                        activeMenus.end());
}
void DropdownMenu::close() { isVisible = false; }


MenuItem::MenuItem(sf::Vector2f parentPosition, sf::Vector2f position, std::string text, int ind, float xSze, float ySze)
: textButton(parentPosition, position, text, ind, xSze, ySze)
{

}
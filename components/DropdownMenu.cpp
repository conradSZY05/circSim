#include "DropdownMenu.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


DropdownMenu::DropdownMenu(sf::Vector2f mousePos, int size)
: position(mousePos),
isVisible(true)
{
    float xSize = 20.f * size;
    float ySize = 50.f * size;
    this->container.setSize(sf::Vector2f{ xSize, ySize });

    this->container.setPosition(mousePos);
    this->container.setFillColor(sf::Color::Yellow);
    this->container.setOutlineColor(sf::Color::Black);
    this->container.setOutlineThickness(2.f);

    
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
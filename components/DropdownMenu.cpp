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


DropdownMenu::DropdownMenu(Simulator& simulator, sf::Vector2f mousePos, int size, std::vector<std::string> menuItems)
: position(mousePos),
isVisible(true),
width(152.f),
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

        auto item = std::make_unique<MenuItem>(position, menuPosition, menuItems[i], i, width-2.f, 20.f);
    
        if(menuItems[i] == "AND")
            item->textButton.setCallback([&simulator, this]() { simulator.add(std::make_unique<AndGate>(position));
                                                                            this->close(); });

        buttons.push_back(std::move(item));
    }
}
sf::RectangleShape DropdownMenu::getContainer() { return container; }
bool DropdownMenu::wantsToClose() const
{
    return !isVisible;
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

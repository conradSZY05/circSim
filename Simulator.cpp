#include "Simulator.hpp"
#include <SFML/Graphics.hpp>

#include "components/AndGate.hpp"
#include "components/Component.hpp"


Simulator::Simulator() //initialise a simulator window
: mWindow(sf::VideoMode(1920,1080), "circSim")
{
    mWindow.clear();

}
void Simulator::run() //processEvents() handles user input
{
    while(mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}
void Simulator::processEvents()
{
    sf::Event event;
    //initialise mousePos because processEvents() gets called every time something happens with mouse or keyboard
    sf::Vector2f mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::MouseMoved:
                /*mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                std::cout << mousePos.x << ", " << mousePos.y << "\n";*/
                break;
            case sf::Event::MouseButtonPressed:
                //std::cout << mousePos.x << ", " << mousePos.y << "\n";
                handleMouseInput(event.mouseButton.button, mousePos, true);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, mousePos, false);
                break;

            case sf::Event::Resized:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::TextEntered:
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
            case sf::Event::Count:
              break;
            }
    }
}
void Simulator::update()
{
    //mWindow.display(); only display once something changed
}
void Simulator::render()
{
    sf::Color color(129, 129, 129);
    mWindow.clear(color);
    for(auto& c : components) //maybe make it so it draws components that have experienced change
    {
        mWindow.draw(c->getComponent());
    }
    mWindow.display();
}
void Simulator::handleMouseInput(sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed)
{
    if(pressed)
    {
        //must be trying to interact with an object
        if(button == sf::Mouse::Left)
        {
            //check mousepos, is mouse over object?
            // at this point loop through objects added and check each individually
            /*if(test.getGlobalBounds().contains(mousePos))
            {
                //moving test

            }*/
        }
        else if(button == sf::Mouse::Right) 
        {
            //open dropdown but for now just add a new test entity
            // should be added in Simulation class with component passed
            add(std::make_unique<AndGate>(mousePos));

        }
    }
    else 
    {
        //stop interacting with object
    }
    if(button == sf::Mouse::Left) //pressing on something
    {
        //
    }
}
void Simulator::add(std::unique_ptr<Component> component)
{
    // add component to binary search tree and to grid
    //changeComponentPosition(component, mousePos);
    components.push_back(std::move(component));
}
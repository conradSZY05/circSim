#include "Simulator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

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
        render();
        update();
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
                handleMouseInput(event, event.mouseButton.button, mousePos, false);
                break;
            case sf::Event::MouseButtonPressed:
                //std::cout << mousePos.x << ", " << mousePos.y << "\n";
                handleMouseInput(event, event.mouseButton.button, mousePos, true);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseInput(event, event.mouseButton.button, mousePos, false);
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
    mWindow.display();
}
void Simulator::render()
{
    sf::Color color(129, 129, 129);
    mWindow.clear(color);
    for(auto& c : components) //maybe make it so it draws components that have experienced change
        c->draw(mWindow);
    //mWindow.draw(c->getComponent());
}
void Simulator::handleMouseInput(sf::Event event, sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed)
{
    if(pressed)
    {
        //must be trying to interact with an object
        if(button == sf::Mouse::Left)
        {  
            for(auto& c : components)
            {
                // check if mouse is over component
                if(c->getComponent().getGlobalBounds().contains(mousePos))
                {
                    c->setMouseClickedOffset(mousePos);
                    c->setMoving(true);
                }
            }
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
        if(button == sf::Mouse::Left)
        {
            // check if dropping
            for(auto& c : components)
            {
                if(c->getComponent().getGlobalBounds().contains(mousePos))
                {
                    c->setMoving(false);
                }
            }
        }
        // mouse move? then maybe move component or do button stuff
        for(auto& c : components)
        {
            c->handleMouseEvent(mWindow, event, mousePos);
        }
        
        //stop interacting with object
    }
}
void Simulator::add(std::unique_ptr<Component> component)
{
    // add component to binary search tree and to grid
    //changeComponentPosition(component, mousePos);
    components.push_back(std::move(component));
}
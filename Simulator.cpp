#include "Simulator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

#include "colors.cpp"
#include "components/Component.hpp"
#include "components/DropdownMenu.hpp"


Simulator::Simulator() //initialise a simulator window
: gridSnapping(true), // for now just test this as true 
view(),
currentZoom(1.f),
draggingWindow(false),
lastPixelPos()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // necessary to prevent distortion on zooming out

    mWindow.create(sf::VideoMode(1920, 1080), "circSim", sf::Style::Default, settings);
    mWindow.clear();
    view.setCenter({1920.f/2.f, 1080.f/2.f });
    view.setSize({1920.f, 1080.f });
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
                handleMouseInput(event, event.mouseButton.button, mousePos, false);
                break;
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
    sf::Color color(Teal);
    mWindow.clear(color);
    for(auto& c : components) //maybe make it so it draws components that have experienced change
        c->draw(mWindow);
    for(auto& menu : activeMenus)
    {
        menu->draw(mWindow);
    }
}
void Simulator::handleMouseInput(sf::Event event, sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);

    bool draggingComponent = false;
    if(pressed)
    {
        for(auto& menu : activeMenus)
        {
            // once add submenus need to check them here
            if(!menu->getContainer().getGlobalBounds().contains(mousePos))
                menu->close();
        }
        
        
        //must be trying to interact with an object
        if(button == sf::Mouse::Left)
        {  
            for(auto& c : components)
            {
                // check if mouse is over component
                if(c->getComponent().getGlobalBounds().contains(mousePos) && !c->interactingWithButton())
                {
                    c->setMouseClickedOffset(mousePos);
                    c->setMoving(true);
                    draggingComponent = true;
                    break;
                }
            }

            if(!draggingComponent)
            {
                draggingWindow = true;
                lastPixelPos = pixelPos;
            }
        }
        else if(button == sf::Mouse::Right) 
        {
            // open dropdown

            activeMenus.push_back(std::make_unique<DropdownMenu>(mousePos, 6));
            //add(std::make_unique<AndGate>(mousePos));

        }
    }
    else 
    {
        if(event.type == sf::Event::MouseWheelScrolled)
        {
            float zoomFactor = 1.f + (-event.mouseWheelScroll.delta * 0.1f);
            float newZoom = currentZoom * zoomFactor;

            if(newZoom > 0.2f && newZoom < 5.f)
            {
                currentZoom = newZoom;
                
                sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
                sf::Vector2f beforeZoomPos = mWindow.mapPixelToCoords(pixelPos, view);
                view.zoom(zoomFactor);
                sf::Vector2f afterZoomPos = mWindow.mapPixelToCoords(pixelPos, view);
                sf::Vector2f offset = beforeZoomPos - afterZoomPos;
            
                view.move(offset);
                mWindow.setView(view);
            }
        }
        if(button == sf::Mouse::Left)
        {
            draggingWindow = false;
            // check if dropping
            for(auto& c : components)
            {
                if(c->getComponent().getGlobalBounds().contains(mousePos))
                {
                    c->setMoving(false);
                }
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {
            //dragging the view
            if(draggingWindow)
            {
                sf::Vector2i currentPixel = pixelPos;
                sf::Vector2i pixelDelta = lastPixelPos - currentPixel;

                view.move(
                    static_cast<float>(pixelDelta.x) * currentZoom,
                    static_cast<float>(pixelDelta.y) * currentZoom
                );

                mWindow.setView(view);
                lastPixelPos = currentPixel;
            }

            // mouse move? then maybe move component or do button stuff
            for(auto& c : components)
            {
                c->handleMouseEvent(mWindow, event, mousePos, gridSnapping);
            }
        }
    
    }
    for(auto& menu : activeMenus)
    {
        menu->update(activeMenus, mWindow, event);
    }
}
void Simulator::add(std::unique_ptr<Component> component)
{
    // add component to binary search tree and to grid
    //changeComponentPosition(component, mousePos);
    components.push_back(std::move(component));
}
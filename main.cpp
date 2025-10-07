#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

class Component
{
    public:
        Component(sf::Vector2f mousePos); //mousePos is initial setpos location
        void changePosition(sf::Vector2f mousePos);
        sf::CircleShape getComponent(); //change return type here
        sf::Vector2f getPos(); // return position of component relative to map relative to window relative to screen

    private:
        sf::CircleShape setType(sf::Vector2f mousePos); //take dropdown string as parameter here


    private:
        float xPos;
        float yPos;
        sf::CircleShape type;
};
class Simulator
{
    public:
        Simulator();
        void run();
        void add(Component component, sf::Vector2f mousePos);

    private:
        void processEvents();
        void update();
        void render();
        void handleMouseInput(sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed);
        void changeComponentPosition(Component component, sf::Vector2f mousePos);

    private:
        sf::RenderWindow mWindow;
        //binary search tree of all circuit elements
        //for now just use a test class
        Component test;


};

int main()
{
    Simulator simulator;
    simulator.run();


    return 0;
}

Component::Component(sf::Vector2f mousePos)
:xPos(),
yPos(),
type()
{
    // initialise
    type = setType(mousePos); //pass initial paramters to where shape initialised
    

}
void Component::changePosition(sf::Vector2f mousePos) 
{
    //get mouse delta and add to xpos and ypos
    xPos = mousePos.x;
    yPos = mousePos.y;

    
}
sf::CircleShape Component::setType(sf::Vector2f mousePos) //should return a vertex array but for now just a circleshape
{
    //std::cout << mousePos.x << ", " << mousePos.y << "\n";
    //should take dropdown menu as paramater here but for now just add a circle
    sf::CircleShape shape(50.f);
    shape.setPosition(mousePos);
    shape.setFillColor(sf::Color::Yellow);
    return shape;
}
sf::CircleShape Component::getComponent()
{
    return type;
}


Simulator::Simulator() //initialise a simulator window
: mWindow(sf::VideoMode(960,540), "circSim"),
test({0.f, 0.f})
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
    //FIX: mWindow.clear() refreashing entities every frame
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
            Component component = Component(mousePos);
            add(component, mousePos);

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
void Simulator::changeComponentPosition(Component component, sf::Vector2f mousePos)
{
    //change xpos ypos in component, update through class

    component.changePosition(mousePos);
}
void Simulator::add(Component component, sf::Vector2f mousePos)
{
    // add component to binary search tree and to grid
    //changeComponentPosition(component, mousePos);
    mWindow.draw(component.getComponent());
    mWindow.display();
}
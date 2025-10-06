#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

class Component
{
    public:
        Component();
        void changePosition();
        void getType(); // maybe store type as string
        sf::Vector2f getPos(); // return position of component relative to map relative to window relative to screen

    private:
        void setType(); //take dropdown string as parameter here


    private:
        float xPos;
        float yPos;
        std::string type;
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

Component::Component()
:xPos(),
yPos()
{
    // initialise
    setType();
    

}
void Component::changePosition() 
{
    //get mouse delta and add to xpos and ypos
    setType();
    
}
void Component::setType()
{
    //should take dropdown menu as paramater here but for now just add a circle
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Yellow);
}


Simulator::Simulator() //initialise a simulator window
: mWindow(sf::VideoMode(960,540), "circSim")
{
    

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
    sf::Vector2f mousePos;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::MouseMoved:
                mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, mousePos, true);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, mousePos, false);
                break;

        }
    }
}
void Simulator::update()
{

}
void Simulator::render()
{
    mWindow.clear();
    
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
            Component component = Component();
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
    
}
void Simulator::add(Component component, sf::Vector2f mousePos)
{
    // add component to binary search tree and to grid
    changeComponentPosition(component, mousePos);

}
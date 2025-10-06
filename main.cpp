#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

class Element
{
    public:
        Element();
        void changePosition();

    private:
        void setType();

    private:
        float xPos;
        float yPos;
};
class Simulator
{
    public:
        Simulator();
        void run();

    private:
        void processEvents();
        void update();
        void render();
        void handleMouseInput(sf::Mouse::Button button, sf::Vector2f mousePos, bool pressed);

    private:
        sf::RenderWindow mWindow;
        //binary search tree of all circuit elements
        //for now just use a test class
        //Element test;


};

int main()
{
    Simulator simulator;
    simulator.run();


    return 0;
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
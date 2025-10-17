#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Button 
{
    public:
        Button() : state(false) {}
        bool setState();

    private:
        bool state; //clicked or not clicked
};

class InputButton : Button 
{

};

class OutputButton : Button
{

}; 
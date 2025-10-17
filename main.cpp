#include <SFML/Graphics.hpp>
#include <iostream>

//class headers
#include "components/Component.hpp"
#include "Simulator.hpp"
#include "ResourceManager.hpp"




int main()
{
    ResourceManager::preLoadTextures("./models");

    Simulator simulator;
    simulator.run();

    ResourceManager::clearTextures();
    return 0;
}

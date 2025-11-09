#include <SFML/Graphics.hpp>
#include <iostream>

//class headers
#include "components/Component.hpp"
#include "Simulator.hpp"
#include "ResourceManager.hpp"




int main()
{
    ResourceManager::preLoadTextures("./models/Textures");
    ResourceManager::preLoadFonts("./models/Fonts");

    Simulator simulator;
    simulator.run();

    ResourceManager::clearTextures();
    ResourceManager::clearFonts();
    return 0;
}

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

class ResourceManager
{
    private:
        static std::map<std::string, sf::Texture*> textureMap;

    public:
        static sf::Texture* getTexture(const std::string filePath);
        static void preLoadTextures(const std::string folderPath, bool recurse = true);
        static void clearTextures();

};

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

class ResourceManager
{
    private:
        static std::map<std::string, sf::Texture*> textureMap;
        static std::map<std::string, sf::Font*> fontMap;

    public:
        static sf::Texture* getTexture(const std::string filePath);
        static void preLoadTextures(const std::string folderPath, bool recurse = true);
        static void clearTextures();

        static sf::Font* getFont(const std::string filePath);
        static void preLoadFonts(const std::string folderPath, bool rescurse = true);
        static void clearFonts();

};

#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <map>
#include <sstream>


//initialise texture map as empty
std::map<std::string, sf::Texture*> ResourceManager::textureMap;


sf::Texture* ResourceManager::getTexture(const std::string filePath) {
    //search to see if theres already an entry
    for(auto element: textureMap) {
        if(element.first == filePath)
            return element.second;
    }

    //making it to this point means no matching entry in map, so make a new one
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(filePath);

    textureMap[filePath] = texture;
    return textureMap[filePath];
}

void ResourceManager::preLoadTextures(const std::string folderPath, bool recurse) {
    //iterate through every file in the folder
    //both loops are the same, the first just will have more files to process
    if(recurse) {
        for(auto& file: std::filesystem::recursive_directory_iterator(folderPath)) {
            //get path as a string here
            std::stringstream ss;
            ss << file;

            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
            textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
        }
    } else {
        for(auto& file: std::filesystem::directory_iterator(folderPath)) {
            std::stringstream ss;
            ss << file;

            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
            textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
        }
    }
}

void ResourceManager::clearTextures() {
    //delete all of the pointers
    for(auto element: textureMap) {
        delete element.second;
    }
    
    //clear all entries
    textureMap.clear();
}
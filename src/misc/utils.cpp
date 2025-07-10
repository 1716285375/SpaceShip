#include "utils.h"

#include <iostream>
#include <fstream>

SDL_Point renderTextCenter(const std::string &text, int x, int y, int fontSize, SDL_Color color)
{
    return SDL_Point();
}

void renderText(const std::string &text, int x, int y, int fontSize, SDL_Color color)
{
}

void renderTextRight(const std::string &text, int x, int y, int fontSize, SDL_Color color)
{
    
}

std::vector<std::string> readTagsFromFile(const std::string &fileName)
{
    std::vector<std::string> tags;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return tags;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            tags.push_back(line);
        }   
    }
    file.close();
    return tags;
}

#include "utils.h"

#include <iostream>
#include <fstream>

SDL_Rect renderTextCenter(SDL_Renderer* renderer, TTF_Font* font, const std::string &text, int x, int y, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {
        (x - surface->w) / 2,
        y,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return dstRect;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int w, int h, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {
        x,
        y,
        w,
        h
    };

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

void renderTextRight(const std::string &text, int x, int y, int fontSize, SDL_Color color)
{
    
}

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int width, int height, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    // SDL_RenderCopy
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
            // std::cout << "push tag: " << line << std::endl;
            tags.push_back(line);
        }   
    }
    file.close();
    return tags;
}

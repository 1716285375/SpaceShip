#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>

SDL_Rect renderTextCenter(SDL_Renderer* renderer, TTF_Font* font, const std::string &text, int x, int y, SDL_Color color);
void renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color);
void renderTextRight(const std::string& text, int x, int y, int fontSize, SDL_Color color);

std::vector<std::string> readTagsFromFile(const std::string& fileName);
#endif // UTIL_H
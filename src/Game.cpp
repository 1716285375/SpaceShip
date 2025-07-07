#include "Game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>



void Game::addToScoreBoard(int score, const std::string &name)
{
    scoreBoard.insert({std::make_pair(score, name)});
    if (scoreBoard.size() > 8)
    {
        scoreBoard.erase(--scoreBoard.end());
    }
}

void Game::saveData()
{
    // 保存得分的文件
    std::ofstream file("../../data/score.dat");
    if (!file.is_open())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to open file! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    for (const auto &item : scoreBoard)
    {
        file << item.first << " " << item.second << std::endl;
    }
}

void Game::loadData()
{
    // 加载得分的文件
    std::ifstream file("../../data/score.dat");
    if (!file.is_open())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to open file! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    scoreBoard.clear();
    int score;
    std::string name;
    while (file >> score >> name)
    {
        addToScoreBoard(score, name);
    }
}

Game::Game()
{
    
}

Game::~Game()
{
    saveData(); // 保存得分数据
    clean();
}


void Game::init()
{
    frameTime = 1000 / 60; // 16.66ms/帧
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建窗口
    window = SDL_CreateWindow("Space Shoot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    // 初始化SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 初始化SDL_ttf
    if (TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_ttf could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 初始化SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    // 打开音频设备
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not open audio! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    Mix_AllocateChannels(32); // 设置最大音频通道数
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 8);

    // 初始化背景
    nearStars.texture = IMG_LoadTexture(renderer, "../../assets/image/Stars-A.png");
    if (nearStars.texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    SDL_QueryTexture(nearStars.texture, NULL, NULL, &nearStars.width, &nearStars.height);
    nearStars.width /= 4;
    nearStars.height /= 4;
    
    farStars.texture = IMG_LoadTexture(renderer, "../../assets/image/Stars-B.png");
    SDL_QueryTexture(farStars.texture, NULL, NULL, &farStars.width, &farStars.height);
    if (farStars.texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    farStars.speed = 20;
    farStars.width /= 4;
    farStars.height /= 4;

    // 初始化字体
    titleFont = TTF_OpenFont("../../assets/font/VonwaonBitmap-16px.ttf", 32);
    textFont = TTF_OpenFont("../../assets/font/VonwaonBitmap-16px.ttf", 32);
    if (textFont == nullptr || titleFont == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    // 加载数据
    loadData(); // 加载得分数据

    // 切换到主场景
    currentScene = new SceneTitle();
    currentScene->init();
}


void Game::run()
{
    while (isRunning)
    {
        auto frameStart = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        SDL_Event event;
        handleEvent(&event);

        update(deltaTime);

        render();
        auto frameEnd = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        auto diff = frameEnd - frameStart; // 计算两次时刻间隔
        if (diff < frameTime)
        {
            SDL_Delay(frameTime - diff);
            deltaTime = frameTime / 1000.0f;
        }
        else
        {
            deltaTime = diff / 1000.0f;
        }
    }
}

void Game::clean()
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    if (nearStars.texture != nullptr)
    {
        SDL_DestroyTexture(nearStars.texture);
    }
    if (farStars.texture != nullptr)
    {
        SDL_DestroyTexture(farStars.texture);
    }
    if (titleFont != nullptr)
    {
        TTF_CloseFont(titleFont);
    }
    if (textFont != nullptr)
    {
        TTF_CloseFont(textFont);
    }

    // 清理SDL_image
    IMG_Quit();
    // 清理SDL_ttf
    TTF_Quit();
    // 清理SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
    // 清理SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::changeScene(Scene *scene)
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}


void Game::handleEvent(SDL_Event* event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            isRunning = false;
        }
        currentScene->handleEvent(event);
    }
}

void Game::backgroundUpdate(float deltaTime)
{
    nearStars.offset += nearStars.speed * deltaTime;
    if (nearStars.offset >= 0)
    {
        nearStars.offset -= nearStars.height;
    }

    farStars.offset += farStars.speed * deltaTime;
    if (farStars.offset >= 0){
        farStars.offset -= farStars.height;
    }
}

void Game::renderBackground()
{
    // 渲染远处的星星
    for (int posY = static_cast<int>(farStars.offset); posY < getWindowHeight(); posY += farStars.height){
        for (int posX = 0; posX < getWindowWidth(); posX += farStars.width){
            SDL_Rect ds = {posX, posY, farStars.width, farStars.height};
            SDL_RenderCopy(renderer, farStars.texture, NULL, &ds);
        }
    }
    // 渲染近处的星星
    for (int posY = static_cast<int>(nearStars.offset); posY < getWindowHeight(); posY += nearStars.height)
    {
        for (int posX = 0; posX < getWindowWidth(); posX += nearStars.width)
        {
            SDL_Rect dstRect = {posX, posY, nearStars.width, nearStars.height};
            SDL_RenderCopy(renderer, nearStars.texture, NULL, &dstRect);
        }
        
    }
}

void Game::update(float deltaTime)
{
    backgroundUpdate(deltaTime);
    currentScene->update(deltaTime);
}
void Game::render()
{
    // 清空
    SDL_RenderClear(renderer);
    // 渲染背景
    renderBackground();
    // 渲染场景
    currentScene->render();
    // 显示渲染结果
    SDL_RenderPresent(renderer);
}

SDL_Point Game::renderTextCenter(const std::string &text, int x, int y, int fontSize, SDL_Color color, FontType fontType)
{
    TTF_Font* font;
    switch (fontType)
    {
    case FontType::Silver:
        font = TTF_OpenFont("../../assets/font/Silver.ttf", fontSize);
        break;
    case FontType::Vonwaon:
        font = TTF_OpenFont("../../assets/font/VonwaonBitmap-16px.ttf", fontSize);
        break;
    default:
        break;
    }
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return SDL_Point{0, 0};
    }
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

    // 返回文字的右上角坐标
    return SDL_Point{
        dstRect.x + dstRect.w,
        dstRect.y
    };
}

void Game::renderText(const std::string &text, int x, int y, int fontSize, SDL_Color color, FontType fontType)
{
        TTF_Font* font;
    switch (fontType)
    {
    case FontType::Silver:
        font = TTF_OpenFont("../../assets/font/Silver.ttf", fontSize);
        break;
    case FontType::Vonwaon:
        font = TTF_OpenFont("../../assets/font/VonwaonBitmap-16px.ttf", fontSize);
        break;
    default:
        break;
    }
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {
        x,
        y,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Game::renderTextRight(const std::string &text, int x, int y, int fontSize, SDL_Color color, FontType fontType)
{
    TTF_Font* font;
    switch (fontType)
    {
    case FontType::Silver:
        font = TTF_OpenFont("../../assets/font/Silver.ttf", fontSize);
        break;
    case FontType::Vonwaon:
        font = TTF_OpenFont("../../assets/font/VonwaonBitmap-16px.ttf", fontSize);
        break;
    default:
        break;
    }
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {
        windowWidth - x - surface->w,
        y,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

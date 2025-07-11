#include "LevelScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>

LevelScene::LevelScene()
{

}

LevelScene::~LevelScene()
{
}

void LevelScene::handleInput(SDL_Event* event)
{   

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                Scene::getSceneManager().goBack();
                break;
        }
    }
}

void LevelScene::update(float deltaTime)
{

}

void LevelScene::render(SDL_Renderer* renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in LevelScene::render");
        return;
    }
    renderTextCenter(renderer, Scene::m_sceneFont_, "Level Scene", Scene::getWindowWidth(), Scene::getWindowHeight() / 2, {255, 255, 255, 255});
}

void LevelScene::onEnter()
{
    spdlog::info("Enter LevelScene");
    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
        Scene::m_sceneFont_ = font->getFont();
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }

}

void LevelScene::onExit()
{
    spdlog::info("Exit LevelScene");
}
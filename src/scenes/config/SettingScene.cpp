#include "SettingScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "utils.h"
#include <spdlog/spdlog.h>


SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::update(float deltaTime)
{
}

void SettingScene::render(SDL_Renderer *renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in SettingScene::render");
        return;
    }
    renderTextCenter(renderer, Scene::m_sceneFont_, "Setting Scene", Scene::getWindowWidth(), Scene::getWindowHeight() / 2, {255, 255, 255, 255});
}

void SettingScene::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                Scene::getSceneManager().goBack();
                break;
        }
    }
}

void SettingScene::onEnter()
{
    spdlog::info("SettingScene::onEnter");
    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
        Scene::m_sceneFont_ = font->getFont();
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }
}

void SettingScene::onExit()
{
    spdlog::info("SettingScene::onExit");
}

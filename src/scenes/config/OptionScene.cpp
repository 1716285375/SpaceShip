#include "OptionScene.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "utils.h"
#include <spdlog/spdlog.h>

OptionScene::OptionScene()
{
}

OptionScene::~OptionScene()
{
}

void OptionScene::update(float deltaTime)
{
}

void OptionScene::render(SDL_Renderer *renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in OptionScene::render");
        return;
    }
    renderTextCenter(renderer, Scene::m_sceneFont_, "Option Scene", Scene::getWindowWidth(), Scene::getWindowHeight() / 2, {255, 255, 255, 255});
}

void OptionScene::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                Scene::getSceneManager().goBack();
                break;
        }
    }
}

void OptionScene::onEnter()
{
    spdlog::info("Entering OptionScene");
    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
        Scene::m_sceneFont_ = font->getFont();
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }
}

void OptionScene::onExit()
{
    spdlog::info("Exiting OptionScene");
}

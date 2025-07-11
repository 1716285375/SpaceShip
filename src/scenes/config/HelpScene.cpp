#include "HelpScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "utils.h"
#include <spdlog/spdlog.h>
HelpScene::HelpScene()
{
}

HelpScene::~HelpScene()
{
}

void HelpScene::update(float deltaTime)
{
}

void HelpScene::render(SDL_Renderer *renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in HelpScene::render");
        return;
    }
    renderTextCenter(renderer, Scene::m_sceneFont_, "Help Scene", Scene::getWindowWidth(), Scene::getWindowHeight() / 2, {255, 255, 255, 255});
}

void HelpScene::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                Scene::getSceneManager().goBack();
                break;
        }
    }
}

void HelpScene::onEnter()
{
    spdlog::info("Entering HelpScene");
    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
        Scene::m_sceneFont_ = font->getFont();
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }
}

void HelpScene::onExit()
{
    spdlog::info("Exiting HelpScene");
}

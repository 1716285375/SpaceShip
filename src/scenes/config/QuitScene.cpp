#include "QuitScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "utils.h"
#include <spdlog/spdlog.h>


QuitScene::QuitScene()
{
}

QuitScene::~QuitScene()
{
}

void QuitScene::update(float deltaTime)
{
}

void QuitScene::render(SDL_Renderer *renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in QuitScene::render");
        return;
    }
    renderTextCenter(renderer, Scene::m_sceneFont_, "Quit Scene", Scene::getWindowWidth(), Scene::getWindowHeight() / 2, {255, 255, 255, 255});
}

void QuitScene::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                Scene::getSceneManager().goBack();
                break;
        }
    }
}

void QuitScene::onEnter()
{
    spdlog::info("QuitScene::onEnter");
    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
        Scene::m_sceneFont_ = font->getFont();
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }
}

void QuitScene::onExit()
{
    spdlog::info("QuitScene::onExit");
}

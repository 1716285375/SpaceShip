#include "SceneMain.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>



SceneMain::SceneMain() : game(Game::getInstance())
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::update(float deltaTime)
{
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
}

void SceneMain::render()
{
    // 渲染玩家
    SDL_Rect playerRect{
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        player.width,
        player.height
    };
    SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);

    // 渲染玩家子弹
    renderPlayerProjectiles();
}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::init()
{
    // 初始化玩家对象
    player.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/SpaceShip.png");
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = static_cast<float>(game.getWindowWidth()) / 2 - static_cast<float>(player.width) / 2;
    player.position.y = static_cast<float>(game.getWindowHeight()) - static_cast<float>(player.height);

    // 初始化子弹模板
    projectilePlayerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/Bullet.png");
    SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, &projectilePlayerTemplate.width, &projectilePlayerTemplate.height);
    projectilePlayerTemplate.width /= 4;
    projectilePlayerTemplate.height /= 4;

}

void SceneMain::clean()
{
    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }

    for (auto& projectile: projectilesPlayer) {
        if (projectile != nullptr)
        {
            delete projectile;
        }
    }
    projectilesPlayer.clear();

    if (projectilePlayerTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
    }
}

void SceneMain::keyboardControl(float deltaTime)
{
    auto keyboardState = SDL_GetKeyboardState(NULL);
    
    // 按键控制, WSAD控制玩家移动
    if (keyboardState[SDL_SCANCODE_W])
    {
        player.position.y -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        player.position.y += deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        player.position.x -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        player.position.x += deltaTime * player.speed;
    }
    
    // 边界检测
    if (player.position.x < 0)
    {
        player.position.x = 0;
    }
    if (player.position.x > game.getWindowWidth() - player.width)
    {
        player.position.x = game.getWindowWidth() - player.width;
    }
    if (player.position.y < 0)
    {
        player.position.y = 0;
    }
    if (player.position.y > game.getWindowHeight() - player.height)
    {
        player.position.y = game.getWindowHeight() - player.height;
    }

    // 发射子弹
    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        // TODO: 发射子弹
        auto currentTime = SDL_GetTicks();
        if (currentTime - player.lastShootTime > player.coolDown)
        {
            shootPlayer();
            player.lastShootTime = currentTime;
        }

    }
}

void SceneMain::shootPlayer()
{

    // TODO: 发射子弹
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;
    projectile->position.y = player.position.y - projectile->height;
    projectilesPlayer.push_back(projectile);
}

void SceneMain::updatePlayerProjectiles(float deltaTime)
{
    int margin = 32; // 子弹与超出屏幕外边界的距离
    for (auto it = projectilesPlayer.begin(); it != projectilesPlayer.end();)
    {
        auto projectile = *it;
        projectile->position.y -= deltaTime * projectile->speed;
        // TODO: 检查子弹是否超出屏幕
        if (projectile->position.y + margin < 0)
        {
            delete projectile;
            it = projectilesPlayer.erase(it);
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Projectile out of screen, deleted");
        }
        else
        {
            ++it;
        }
    }
}

void SceneMain::renderPlayerProjectiles()
{
    for (const auto& projectile: projectilesPlayer)
    {
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width,
            projectile->height
        };
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &projectileRect);
    }
}

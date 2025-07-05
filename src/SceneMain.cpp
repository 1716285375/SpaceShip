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
    spawnEnemy();
    updateEnemies(deltaTime);
    updateEnemyProjectiles(deltaTime);
}

void SceneMain::render()
{
    // 渲染敌人
    renderEnemies();

    // 渲染玩家残影
    int alphaStep = 255 / (player.trail.size() + 1);
    int alpha = alphaStep;
    for (const auto& pos : player.trail) {
        SDL_Rect shadowRect{
            static_cast<int>(pos.x),
            static_cast<int>(pos.y),
            player.width,
            player.height
        };
        SDL_SetTextureAlphaMod(player.texture, alpha); // 设置透明度
        SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &shadowRect);
        alpha += alphaStep;
    }
    SDL_SetTextureAlphaMod(player.texture, 255); // 恢复不透明

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
    // 渲染敌人子弹
    renderEnemyProjectiles();

}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::init()
{
    // 初始化随机数生成器
    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f);

    // 初始化玩家对象
    player.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/SpaceShip.png");
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = static_cast<float>(game.getWindowWidth()) / 2 - static_cast<float>(player.width) / 2;
    player.position.y = static_cast<float>(game.getWindowHeight()) - static_cast<float>(player.height);

    // 初始化玩家子弹模板
    projectilePlayerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/laser-3.png");
    SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, &projectilePlayerTemplate.width, &projectilePlayerTemplate.height);
    projectilePlayerTemplate.width /= 4;
    projectilePlayerTemplate.height /= 4;

    // 初始化敌人对象模板
    enemyTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/insect-1.png");
    SDL_QueryTexture(enemyTemplate.texture, NULL, NULL, &enemyTemplate.width, &enemyTemplate.height);
    enemyTemplate.width /= 4;
    enemyTemplate.height /= 4;

    // 初始化敌人子弹模板
    projectileEnemyTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/bullet-1.png");
    SDL_QueryTexture(projectileEnemyTemplate.texture, NULL, NULL, &projectileEnemyTemplate.width, &projectileEnemyTemplate.height);
    projectileEnemyTemplate.width /= 4;
    projectileEnemyTemplate.height /= 4;

}

void SceneMain::clean()
{
    // 释放玩家子弹资源
    for (auto& projectile: projectilesPlayer) {
        if (projectile != nullptr)
        {
            delete projectile;
        }
    }
    projectilesPlayer.clear();

    // 释放敌人资源
    for (auto& enemy: enemies) {
        if (enemy != nullptr)
        {
            delete enemy;
        }
    }
    enemies.clear();

    if (enemyTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(enemyTemplate.texture);
    }

    // 释放敌人子弹资源
    for (auto& projectile: projectilesEnemy) {
        if (projectile != nullptr)
        {
            delete projectile;
        }
    }

    // 清理模板
    // 释放玩家资源
    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }

    // 释放敌人资源
    if (enemyTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(enemyTemplate.texture);
    }

    // 释放玩家子弹模板资源
    if (projectilePlayerTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
    }

    // 释放敌人子弹模板资源
    if (projectileEnemyTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(projectileEnemyTemplate.texture);
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
    // 每帧更新时
    player.trail.push_back(player.position);
    // 最多保留10个历史点
    if (player.trail.size() > 10)
    { 
        player.trail.pop_front();
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
        // 检查子弹是否超出屏幕
        if (projectile->position.y + margin < 0)
        {
            delete projectile;
            it = projectilesPlayer.erase(it);
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Projectile out of screen, deleted");
        }
        else
        {
            bool hit = false;
            for (auto enemy: enemies)
            {
                SDL_Rect enemyRect = {
                    static_cast<int>(enemy->position.x),
                    static_cast<int>(enemy->position.y),
                    enemy->width,
                    enemy->height
                };

                SDL_Rect projectileRect = {
                    static_cast<int>(projectile->position.x),
                    static_cast<int>(projectile->position.y),
                    projectile->width,
                    projectile->height
                };
                if (SDL_HasIntersection(&enemyRect, &projectileRect))
                {
                    // 子弹击中敌人
                    enemy->currentHealth -= projectile->damage; // 扣除敌人的生命值
                    delete projectile;
                    it = projectilesPlayer.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit)
            {
                ++it;
            }

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

void SceneMain::spawnEnemy()
{
    if (dis(gen) > 1 / 60.0f)
    {
        return;
    }

    Enemy* enemy = new Enemy(enemyTemplate);
    enemy->position.x = dis(gen) * static_cast<float>(game.getWindowWidth() - enemy->width);
    enemy->position.y = -static_cast<float>(enemy->height);
    enemies.push_back(enemy);
}

void SceneMain::updateEnemies(float deltaTime)
{
    auto currentTime = SDL_GetTicks();
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        auto enemy = *it;
        enemy->position.y += deltaTime * enemy->speed;
        if (enemy->position.y > game.getWindowHeight())
        {
            delete enemy;
            it = enemies.erase(it);
        }
        else
        {
            int safeDistance = game.getWindowHeight() - 4 * player.height; // 敌人的安全距离(在该条件下敌机可能不会发射子弹), 距离屏幕底部4个玩家的高度
            if (enemy->position.y < player.position.y + player.height &&
                enemy->position.y < safeDistance)
            {
                // 敌人在玩家上方，发射子弹
                if (currentTime - enemy->lastShootTime > enemy->coolDown)
                {
                    shootEnemy(enemy);
                    enemy->lastShootTime = currentTime;
                }
            }
            else if (enemy->position.y > safeDistance)
            {
                // 敌人能检测到玩家(是否x轴有重叠, 且敌机在玩家上方)，发射子弹
                if (!(player.position.x + player.width < enemy->position.x ||
                    enemy->position.x + enemy->width < player.position.x) &&
                    enemy->position.y < player.position.y + player.height)
                {
                    if (currentTime - enemy->lastShootTime > enemy->coolDown)
                    {
                        shootEnemy(enemy);
                        enemy->lastShootTime = currentTime;
                    }
                }
            }

            if (enemy->currentHealth <= 0)
            {
                enemyExplode(enemy);
                it = enemies.erase(it);
            }
            else
            {
                ++it;
            }

        }
    }
}

void SceneMain::renderEnemies()
{
    for (auto enemy: enemies)
    {
        SDL_Rect enemyRect = {
            static_cast<int>(enemy->position.x),
            static_cast<int>(enemy->position.y),
            enemy->width,
            enemy->height
        };
        SDL_RenderCopy(game.getRenderer(), enemy->texture, NULL, &enemyRect);
    }
}

void SceneMain::shootEnemy(Enemy* enemy)
{
    auto projectile = new ProjectileEnemy(projectileEnemyTemplate);
    projectile->position.x = enemy->position.x + enemy->width / 2 - projectile->width / 2;
    projectile->position.y = enemy->position.y + enemy->height / 2 - projectile->height / 2;
    projectile->direction = getDirection(enemy);
    projectilesEnemy.push_back(projectile);
}

void SceneMain::updateEnemyProjectiles(float deltaTime)
{
    auto margin = 32; // 子弹与超出屏幕外边界的距离
    for (auto it = projectilesEnemy.begin(); it != projectilesEnemy.end();)
    {
        auto projectile = *it;
        projectile->position.x += projectile->speed * projectile->direction.x * deltaTime;
        projectile->position.y += projectile->speed * projectile->direction.y * deltaTime;
        if (projectile->position.x > game.getWindowWidth() + margin ||
            projectile->position.x < -margin ||
            projectile->position.y > game.getWindowHeight() + margin)
        {
            delete projectile;
            it = projectilesEnemy.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SceneMain::renderEnemyProjectiles()
{
    for (auto projectile: projectilesEnemy)
    {
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width,
            projectile->height
        };
        // SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &projectileRect);
        float angle = atan2(projectile->direction.y, projectile->direction.x) * 180 / M_PI - 90;
        SDL_RenderCopyEx(game.getRenderer(), projectile->texture, NULL, &projectileRect, angle, NULL, SDL_FLIP_NONE);
    }
}

void SceneMain::enemyExplode(Enemy *enemy)
{
    delete enemy;
}

SDL_FPoint SceneMain::getDirection(Enemy *enemy)
{
    auto x = (player.position.x + player.width / 2) - (enemy->position.x - enemy->width / 2);
    auto y = (player.position.y + player.height / 2) - (enemy->position.y + enemy->height / 2);
    auto length = sqrt(x * x + y * y);
    x /= length;
    y /= length;
    return SDL_FPoint{x, y};
}

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
    updatePlayer(deltaTime);
    updatePlayerProjectiles(deltaTime);
    spawnEnemy();
    updateEnemies(deltaTime);
    updateEnemyProjectiles(deltaTime);
    updateExplosions(deltaTime);
    updateItems(deltaTime);
}

void SceneMain::render()
{
    if (!isDead)
    {
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
    }
    // 渲染敌人
    renderEnemies();

    // 渲染玩家子弹
    renderPlayerProjectiles();
    // 渲染敌人子弹
    renderEnemyProjectiles();
    // 渲染爆炸
    renderExplosions();
    // 渲染道具
    renderItems();
    // 渲染UI
    renderUI();

}

void SceneMain::handleEvent(SDL_Event *event)
{
    return;
}

void SceneMain::init()
{
    // 读取并播放音乐
    bgMusic = Mix_LoadMUS("../../assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    if (bgMusic == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load bg music: %s", Mix_GetError());
    }
    Mix_PlayMusic(bgMusic, -1);

    // 读取音效资源
    sounds["player_shoot"] = Mix_LoadWAV("../../assets/sound/laser_shoot4.wav");
    sounds["enemy_shoot"] = Mix_LoadWAV("../../assets/sound/xs_laser.wav");
    sounds["player_explode"] = Mix_LoadWAV("../../assets/sound/explosion1.wav");
    sounds["enemy_explode"] = Mix_LoadWAV("../../assets/sound/explosion3.wav");
    sounds["ger_item"] = Mix_LoadWAV("../../assets/sound/eff5.wav");
    sounds["hit"] = Mix_LoadWAV("../../assets/sound/eff11.wav");

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

    // 初始化爆炸模板
    explosionTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/effect/explosion.png");
    SDL_QueryTexture(explosionTemplate.texture, NULL, NULL, &explosionTemplate.width, &explosionTemplate.height);
    explosionTemplate.totalFrames = explosionTemplate.width / explosionTemplate.height;
    // explosionTemplate.height /= 4;
    explosionTemplate.width = explosionTemplate.height;

    // 初始化道具模板
    itemTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/bonus_life.png");
    SDL_QueryTexture(itemTemplate.texture, NULL, NULL, &itemTemplate.width, &itemTemplate.height);
    itemTemplate.width /= 4;
    itemTemplate.height /= 4;

    // 初始化生命值UI
    uiHealth = IMG_LoadTexture(game.getRenderer(), "../../assets/image/Health UI Black.png");
}

void SceneMain::clean()
{
    // 释放音效资源
    for (auto& sound : sounds) {
        if (sound.second != nullptr)
        {
            Mix_FreeChunk(sound.second);
        }
    }
    sounds.clear();

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
    projectilesEnemy.clear();

    // 释放爆炸资源
    for (auto& explosion: explosions) {
        if (explosion != nullptr)
        {
            delete explosion;
        }
    }
    explosions.clear();

    for (auto& item: items) {
        if (item != nullptr)
        {
            delete item;
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
    
    // 释放爆炸模板资源
    if (explosionTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(explosionTemplate.texture);
    }

    // 释放道具模板资源
    if (itemTemplate.texture != nullptr)
    {    
        SDL_DestroyTexture(itemTemplate.texture);   
    }

    // 清理音乐资源
    if (bgMusic != nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(bgMusic);
    }

    // 清理生命值UI资源
    if (uiHealth != nullptr)
    {
        SDL_DestroyTexture(uiHealth);
    }
}

void SceneMain::keyboardControl(float deltaTime)
{
    if (isDead)
    {
        return;
    }
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
        // 发射子弹
        auto currentTime = SDL_GetTicks();
        if (currentTime - player.lastShootTime > player.coolDown)
        {
            shootPlayer();
            player.lastShootTime = currentTime;
        }
    }
    // 每帧更新时
    player.trail.push_back(player.position);
    // 最多保留8个历史点
    if (player.trail.size() > 8)
    { 
        player.trail.pop_front();
    }
}

void SceneMain::updatePlayer(float deltaTime)
{
    if (isDead)
    {
        return;
    }
    if (player.currentHealth <= 0)
    {   
        // 游戏结束
        auto currentTime = SDL_GetTicks();
        isDead = true;
        auto explosion = new Explosion(explosionTemplate);
        explosion->position.x = player.position.x + player.width / 2 - explosion->width / 2;
        explosion->position.y = player.position.y + player.height / 2 - explosion->height / 2;
        explosion->startTime = currentTime;
        explosions.push_back(explosion);
        Mix_PlayChannel(-1, sounds["player_explode"], 0);
        return;
    }
    for (auto enemy: enemies)
    {
        SDL_Rect enemyRect = {
            static_cast<int>(enemy->position.x),
            static_cast<int>(enemy->position.y),
            enemy->width,
            enemy->height
        };
        SDL_Rect playerRect = {
            static_cast<int>(player.position.x),
            static_cast<int>(player.position.y),
            player.width,
            player.height
        };
        if (SDL_HasIntersection(&playerRect, &enemyRect))
        {
            // 玩家被敌人击中
            player.currentHealth -= enemy->damage; // 扣除玩家的生命值
            enemy->currentHealth = 0; // 敌人死亡
        }
    }
}

void SceneMain::shootPlayer()
{

    // 发射子弹
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;
    projectile->position.y = player.position.y - projectile->height;
    projectilesPlayer.push_back(projectile);
    Mix_PlayChannel(0, sounds["player_shoot"], 0);
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
            // SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Projectile out of screen, deleted");
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
                    Mix_PlayChannel(-1, sounds["hit"], 0);
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

void SceneMain::playerGetItem(Item *item)
{
    switch (item->type)
    {
        case ItemType::Life:
        {
            player.currentHealth += 50;
            if (player.currentHealth > player.health)
            {
                player.currentHealth = player.health;
            }
        }
        break;
        case ItemType::Time:
        {

        }
        break;
        case ItemType::Shield:
        {

        }
        default:
        {

        }
            break;
    }

    Mix_PlayChannel(-1, sounds["ger_item"], 0);
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
        if (!isDead)
        {
            // 玩家死亡后，敌人不再移动
            enemy->position.y += deltaTime * enemy->speed;
        }

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
                if (currentTime - enemy->lastShootTime > enemy->coolDown && !isDead)
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
                    if (currentTime - enemy->lastShootTime > enemy->coolDown && !isDead)
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
    Mix_PlayChannel(-1, sounds["enemy_shoot"], 0);
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
            SDL_Rect playerRect = {
                static_cast<int>(player.position.x),
                static_cast<int>(player.position.y),
                player.width,
                player.height
            };
            SDL_Rect projectileRect = {
                static_cast<int>(projectile->position.x),
                static_cast<int>(projectile->position.y),
                projectile->width,
                projectile->height
            };
            if (SDL_HasIntersection(&playerRect, &projectileRect) && !isDead)
            {
                // 子弹击中玩家
                player.currentHealth -= projectile->damage; // 扣除玩家的生命值
                delete projectile;
                it = projectilesEnemy.erase(it);
            }
            else
            {
                ++it;
            }

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
    auto currentTime = SDL_GetTicks();
    auto explosion = new Explosion(explosionTemplate);
    explosion->position.x = enemy->position.x + enemy->width / 2 - explosion->width / 2;
    explosion->position.y = enemy->position.y + enemy->height / 2 - explosion->height / 2;
    explosion->startTime = currentTime;
    explosions.push_back(explosion);
    Mix_PlayChannel(-1, sounds["enemy_explode"], 0);
    if (dis(gen) < 0.5f)
    {
        dropItem(enemy);
    }

    delete enemy;
}

void SceneMain::updateExplosions(float deltaTime)
{
    auto currentTime = SDL_GetTicks();
    for (auto it = explosions.begin(); it != explosions.end();)
    {
        auto explosion = *it;
        explosion->currentFrame = (currentTime - explosion->startTime) * explosion->FPS / 1000.0f;
        if (explosion->currentFrame >= explosion->totalFrames)
        {
            delete explosion;
            it = explosions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SceneMain::renderExplosions()
{
    for (auto explosion: explosions)
    {
        SDL_Rect src = {
            explosion->currentFrame * explosion->width,
            0,
            explosion->width,
            explosion->height
        };
        SDL_Rect dst = {
            static_cast<int>(explosion->position.x),
            static_cast<int>(explosion->position.y),
            explosion->width,
            explosion->height
        };
        SDL_RenderCopy(game.getRenderer(), explosion->texture, &src, &dst);
    }
}

void SceneMain::dropItem(Enemy *enemy)
{
    auto item = new Item(itemTemplate);
    item->position.x = enemy->position.x + enemy->width / 2 - item->width / 2;
    item->position.y = enemy->position.y + enemy->height / 2 - item->height / 2;
    float angle = dis(gen) * 2 * M_PI;
    item->direction.x = cos(angle);
    item->direction.y = sin(angle);
    items.push_back(item);
}

void SceneMain::updateItems(float deltaTime)
{
    for (auto it = items.begin(); it != items.end();)
    {
        auto item = *it;
        // 物品的移动
        item->position.x += item->speed * item->direction.x * deltaTime;
        item->position.y += item->speed * item->direction.y * deltaTime;
        // 物品与边界的碰撞检测
        if (item->bounceCount > 0)
        {
            if (item->position.x < 0)
            {
                item->direction.x = -item->direction.x;
                item->speed += 100;
                item->bounceCount--;
            }
            else if (item->position.x + item->width > game.getWindowWidth())
            {
                item->direction.x = -item->direction.x;
                item->speed += 100;
                item->bounceCount--;
            }
            else if (item->position.y < 0)
            {
                item->direction.y = -item->direction.y;
                item->speed += 100;
                item->bounceCount--;
            }
            else if (item->position.y + item->height > game.getWindowHeight())
            {
                item->direction.y = -item->direction.y;
                item->speed += 100;
                item->bounceCount--;
            }
        }
        // 物品的边界检测
        if (item->position.x + item->width < 0 ||
            item->position.x > game.getWindowWidth() ||
            item->position.y + item->height < 0 ||
            item->position.y > game.getWindowHeight())
        {
            delete item;
            it = items.erase(it);
        }
        else
        {
            SDL_Rect playerRect = {
                static_cast<int>(player.position.x),
                static_cast<int>(player.position.y),
                player.width,
                player.height
            };
            SDL_Rect itemRect = {
                static_cast<int>(item->position.x),
                static_cast<int>(item->position.y),
                item->width,
                item->height
            };
            if (SDL_HasIntersection(&playerRect, &itemRect))
            {
                // 玩家获得物品
                playerGetItem(item);
                delete item;
                it = items.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void SceneMain::renderItems()
{
    for (auto item: items)
    {
        SDL_Rect itemRect = {
            static_cast<int>(item->position.x),
            static_cast<int>(item->position.y),
            item->width,
            item->height
        };
        SDL_RenderCopy(game.getRenderer(), item->texture, NULL, &itemRect);
    }
}

void SceneMain::renderUI()
{
    int x = 30;
    int y = 30;
    int size = 32;
    int offset = 40;
    SDL_SetTextureColorMod(uiHealth, 100, 100, 100);
    for(int i = 0; i < player.health / 10; i++)
    {
        SDL_Rect rect = {
            x + i * offset,
            y,
            size,
            size
        };
        SDL_RenderCopy(game.getRenderer(), uiHealth, NULL, &rect);
    }
    SDL_SetTextureColorMod(uiHealth, 255, 255, 255);
    for(int i = 0; i < player.currentHealth / 10; i++)
    {
        SDL_Rect rect = {
            x + i * offset,
            y,
            size,
            size
        };
        SDL_RenderCopy(game.getRenderer(), uiHealth, NULL, &rect);
    }

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

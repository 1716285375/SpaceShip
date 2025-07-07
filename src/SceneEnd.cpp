#include "SceneEnd.h"
#include "SceneTitle.h"
#include "Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


SceneEnd::~SceneEnd()
{
}

void SceneEnd::init()
{
    m_bgMusic = Mix_LoadMUS("../../assets/music/06_Battle_in_Space_Intro.ogg");
    if (m_bgMusic == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Mix_LoadMUS failed: %s", SDL_GetError());
        // game.setRunning(false);
    }
    Mix_PlayMusic(m_bgMusic, -1);
    if (!SDL_IsTextInputActive())
    {
        SDL_StartTextInput();
    }
    if (!SDL_IsTextInputActive())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_StartTextInput failed: %s", SDL_GetError());
    }
}

void SceneEnd::update(float deltaTime)
{
    m_blinkTimer -= deltaTime;
    if (m_blinkTimer < 0)
    {
        m_blinkTimer += 1.0f;
    }
}

void SceneEnd::render()
{
    if (m_isTyping)
    {
        renderTitletext();
    }
    else
    {
        renderRankText();
    }

}

void SceneEnd::clean()
{
    if (m_bgMusic!= nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(m_bgMusic);
    }
}

void SceneEnd::handleEvent(SDL_Event *event)
{
    if (m_isTyping)
    {
        if (event->type == SDL_TEXTINPUT)
        {
            m_name += event->text.text;
        }
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                m_isTyping = false;
                SDL_StopTextInput();
                if (m_name.empty())
                {
                    m_name = "Player";
                }
                game.addToScoreBoard(game.getScore(), m_name);
            }
            if (event->key.keysym.sym == SDL_SCANCODE_BACKSPACE)
            {
                removeUTF8Char(m_name);
            }
        }
    }
    else
    {
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                auto scene = new SceneTitle();
                game.changeScene(scene);
            }
        }
    }
}

void SceneEnd::renderTitletext()
{
    std::string titleText = "Game Over";
    std::string scoreText = "Your Score: " + std::to_string(game.getScore());
    std::string nameText = "Please Input Your Name, Press Enter to Confirm";
    SDL_Color textColor = { 255, 255, 255, 255 };
    
    game.renderTextCenter(titleText, game.getWindowWidth(), game.getWindowHeight() / 8, 72, textColor, FontType::Silver);
    game.renderTextCenter(scoreText, game.getWindowWidth(), game.getWindowHeight() / 4, 60, textColor, FontType::Silver);
    game.renderTextCenter(nameText, game.getWindowWidth(), game.getWindowHeight() / 2, 36, textColor, FontType::Silver);

    if (!m_name.empty())
    {
        SDL_Point pos = game.renderTextCenter(m_name, game.getWindowWidth(), game.getWindowHeight() / 2 + 100, 36, textColor, FontType::Silver);
        if (m_blinkTimer < 0.5f)
        {
            game.renderText("_", pos.x, pos.y, 36, textColor, FontType::Silver);
        }

    }
    else
    {
        if (m_blinkTimer < 0.5f)
        {
            game.renderTextCenter("_", game.getWindowWidth(), game.getWindowHeight() / 2 + 100, 36, textColor, FontType::Silver);
        }
        
    }
}

void SceneEnd::renderRankText()
{
    SDL_Color textColor = { 255, 255, 255, 255 };
    game.renderTextCenter("Rank", game.getWindowWidth(), 0.05 * game.getWindowHeight(), 60, textColor, FontType::Silver);
    int i = 1;
    int posY = 0.2 * game.getWindowHeight();
    int posX = 0.2 * game.getWindowWidth();
    for (auto &item : game.getScoreBoard())
    {
        std::string name = std::to_string(i) + ". " + item.second;
        std::string score = std::to_string(item.first);
        game.renderText(name, posX, posY, 48, textColor, FontType::Silver);
        game.renderTextRight(score, posX, posY, 48, textColor, FontType::Silver);
        posY += 50;
        ++i;
    }
    if (m_blinkTimer < 0.5f)
    {
        game.renderTextCenter("Press Enter to back to Menu", game.getWindowWidth(), 0.8 * game.getWindowHeight(), 60, textColor, FontType::Silver);
    }
}

void SceneEnd::removeUTF8Char(std::string &str)
{
    if (str.empty())
    {
        return;
    }
    auto lastChar = str.back();
    if ((lastChar & 0b10000000) == 0b10000000)    // 中文字符
    {
        str.pop_back();
        while((str.back() & 0b11000000) != 0b11000000) // 中文字符后续字节
        {
            str.pop_back(); // 移除后续字节
        }
    }
    str.pop_back();
}

#ifndef SCENEEND_H
#define SCENEEND_H


#include "Scene.h"
#include <string>
#include <SDL_mixer.h>

class SceneEnd : public Scene {
public:
    ~SceneEnd();
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handleEvent(SDL_Event* event) override;

private:
    Mix_Music* m_bgMusic;
    int m_score;
    bool m_isTyping = true;
    float m_blinkTimer = 1.0f;
    std::string m_name;
    void renderTitletext();
    void renderRankText();

    void removeUTF8Char(std::string& str);

};

#endif
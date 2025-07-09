#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Scene.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class LevelScene : public Scene {
    public:
        // LevelScene(const std::string& filename);
        // ~LevelScene();

    private:

    // 关卡场景

    // std::ifstream f("example.json");
    // json data = json::parse(f);
    // m_levelPath;
};



#endif // LEVELSCENE_H
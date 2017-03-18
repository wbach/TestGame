#pragma once
#include "../GameEngine/Engine/Engine.h"
#include "../GameEngine/Scene/Scene.hpp"
#include "../GameEngine/Objects/RenderAble/Grass.h"
#include "../GameEngine/Camera/FirstPersonCamera.h"
#include "../GameEngine/Camera/ThridPersonCamera.h"
#include "../GameEngine/Objects/RenderAble/Terrain.h"
#include "Player.h"
#include <map>
class MainScene : public CScene
{
public:
    MainScene(CEngine& engine);
    virtual ~MainScene() override;
    virtual int		Initialize();
    virtual void	PostInitialize() {};
    virtual int		Update();
private:
    std::map<CTerrain::TexturesTypes, std::string> CreateTerrainTexturesMap();
    void AddTerrain(std::map<CTerrain::TexturesTypes, std::string>& textures);
    void AddGrass();
    CPlayer* player;
    CTerrain *terrain;
    double time_clock = 0;
    CEngine& engine;
};

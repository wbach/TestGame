#include "MainScene.h"

MainScene::MainScene(CEngine &engine)
    : engine(engine)
{
}

MainScene::~MainScene()
{

}

int MainScene::Initialize()
{
    auto crate = AddGameObject(new CEntity(m_ResourceManager, "../Data/Meshes/Crate/crate.obj", glm::vec3(0, 2, 0)), glm::vec3(0,0, -5));
    engine.m_Renderer->Subscribe(crate);

    player = new CPlayer(&engine.m_InputManager, m_ResourceManager, "../Data/Meshes/Triss/Triss.obj", glm::vec3(0, 2, 0)), glm::vec3(0, 0, 0);
    AddGameObject(player);
    engine.m_Renderer->Subscribe(player);

    auto small_house = AddGameObject(new CEntity(m_ResourceManager, "../Data/Meshes/smallHouse1/smallHouse1.obj", glm::vec3(0,5,0)), glm::vec3(0.f, 0.f, -5.f));
    engine.m_Renderer->Subscribe(small_house);

    auto terrain_textures = CreateTerrainTexturesMap();
    AddTerrain(terrain_textures);
    AddGrass();

    m_DayNightCycle.SetDirectionalLight(&m_DirectionalLight);
    m_DayNightCycle.SetTime(.5f);

    m_Camera = std::make_unique<CFirstPersonCamera>(&engine.m_InputManager, &engine.m_DisplayManager);

    //m_Camera = std::make_unique<CThirdPersonCamera>(&engine.m_InputManager, player->m_WorldTransform);
    return 0;
}

int MainScene::Update()
{
    if (m_Camera != nullptr)
    {
        m_Camera->CalculateInput();
        m_Camera->Move();
    }
    m_DeltaTime = static_cast<float>(engine.m_DisplayManager.GetDeltaTime());
    m_GloabalTime += m_DeltaTime;

    time_clock += m_DeltaTime;
    if(time_clock > 1.f)
    {
        int hour = 0, minutes = 0;
        m_DayNightCycle.GetCurrentHour(hour, minutes);
        std::cout << "Game Time : " << hour << " : " << minutes << "\n";
        Utils::PrintVector("Light position : ", this->m_DirectionalLight.GetPosition());
        time_clock = 0;
    }

    m_DayNightCycle.Update(m_DeltaTime);

    player->Move(m_DeltaTime);
    player->CheckInputs();

    auto height = terrain->GetHeightofTerrain(player->m_WorldTransform.GetPositionXZ());
    auto ppos = player->m_WorldTransform.GetPosition();
    if (ppos.y < height)
    {
        ppos.y = height;
        player->SetPosition(ppos);
    }
    return 0;
}

std::map<CTerrain::TexturesTypes, std::string> MainScene::CreateTerrainTexturesMap()
{
    return
    {
        { CTerrain::blendMap , "../Data/Textures/testBlendMap.png"},
        { CTerrain::backgorundTexture, "../Data/Textures/G3_Nature_Ground_Grass_01_Diffuse_01.png" },
        { CTerrain::redTexture, "../Data/Textures/165.png",  },
        { CTerrain::greenTexture,"../Data/Textures/G3_Nature_Ground_Path_03_Diffuse_01.png"},
        { CTerrain::blueTexture, "../Data/Textures/G3_Nature_Ground_Forest_01_Diffuse_01.png" },
        { CTerrain::displacementMap, "../Data/Textures/heightmap.png" }
    };
}

void MainScene::AddTerrain(std::map<CTerrain::TexturesTypes, std::string> &textures)
{
    terrain = new CTerrain();
    for(const auto& t : textures)
         terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture(t.second), t.first);

    SImage height_map;
    m_ResourceManager.GetTextureLaoder().ReadFile(textures[CTerrain::displacementMap], height_map, TextureFlip::VERTICAL);
    terrain->LoadHeight(height_map);

    terrain->model = m_ResourceManager.LoadModel("../Data/Example/quad.obj");
    m_ResourceManager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(terrain->model);

    AddGameObject(terrain, glm::vec3(0.f, 0.f, 0.f));
    engine.m_Renderer->Subscribe(terrain);
}

void MainScene::AddGrass()
{
    std::vector<float> grass_position;
    std::vector<unsigned short> indicies;
    std::vector<float> empty_float_vec;
    std::vector<SVertexBoneData> empty_bones;
    SMaterial grass_material;

    for(float y = 0.f ; y < 200.f; y += 1.5f)
    {
        for (float x = 0.f; x < 200.f; x += 1.5f)
        {
            grass_position.push_back(x + ((rand() % 200 - 100) / 100.f));
            grass_position.push_back(terrain->GetHeightofTerrain(x, y) + 1.f);
            grass_position.push_back(y + ((rand() % 200 - 100) / 100.f));
        }
    }

    CGrass* grass = new CGrass();
    grass->model = new CModel();
    grass_material.m_DiffuseTexture = m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/G3_Nature_Plant_Grass_06_Diffuse_01.png");
    grass->model->AddMesh(grass_position, empty_float_vec, empty_float_vec, empty_float_vec, indicies, grass_material, empty_bones);
    m_ResourceManager.AddModel(grass->model);
    engine.m_Renderer->Subscribe(grass);
}

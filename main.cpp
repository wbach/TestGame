#include "../GameEngine/Engine/Engine.h"
#include "../GameEngine/Scene/Scene.hpp"
#include "../GameEngine/Objects/RenderAble/Grass.h"
#include "../GameEngine/Camera/FirstPersonCamera.h"
#include "../GameEngine/Camera/ThridPersonCamera.h"
#include "../GameEngine/Objects/RenderAble/Terrain.h"
#include "Player.h"

//#include "../GameEngine/Objects/RenderAble/RenderObject.h"

void MemoryTest()
{
	static CEngine engine("Test Game - Open GL", 640, 480, false);

	class TestScene : public CScene
	{
	public:
		TestScene()
		{
		}
		virtual int		Initialize()
		{
			//AddEntity("../Data/Example/monkey.obj", glm::vec3(0,1,0));
			/*AddEntity("../Data/Meshes/smallHouse1/smallHouse1.obj");
			AddEntity("../Data/Meshes/G3_Myrtana_Castle_Mainhouse/G3_Myrtana_Castle_Mainhouse.obj");
			AddEntity("../Data/Meshes/fishingHouse/fishingHouse.obj");
			AddEntity("../Data/Meshes/alchemTable/alchemTable.obj");*/
			m_Camera = std::make_unique<CFirstPersonCamera>(&engine.m_InputManager, &engine.m_DisplayManager);
			return 0;
		}
		virtual void	PostInitialize() {};
		virtual int		Update()
		{
			if (m_Camera != nullptr)
			{
				m_Camera->CalculateInput();
				m_Camera->Move();
			}
			return 0;
		}

	};
	engine.Init();

	long long i = 0;
	while(1)
	{
		std::cout << "Reply: "<< i++ << std::endl;

		if (engine.m_Scene != nullptr)
			engine.m_Scene.reset();
		engine.m_Scene = std::make_unique<TestScene>();
		engine.PreperaScene();
	}
}
void TestGameStart()
{
    static CEngine engine("Test Game - Open GL", 1000, 600, false);

	class TestScene : public CScene
	{
		CPlayer* player;
		CTerrain *terrain;
        double time_clock = 0;
	public:
		TestScene()
		{
		}

		virtual int		Initialize()
		{
			auto crate = AddGameObject(new CEntity(m_ResourceManager, "../Data/Meshes/Crate/crate.obj", glm::vec3(0, 2, 0)), glm::vec3(0,0, -5));
			engine.m_Renderer->Subscribe(crate);

			player = new CPlayer(&engine.m_InputManager, m_ResourceManager, "../Data/Meshes/Triss/Triss.obj", glm::vec3(0, 2, 0)), glm::vec3(0, 0, 0);
			AddGameObject(player);
			engine.m_Renderer->Subscribe(player);

			auto small_house = AddGameObject(new CEntity(m_ResourceManager, "../Data/Meshes/smallHouse1/smallHouse1.obj", glm::vec3(0,5,0)), glm::vec3(0.f, 0.f, -5.f));
			engine.m_Renderer->Subscribe(small_house);

			terrain = new CTerrain();
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/testBlendMap.png"), CTerrain::blendMap);
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/G3_Nature_Ground_Grass_01_Diffuse_01.png"), CTerrain::backgorundTexture);
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/165.png"), CTerrain::redTexture);
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/G3_Nature_Ground_Path_03_Diffuse_01.png"), CTerrain::greenTexture);
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/G3_Nature_Ground_Forest_01_Diffuse_01.png"), CTerrain::blueTexture);
			terrain->SetTexture(m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/heightmap.png"), CTerrain::displacementMap);

			SImage height_map;
			m_ResourceManager.GetTextureLaoder().ReadFile("../Data/Textures/heightmap.png", height_map, TextureFlip::VERTICAL);
			terrain->LoadHeight(height_map);

			std::vector<float> grass_position;
          //  grass_position.reserve(100 * 100);

            for(float y = 0.f ; y < 200.f; y += 1.5f)
            {
                for (float x = 0.f; x < 200.f; x += 1.5f)
				{
                    grass_position.push_back(x + ((rand() % 200 - 100) / 100.f));
                    grass_position.push_back(terrain->GetHeightofTerrain(x, y) + 1.f);
                    grass_position.push_back(y + ((rand() % 200 - 100) / 100.f));
				}
            }
            std::cout << "Grass size : " << grass_position.size() << std::endl;
            //*

            std::vector<unsigned short> indicies;

            CGrass* grass = new CGrass();
            grass->model = new CModel();
            SMaterial grass_material;
            grass_material.m_DiffuseTexture = m_ResourceManager.GetTextureLaoder().LoadTexture("../Data/Textures/G3_Nature_Plant_Grass_06_Diffuse_01.png");
            std::vector<float> empty_float_vec;
            std::vector<SVertexBoneData> empty_bones;
            auto mesh = grass->model->AddMesh(grass_position, empty_float_vec, empty_float_vec, empty_float_vec, indicies, grass_material, empty_bones);
            //m_ResourceManager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(grass->model);
            m_ResourceManager.AddModel(grass->model);
            engine.m_Renderer->Subscribe(grass);
            //*/
			//m_Texture = scene->GetResourceManager().GetTextureLaoder().LoadTextureImmediately("../Data/Textures/G3_Nature_Plant_Grass_06_Diffuse_01.png");			

            /*
            grassvertex.reserve(positions.size() * 3);
			for (const auto& v : positions)
			{
				grassvertex.push_back(v.x);
				grassvertex.push_back(v.y);
				grassvertex.push_back(v.z);
			}
			m_MeshVao = Utils::CreateVao();
			m_VertexSize = grassvertex.size() / 3;
			m_VertexVbo = Utils::StoreDataInAttributesList(0, 3, grassvertex);
            Utils::UnbindVao();//*/

			terrain->model = m_ResourceManager.LoadModel("../Data/Example/quad.obj");
			m_ResourceManager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(terrain->model);

			AddGameObject(terrain, glm::vec3(0.f, 0.f, 0.f));
			engine.m_Renderer->Subscribe(terrain);



		//	AddEntity("../Data/Meshes/Crate/crate.obj");
			//AddEntity("../Data/Meshes/smallHouse1/smallHouse1.obj");
		//	AddEntity("../Data/Meshes/G3_Myrtana_Castle_Mainhouse/G3_Myrtana_Castle_Mainhouse.obj");
			//AddEntity("../Data/Meshes/fishingHouse/fishingHouse.obj");
			//AddEntity("../Data/Meshes/alchemTable/alchemTable.obj");*/
			
            m_DayNightCycle.SetDirectionalLight(&m_DirectionalLight);
            m_DayNightCycle.SetTime(.5f);

			m_Camera = std::make_unique<CFirstPersonCamera>(&engine.m_InputManager, &engine.m_DisplayManager);

			//m_Camera = std::make_unique<CThirdPersonCamera>(&engine.m_InputManager, player->m_WorldTransform);
			return 0;
		}
		virtual void	PostInitialize() {};
		virtual int		Update()
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
	};
	engine.Init();

	if (engine.m_Scene != nullptr)
		engine.m_Scene.reset();
	engine.m_Scene = std::make_unique<TestScene>();
	engine.PreperaScene();
	engine.GameLoop();
}

int main(int argc, char* argv[])
{	
	//MemoryTest();
	CLogger::Instance().EnableLogs();
	TestGameStart();
	return 0;
}

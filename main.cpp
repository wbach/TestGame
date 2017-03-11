#include "../GameEngine/Engine/Engine.h"
#include "../GameEngine/Scene/Scene.hpp"
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
	static CEngine engine("Test Game - Open GL", 1366, 768, false);

	class TestScene : public CScene
	{
		CPlayer* player;
		CTerrain *terrain;
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

			terrain->model = m_ResourceManager.LoadModel("../Data/Example/quad.obj");
			m_ResourceManager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(terrain->model);

			AddGameObject(terrain, glm::vec3(0.f, 0.f, 0.f));
			engine.m_Renderer->Subscribe(terrain);

		//	AddEntity("../Data/Meshes/Crate/crate.obj");
			//AddEntity("../Data/Meshes/smallHouse1/smallHouse1.obj");
		//	AddEntity("../Data/Meshes/G3_Myrtana_Castle_Mainhouse/G3_Myrtana_Castle_Mainhouse.obj");
			//AddEntity("../Data/Meshes/fishingHouse/fishingHouse.obj");
			//AddEntity("../Data/Meshes/alchemTable/alchemTable.obj");*/
			//m_Camera = std::make_unique<CFirstPersonCamera>(&engine.m_InputManager, &engine.m_DisplayManager);

			m_Camera = std::make_unique<CThirdPersonCamera>(&engine.m_InputManager, player->m_WorldTransform);
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

			player->Move(0.01f);
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
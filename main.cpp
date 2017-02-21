#include "../GameEngine/Engine/Engine.h"
#include "../GameEngine/Scene/Scene.hpp"
#include "../GameEngine/Camera/FirstPersonCamera.h"

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
			AddEntity("../Data/Meshes/smallHouse1/smallHouse1.obj");
			AddEntity("../Data/Meshes/G3_Myrtana_Castle_Mainhouse/G3_Myrtana_Castle_Mainhouse.obj");
			AddEntity("../Data/Meshes/fishingHouse/fishingHouse.obj");
			AddEntity("../Data/Meshes/alchemTable/alchemTable.obj");
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

	for (int x = 0; x < 10000000000000; x++)
	{
		if (engine.m_Scene != nullptr)
			engine.m_Scene.reset();
		engine.m_Scene = std::make_unique<TestScene>();
		engine.PreperaScene();
	}
}
void TestGameStart()
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
			AddEntity("../Data/Meshes/smallHouse1/smallHouse1.obj");
			AddEntity("../Data/Meshes/G3_Myrtana_Castle_Mainhouse/G3_Myrtana_Castle_Mainhouse.obj");
			AddEntity("../Data/Meshes/fishingHouse/fishingHouse.obj");
			AddEntity("../Data/Meshes/alchemTable/alchemTable.obj");
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

	for (int x = 0; x < 10000000000000; x++)
	{
		if (engine.m_Scene != nullptr)
			engine.m_Scene.reset();
		engine.m_Scene = std::make_unique<TestScene>();
		engine.PreperaScene();
		engine.GameLoop();
	}
}

int main(int argc, char* argv[])
{	
	MemoryTest();

	return 0;
}
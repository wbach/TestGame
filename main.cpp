#include "MainScene.h"

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
    static CEngine engine("Test Game - Open GL", 1200, 700, false);
	engine.Init();
    engine.m_Scene = std::make_unique<MainScene>(engine);
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

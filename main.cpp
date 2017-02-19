#include "../GameEngine/Engine/Engine.h"
#include "../GameEngine/Scene/Scene.hpp"
#include "../GameEngine/Camera/FirstPersonCamera.h"

//#include "../GameEngine/Objects/RenderAble/RenderObject.h"



int main(int argc, char* argv[])
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
	engine.m_Scene = std::make_unique<TestScene>();
	engine.Init();
	engine.GameLoop();

	return 0;
}
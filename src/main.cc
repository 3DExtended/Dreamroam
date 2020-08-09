#include <ComponentBased/SceneHandler.hh>
#include <Scenes/DreamroamScene.hh>

#include <RenderingSystem/RenderingSystem.hh>
#include "main.h"

using namespace DCore::Example;
int main(int argc, char** argv)
{
	auto mSceneHandler = SceneHandler::getInstance();
	mSceneHandler->addScene(std::make_shared<DreamroamScene>());

	mSceneHandler->run();
	return 0;
}
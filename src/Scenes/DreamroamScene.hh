#pragma once
#include <ComponentBased/AScene.hh>
using namespace DCore::ComponentSystem;

namespace DCore {
	namespace Example {
		class DreamroamScene : public AScene
		{
		public:
			DreamroamScene();
			void start();
			void update(double dt);

		private:
			void createGameObjects();

			void registerSystems();
		};
	}
}
#pragma once
#include <ComponentBased/AScene.hh>

class DreamroamScene : public AScene
{
public:
  DreamroamScene();
  void start();
  void update(double dt);

private:
  void createGameObjects();
};

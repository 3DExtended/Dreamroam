#include "DreamroamScene.hh"
#include <Components/RenderComponent.hh>

DreamroamScene::DreamroamScene() : AScene()
{
    mGeometryStore = std::make_shared<GeometryStore>(mDevice);

    std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames;
    imageTexturePathsAndNames.push_back(std::pair<std::string, std::string>("assets/atlas.png","atlas"));
    mTextureStore = std::make_shared<TextureStore>(mDevice, imageTexturePathsAndNames);
}

void DreamroamScene::start()
{
    createGameObjects();
}

void DreamroamScene::update(double dt) {}

inline void DreamroamScene::createGameObjects()
{
    { //load world.obj
        mGeometryStore->registerGeometryFromFileSingle("assets/world.obj", "World");
        auto houseGO = this->instantiate("World");
        auto renderer = std::make_shared<RenderComponent>();
        renderer->active = true;
        renderer->hasTexture = true;
        renderer->textureObj = mTextureStore->getTextureWithName("atlas");
        renderer->isTransparent = false;
        renderer->geometryObj = mGeometryStore->getGeometryWithName("World");
        houseGO->addComponent(renderer);
    }
}

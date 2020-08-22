#pragma once

#include <RenderingSystem/MeshHandlers/GeometryStore.hh>
#include <RenderingSystem/TextureHandlers/TextureStore.hh>
#include <vector>

#include "Systems/UntypedSystemBase.hh"
#include "entt/entt.hpp"
#include "glm/glm.hpp"

namespace DCore {
namespace ComponentSystem {
typedef entt::entity EntityHandle;

using namespace DCore::Textures;
using namespace DCore::Meshes;
class Entity;

/// <summary>
/// This class is abstract and has to be inherited.
/// It provides the standard functions as start() or update().
/// Use your instance of this class in combination with the SceneHandler to
/// define your world. Note: You can create new entities using CreateEntity().
/// </summary>
class AScene {
public:
    /// <summary>
    /// Creates the rendering device instance.
    /// </summary>
    AScene();

    ~AScene();

    /// <summary>
    /// This is called right after the sceneHandler switches to the new scene.
    /// Use this to register your gameObjects, textures and components.
    /// </summary>
    virtual void start(){};

    /// <summary>
    /// This is called for each frame while the scene is loaded.
    /// Can be used to call all entity systems.
    /// Note: This function should not be used to run the games logic. However,
    /// at the current time this is all you got.
    /// </summary>
    /// <param name="dt">Delta Time of the frame in seconds</param>
    virtual void update(double dt){};

    /// <summary>
    /// This is called right before this scene is destroyed. Use this to
    /// deconstruct any game objects and handlers.
    /// </summary>
    virtual void destroy(){};

    /// <summary>
    /// This is called in the rendering loop and should be used to construct
    /// the imgui frame.
    /// </summary>
    virtual void imGuiRender(){};

    /// <summary>
    /// Creates and registers a new entity for your scene.
    /// Please note that you need to keep the returned entity when you want to
    /// update it in the scene. The preferred version for updating entities
    /// however should be the system feature.
    /// </summary>
    /// <param name="name">The name of the enity in the scene. This will be
    /// stored in the TagComponent on the entity.</param> <returns>A new entity
    /// instance.</returns>
    Entity CreateEntity(const std::string& name = std::string());

    /// <summary>
    /// Returns the texture layout of the scenes current texture store.
    /// </summary>
    /// <returns>The texture layout of the texture store</returns>
    const lava::SharedDescriptorSetLayout
    GetCurrentSceneTextureStoreTextureLayout();

    /// <summary>
    /// When you want to act on entities and their oponents, write a custom
    /// system (using the SystemBase templated class) and register it using this
    /// method.
    /// </summary>
    /// <param name="systemPtr">A pointer to a system you want to
    /// register.</param>
    void RegisterEntitySystem(std::shared_ptr<UntypedSystemBase> systemPtr) {
        m_Systems.push_back(systemPtr);
    }

protected:
    /// <summary>
    /// The device which is used to render the scene.
    /// This will be used for a number of initialization procedures.
    /// </summary>
    lava::SharedDevice mDevice;

    /// <summary>
    /// This GeometryStore is used to load meshes and push them to the GPU.
    /// </summary>
    std::shared_ptr<GeometryStore> mGeometryStore;

    /// <summary>
    /// This TextureStore is used to load textures and push them to the GPU.
    /// </summary>
    std::shared_ptr<TextureStore> mTextureStore;

private:
    /// <summary>
    /// We need this in order to access the registry for registering new
    /// components on an entity.
    /// </summary>
    friend class Entity;

    /// <summary>
    /// The SceneHandler must have access to the registry for rendering and
    /// sorting objects.
    /// </summary>
    friend class SceneHandler;

    /// <summary>
    /// The registry for entities in the scene.
    /// </summary>
    entt::registry m_Registry;

    /// <summary>
    /// The list of systems of the scene which will get called when the scene is
    /// active.
    /// </summary>
    std::vector<std::shared_ptr<UntypedSystemBase>> m_Systems;
};
}  // namespace ComponentSystem
}  // namespace DCore
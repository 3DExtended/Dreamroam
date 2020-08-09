# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`DCore::ComponentSystem`](#namespace_d_core_1_1_component_system) | 
`namespace `[`DCore::Example`](#namespace_d_core_1_1_example) | 
`namespace `[`DCore::Meshes`](#namespace_d_core_1_1_meshes) | 
`namespace `[`DCore::Rendering`](#namespace_d_core_1_1_rendering) | 
`namespace `[`DCore::Textures`](#namespace_d_core_1_1_textures) | 
`namespace `[`lava::pipeline`](#namespacelava_1_1pipeline) | 
`namespace `[`UtilsLava`](#namespace_utils_lava) | Partially taken from the Vulkan Cookbook: [https://github.com/PacktPublishing/Vulkan-Cookbook](https://github.com/PacktPublishing/Vulkan-Cookbook)
`class `[`GlobalSettings`](#class_global_settings) | 
`struct `[`stbi_io_callbacks`](#structstbi__io__callbacks) | 

# namespace `DCore::ComponentSystem` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::ComponentSystem::AScene`](#class_d_core_1_1_component_system_1_1_a_scene) | This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e) or [update()](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec). Use your instance of this class in combination with the [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) to define your world. Note: You can create new entities using [CreateEntity()](#class_d_core_1_1_component_system_1_1_a_scene_a67909f14c3eda839350c96416d934b88_1a67909f14c3eda839350c96416d934b88).
`class `[`DCore::ComponentSystem::Entity`](#class_d_core_1_1_component_system_1_1_entity) | 
`class `[`DCore::ComponentSystem::SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler) | A [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) is the manager of the game engine. It implements the singleton pattern and provides getters for the current scene, the switch scene method and more.
`class `[`DCore::ComponentSystem::SystemBase`](#class_d_core_1_1_component_system_1_1_system_base) | System base is the recommended method for accessing your entities and their components. The system originates from the core concept of ECS (entity component systems): You write custom components which can be assigned to entities. When you want to update those components (or want to read them), you have to create a system.
`struct `[`DCore::ComponentSystem::TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component) | This component stores the name and the tags of the entity.
`struct `[`DCore::ComponentSystem::TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component) | This class is a part of each GameObject which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.

# class `DCore::ComponentSystem::AScene` 

This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e) or [update()](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec). Use your instance of this class in combination with the [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) to define your world. Note: You can create new entities using [CreateEntity()](#class_d_core_1_1_component_system_1_1_a_scene_a67909f14c3eda839350c96416d934b88_1a67909f14c3eda839350c96416d934b88).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene_ad0eacf691dbc8240fdf3a42d450c1042_1ad0eacf691dbc8240fdf3a42d450c1042)`()` | Creates the rendering device instance.
`public  `[`~AScene`](#class_d_core_1_1_component_system_1_1_a_scene_1a9faf7f1a271327227e83627432d0b210)`()` | 
`public inline virtual void `[`start`](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e)`()` | This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.
`public inline virtual void `[`update`](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec)`(double dt)` | This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.
`public inline virtual void `[`destroy`](#class_d_core_1_1_component_system_1_1_a_scene_a420362ec1665e379fd3136b98c92c295_1a420362ec1665e379fd3136b98c92c295)`()` | This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.
`public `[`Entity`](#class_d_core_1_1_component_system_1_1_entity)` `[`CreateEntity`](#class_d_core_1_1_component_system_1_1_a_scene_a67909f14c3eda839350c96416d934b88_1a67909f14c3eda839350c96416d934b88)`(const std::string & name)` | Creates and registers a new entity for your scene. Please note that you need to keep the returned entity when you want to update it in the scene. The preferred version for updating entities however should be the system feature.
`public const lava::SharedDescriptorSetLayout `[`GetCurrentSceneTextureStoreTextureLayout`](#class_d_core_1_1_component_system_1_1_a_scene_a8466933c7f155a1d5c778c0432680d6f_1a8466933c7f155a1d5c778c0432680d6f)`()` | Returns the texture layout of the scenes current texture store.
`protected lava::SharedDevice `[`mDevice`](#class_d_core_1_1_component_system_1_1_a_scene_aea101e43d1950af16e725b7a53ec136b_1aea101e43d1950af16e725b7a53ec136b) | The device which is used to render the scene. This will be used for a number of initialization procedures.
`protected std::shared_ptr< `[`GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store)` > `[`mGeometryStore`](#class_d_core_1_1_component_system_1_1_a_scene_a4082224d4bc85a7536a5f830a44bd446_1a4082224d4bc85a7536a5f830a44bd446) | This GeometryStore is used to load meshes and push them to the GPU.
`protected std::shared_ptr< `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store)` > `[`mTextureStore`](#class_d_core_1_1_component_system_1_1_a_scene_a9f5432333052579e1af732c2ba94fd74_1a9f5432333052579e1af732c2ba94fd74) | This TextureStore is used to load textures and push them to the GPU.

## Members

#### `public  `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene_ad0eacf691dbc8240fdf3a42d450c1042_1ad0eacf691dbc8240fdf3a42d450c1042)`()` 

Creates the rendering device instance.

#### `public  `[`~AScene`](#class_d_core_1_1_component_system_1_1_a_scene_1a9faf7f1a271327227e83627432d0b210)`()` 

#### `public inline virtual void `[`start`](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e)`()` 

This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.

#### `public inline virtual void `[`update`](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec)`(double dt)` 

This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

#### Parameters
* `dt` Delta Time of the frame in seconds

#### `public inline virtual void `[`destroy`](#class_d_core_1_1_component_system_1_1_a_scene_a420362ec1665e379fd3136b98c92c295_1a420362ec1665e379fd3136b98c92c295)`()` 

This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.

#### `public `[`Entity`](#class_d_core_1_1_component_system_1_1_entity)` `[`CreateEntity`](#class_d_core_1_1_component_system_1_1_a_scene_a67909f14c3eda839350c96416d934b88_1a67909f14c3eda839350c96416d934b88)`(const std::string & name)` 

Creates and registers a new entity for your scene. Please note that you need to keep the returned entity when you want to update it in the scene. The preferred version for updating entities however should be the system feature.

#### Parameters
* `name` The name of the enity in the scene. This will be stored in the [TagComponent](#struct_d_core_1_1_component_system_1_1_tag_component) on the entity.

#### Returns
A new entity instance.

#### `public const lava::SharedDescriptorSetLayout `[`GetCurrentSceneTextureStoreTextureLayout`](#class_d_core_1_1_component_system_1_1_a_scene_a8466933c7f155a1d5c778c0432680d6f_1a8466933c7f155a1d5c778c0432680d6f)`()` 

Returns the texture layout of the scenes current texture store.

#### Returns
The texture layout of the texture store

#### `protected lava::SharedDevice `[`mDevice`](#class_d_core_1_1_component_system_1_1_a_scene_aea101e43d1950af16e725b7a53ec136b_1aea101e43d1950af16e725b7a53ec136b) 

The device which is used to render the scene. This will be used for a number of initialization procedures.

#### `protected std::shared_ptr< `[`GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store)` > `[`mGeometryStore`](#class_d_core_1_1_component_system_1_1_a_scene_a4082224d4bc85a7536a5f830a44bd446_1a4082224d4bc85a7536a5f830a44bd446) 

This GeometryStore is used to load meshes and push them to the GPU.

#### `protected std::shared_ptr< `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store)` > `[`mTextureStore`](#class_d_core_1_1_component_system_1_1_a_scene_a9f5432333052579e1af732c2ba94fd74_1a9f5432333052579e1af732c2ba94fd74) 

This TextureStore is used to load textures and push them to the GPU.

# class `DCore::ComponentSystem::Entity` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1acb936f29e029c3b30c4ccc7650c947f1)`() = default` | 
`public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1a98cfd91b991b7d3bb8b2fc7f24e4dd2e)`(entt::entity handle,`[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` * scene)` | 
`public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1afab6414e0547bfe960b89ca1c23d41ec)`(const `[`Entity`](#class_d_core_1_1_component_system_1_1_entity)` & other) = default` | 
`public template<>`  <br/>`inline T & `[`AddComponent`](#class_d_core_1_1_component_system_1_1_entity_1ad8789a86827f7345e2797c486c8dca45)`(Args &&... args)` | 
`public template<>`  <br/>`inline T & `[`GetComponent`](#class_d_core_1_1_component_system_1_1_entity_1a05808563c4d05800d7c0457242c52ee5)`()` | 
`public template<>`  <br/>`inline bool `[`HasComponent`](#class_d_core_1_1_component_system_1_1_entity_1a1ede6081b5206eda708b1415bb84e443)`()` | 
`public template<>`  <br/>`inline void `[`RemoveComponent`](#class_d_core_1_1_component_system_1_1_entity_1ac1658cd4ec4255578fb62db5b221be9a)`()` | 
`public inline  `[`operator bool`](#class_d_core_1_1_component_system_1_1_entity_1ac773c550e4e756439c1b83f515217c7f)`() const` | 

## Members

#### `public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1acb936f29e029c3b30c4ccc7650c947f1)`() = default` 

#### `public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1a98cfd91b991b7d3bb8b2fc7f24e4dd2e)`(entt::entity handle,`[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` * scene)` 

#### `public  `[`Entity`](#class_d_core_1_1_component_system_1_1_entity_1afab6414e0547bfe960b89ca1c23d41ec)`(const `[`Entity`](#class_d_core_1_1_component_system_1_1_entity)` & other) = default` 

#### `public template<>`  <br/>`inline T & `[`AddComponent`](#class_d_core_1_1_component_system_1_1_entity_1ad8789a86827f7345e2797c486c8dca45)`(Args &&... args)` 

#### `public template<>`  <br/>`inline T & `[`GetComponent`](#class_d_core_1_1_component_system_1_1_entity_1a05808563c4d05800d7c0457242c52ee5)`()` 

#### `public template<>`  <br/>`inline bool `[`HasComponent`](#class_d_core_1_1_component_system_1_1_entity_1a1ede6081b5206eda708b1415bb84e443)`()` 

#### `public template<>`  <br/>`inline void `[`RemoveComponent`](#class_d_core_1_1_component_system_1_1_entity_1ac1658cd4ec4255578fb62db5b221be9a)`()` 

#### `public inline  `[`operator bool`](#class_d_core_1_1_component_system_1_1_entity_1ac773c550e4e756439c1b83f515217c7f)`() const` 

# class `DCore::ComponentSystem::SceneHandler` 

A [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) is the manager of the game engine. It implements the singleton pattern and provides getters for the current scene, the switch scene method and more.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double `[`mMouseX`](#class_d_core_1_1_component_system_1_1_scene_handler_1a388ec0d0e647d85b1cb2c0221ddf1ec4) | 
`public double `[`mMouseY`](#class_d_core_1_1_component_system_1_1_scene_handler_1acb98e23977a5ece85f87dba64a017f0f) | 
`public int `[`mWindowWidth`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab880ba91850afde1ff8fed38665b580b) | 
`public int `[`mWindowHeight`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab3c4aeda00c3dbc4c5171333f91f118c) | 
`public bool `[`mCatchCursor`](#class_d_core_1_1_component_system_1_1_scene_handler_1a9b3acb6989504f1a2bf5481a70be22b8) | 
`public float `[`mCameraMoveSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1a74130b184f9e156a60e286482b9554f7) | 
`public float `[`mCameraMoveSpeedFactor`](#class_d_core_1_1_component_system_1_1_scene_handler_1a51397713f8360ccd0e4a1e1db1889474) | 
`public float `[`mCameraTurnSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1ad24d09097b62570dfe704581470a1782) | 
`public float `[`mCameraScrollSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4b82dff4ae1b7e1655a1a2cfba500da5) | 
`public double `[`mMouseLastX`](#class_d_core_1_1_component_system_1_1_scene_handler_1a320a4ff364e796932ccfcac0cb1eb9b1) | 
`public double `[`mMouseLastY`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2e6a5792168acfa038f4e4238ec0449f) | 
`public double `[`mDoubleClickTime`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae347ad62363def0257f8fe1a5a22356b) | 
`public int `[`mClickCount`](#class_d_core_1_1_component_system_1_1_scene_handler_1aeab8b5887b4aad2619c0c8f2575d183c) | 
`public int `[`mClickButton`](#class_d_core_1_1_component_system_1_1_scene_handler_1a508252728d7b4b1694b0bfc49571e8a4) | 
`public glm::vec2 `[`mClickPos`](#class_d_core_1_1_component_system_1_1_scene_handler_1a3886340a8f142702a3e281fd81cbd1d2) | 
`public lava::Stopwatch `[`mClickTimer`](#class_d_core_1_1_component_system_1_1_scene_handler_1a6acc7a9aa834b0402cb4c6eadc99dfaf) | 
`public inline void `[`setupRenderer`](#class_d_core_1_1_component_system_1_1_scene_handler_a69831e2a027b2f7327db5e35bd326a0b_1a69831e2a027b2f7327db5e35bd326a0b)`(`[`RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base)` * renderer)` | If you want to supply a custom rendering system for rendering your scene, call this method after you have registered all scenes in your main.cc. You can take a look of the implementation of the default rendering system at RenderingSystem.cc
`public  `[`SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_a99fe4ea2e3e102ec3beeb448b6878cc5_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` | Creates a new instance of the scene handler. Should only be called ONCE by the main function.
`public  `[`~SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` | 
`public void `[`run`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` | 
`public void `[`updateCamera`](#class_d_core_1_1_component_system_1_1_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` | 

## Members

#### `public double `[`mMouseX`](#class_d_core_1_1_component_system_1_1_scene_handler_1a388ec0d0e647d85b1cb2c0221ddf1ec4) 

#### `public double `[`mMouseY`](#class_d_core_1_1_component_system_1_1_scene_handler_1acb98e23977a5ece85f87dba64a017f0f) 

#### `public int `[`mWindowWidth`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab880ba91850afde1ff8fed38665b580b) 

#### `public int `[`mWindowHeight`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab3c4aeda00c3dbc4c5171333f91f118c) 

#### `public bool `[`mCatchCursor`](#class_d_core_1_1_component_system_1_1_scene_handler_1a9b3acb6989504f1a2bf5481a70be22b8) 

#### `public float `[`mCameraMoveSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1a74130b184f9e156a60e286482b9554f7) 

#### `public float `[`mCameraMoveSpeedFactor`](#class_d_core_1_1_component_system_1_1_scene_handler_1a51397713f8360ccd0e4a1e1db1889474) 

#### `public float `[`mCameraTurnSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1ad24d09097b62570dfe704581470a1782) 

#### `public float `[`mCameraScrollSpeed`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4b82dff4ae1b7e1655a1a2cfba500da5) 

#### `public double `[`mMouseLastX`](#class_d_core_1_1_component_system_1_1_scene_handler_1a320a4ff364e796932ccfcac0cb1eb9b1) 

#### `public double `[`mMouseLastY`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2e6a5792168acfa038f4e4238ec0449f) 

#### `public double `[`mDoubleClickTime`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae347ad62363def0257f8fe1a5a22356b) 

#### `public int `[`mClickCount`](#class_d_core_1_1_component_system_1_1_scene_handler_1aeab8b5887b4aad2619c0c8f2575d183c) 

#### `public int `[`mClickButton`](#class_d_core_1_1_component_system_1_1_scene_handler_1a508252728d7b4b1694b0bfc49571e8a4) 

#### `public glm::vec2 `[`mClickPos`](#class_d_core_1_1_component_system_1_1_scene_handler_1a3886340a8f142702a3e281fd81cbd1d2) 

#### `public lava::Stopwatch `[`mClickTimer`](#class_d_core_1_1_component_system_1_1_scene_handler_1a6acc7a9aa834b0402cb4c6eadc99dfaf) 

#### `public inline void `[`setupRenderer`](#class_d_core_1_1_component_system_1_1_scene_handler_a69831e2a027b2f7327db5e35bd326a0b_1a69831e2a027b2f7327db5e35bd326a0b)`(`[`RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base)` * renderer)` 

If you want to supply a custom rendering system for rendering your scene, call this method after you have registered all scenes in your main.cc. You can take a look of the implementation of the default rendering system at RenderingSystem.cc

#### Parameters
* `renderer` The new renderer to use for the scene.

#### `public  `[`SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_a99fe4ea2e3e102ec3beeb448b6878cc5_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` 

Creates a new instance of the scene handler. Should only be called ONCE by the main function.

This should not be used to create a new instance. Instead, please use the GetInstance method.

This needs to be public in order to create a new instance using std::make_shared in the GetInstance method.

#### Returns
A new [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler)

#### `public  `[`~SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` 

#### `public void `[`run`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` 

#### `public void `[`updateCamera`](#class_d_core_1_1_component_system_1_1_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` 

# class `DCore::ComponentSystem::SystemBase` 

System base is the recommended method for accessing your entities and their components. The system originates from the core concept of ECS (entity component systems): You write custom components which can be assigned to entities. When you want to update those components (or want to read them), you have to create a system.

For this system you have to specify before hand, which components you try to access. For example, a RenderingSystem has to access the RenderComponent and the transform component of all entities. (If an entity doesn't provide both, we don't want to access it in our RenderingSystem). Thus, the actual rendering system in this engine implements: class RenderingSystemBase : public [SystemBase<RenderComponent, TransformComponent>](#class_d_core_1_1_component_system_1_1_system_base)

Now, in order to act on those selected entities we can implement one of the five methods: Awake, Start, Update, LateUpdate, Destroy. A registered system (see the Samples/Systems folder for an example) can now access the entities like this:

for each (auto entity in entities) auto& [renderer, transform] = entities.get<RenderComponent, TransformComponent>(entity);

Use this pattern to update your entities (i.e. their components) as you wish.

This pattern was chosen as it allows multithreading at a later point.

#### Parameters
* `firstType` The component you want to access

* `...Types` A list of components you need access to

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base_1a55e6c1c193abe2434cb778e3f1862e73)`() = default` | 
`public  `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base_1a801dc9c90b3542530e0d49e180609dfe)`(const `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base)` & other) = default` | 
`public inline virtual void `[`Awake`](#class_d_core_1_1_component_system_1_1_system_base_a26630b06b616740f618530f5e513dbdf_1a26630b06b616740f618530f5e513dbdf)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` | This method is called before the systems start method is called for all components already present in the scene.
`public inline virtual void `[`Start`](#class_d_core_1_1_component_system_1_1_system_base_a6154ab285d5099fa7ffaec1579142d95_1a6154ab285d5099fa7ffaec1579142d95)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` | This method is called on the systems start right before we enter the game loop for all components already present in the scene.
`public inline virtual void `[`Update`](#class_d_core_1_1_component_system_1_1_system_base_a6163c11e3bb5ed83b0e9146f99cf7641_1a6163c11e3bb5ed83b0e9146f99cf7641)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` | This method is called in every game logic update for all components already present in the scene.
`public inline virtual void `[`LateUpdate`](#class_d_core_1_1_component_system_1_1_system_base_a930ba30bf734f81b45f8feb141d2a939_1a930ba30bf734f81b45f8feb141d2a939)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` | This method is called in every game logic update right after the physics has been updated for all components already present in the scene.
`public inline virtual void `[`Destroy`](#class_d_core_1_1_component_system_1_1_system_base_ad5243d0dd5378e3bb987b00780189c57_1ad5243d0dd5378e3bb987b00780189c57)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` | This method is called right before application shutdown. Use this to clean up your systems when they need component access.
`protected inline auto `[`GetEntitiesFromRegistry`](#class_d_core_1_1_component_system_1_1_system_base_a6d6c8a31b3d0c65674a46a94b2995395_1a6d6c8a31b3d0c65674a46a94b2995395)`(entt::registry & reg)` | Returns a view for a given registry for this system.

## Members

#### `public  `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base_1a55e6c1c193abe2434cb778e3f1862e73)`() = default` 

#### `public  `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base_1a801dc9c90b3542530e0d49e180609dfe)`(const `[`SystemBase`](#class_d_core_1_1_component_system_1_1_system_base)` & other) = default` 

#### `public inline virtual void `[`Awake`](#class_d_core_1_1_component_system_1_1_system_base_a26630b06b616740f618530f5e513dbdf_1a26630b06b616740f618530f5e513dbdf)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` 

This method is called before the systems start method is called for all components already present in the scene.

#### Parameters
* `entities` A view on the entities that match the systems component selection.

#### `public inline virtual void `[`Start`](#class_d_core_1_1_component_system_1_1_system_base_a6154ab285d5099fa7ffaec1579142d95_1a6154ab285d5099fa7ffaec1579142d95)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` 

This method is called on the systems start right before we enter the game loop for all components already present in the scene.

#### Parameters
* `entities` A view on the entities that match the systems component selection.

#### `public inline virtual void `[`Update`](#class_d_core_1_1_component_system_1_1_system_base_a6163c11e3bb5ed83b0e9146f99cf7641_1a6163c11e3bb5ed83b0e9146f99cf7641)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` 

This method is called in every game logic update for all components already present in the scene.

#### Parameters
* `entities` A view on the entities that match the systems component selection.

#### `public inline virtual void `[`LateUpdate`](#class_d_core_1_1_component_system_1_1_system_base_a930ba30bf734f81b45f8feb141d2a939_1a930ba30bf734f81b45f8feb141d2a939)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` 

This method is called in every game logic update right after the physics has been updated for all components already present in the scene.

#### Parameters
* `entities` A view on the entities that match the systems component selection.

#### `public inline virtual void `[`Destroy`](#class_d_core_1_1_component_system_1_1_system_base_ad5243d0dd5378e3bb987b00780189c57_1ad5243d0dd5378e3bb987b00780189c57)`(entt::basic_view< entt::entity, entt::exclude_t<>, firstType, Types... > entities)` 

This method is called right before application shutdown. Use this to clean up your systems when they need component access.

#### Parameters
* `entities` A view on the entities that match the systems component selection.

#### `protected inline auto `[`GetEntitiesFromRegistry`](#class_d_core_1_1_component_system_1_1_system_base_a6d6c8a31b3d0c65674a46a94b2995395_1a6d6c8a31b3d0c65674a46a94b2995395)`(entt::registry & reg)` 

Returns a view for a given registry for this system.

#### Parameters
* `reg` The registry to pull entities from

#### Returns
A view of the entities present in the registry

# struct `DCore::ComponentSystem::TagComponent` 

This component stores the name and the tags of the entity.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string `[`Tag`](#struct_d_core_1_1_component_system_1_1_tag_component_aa2d577fb388ecc8de6bb8838ab165eb3_1aa2d577fb388ecc8de6bb8838ab165eb3) | The name of the entity this component is attatched to.
`public  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a2917aceebe478962f7d33eaef20ab3c5)`() = default` | 
`public  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a042301972f8f3436968ea3f9382e25f4)`(const `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component)` &) = default` | 
`public inline  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a6d2dd7e072bd152fca6744af3f72c500)`(const std::string & tag)` | 

## Members

#### `public std::string `[`Tag`](#struct_d_core_1_1_component_system_1_1_tag_component_aa2d577fb388ecc8de6bb8838ab165eb3_1aa2d577fb388ecc8de6bb8838ab165eb3) 

The name of the entity this component is attatched to.

#### `public  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a2917aceebe478962f7d33eaef20ab3c5)`() = default` 

#### `public  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a042301972f8f3436968ea3f9382e25f4)`(const `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component)` &) = default` 

#### `public inline  `[`TagComponent`](#struct_d_core_1_1_component_system_1_1_tag_component_1a6d2dd7e072bd152fca6744af3f72c500)`(const std::string & tag)` 

# struct `DCore::ComponentSystem::TransformComponent` 

This class is a part of each GameObject which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::vec3 `[`position`](#struct_d_core_1_1_component_system_1_1_transform_component_ad2c6b7ac29840c51a5af3ddac6056c9d_1ad2c6b7ac29840c51a5af3ddac6056c9d) | The position of the Transform and the corresponding GameObject
`public glm::vec3 `[`rotation`](#struct_d_core_1_1_component_system_1_1_transform_component_a989597d2302d2a70e1100a8a8c89fda5_1a989597d2302d2a70e1100a8a8c89fda5) | The rotation of the Transform and the corresponding GameObject
`public glm::vec3 `[`scale`](#struct_d_core_1_1_component_system_1_1_transform_component_a237ba1c0072b88eca97676fab599908c_1a237ba1c0072b88eca97676fab599908c) | The scale value of the Transform and the corresponding GameObject
`public  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1a0e4d8f7e3f897da744934193ae961c18)`() = default` | 
`public  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1a7d0052b25cafb3ed7860b64d4c028e6f)`(const `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` &) = default` | 
`public inline  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1ae2f5a4e10abd69c2686193bed8954022)`(const glm::vec3 & pos,const glm::vec3 & rot,const glm::vec3 &)` | 
`public glm::mat4 `[`getModelMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_a5fc531fdaba497dfb2013edce34cb094_1a5fc531fdaba497dfb2013edce34cb094)`()` | This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).
`public glm::mat4 `[`getScaleMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_a44f46dc4d93527e5d971dadf1f4d75b2_1a44f46dc4d93527e5d971dadf1f4d75b2)`()` | This method returns a matrix that scales the object using this Transform
`public glm::mat4 `[`getRotationMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_abf71ce5f341d605fb72c120733728320_1abf71ce5f341d605fb72c120733728320)`()` | This method returns a matrix that rotates the object using this Transform
`public glm::mat4 `[`getPosMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_ad27ecc8cd01fdf0bae5364c13132cf5b_1ad27ecc8cd01fdf0bae5364c13132cf5b)`()` | This method returns a matrix that positions the object using this Transform

## Members

#### `public glm::vec3 `[`position`](#struct_d_core_1_1_component_system_1_1_transform_component_ad2c6b7ac29840c51a5af3ddac6056c9d_1ad2c6b7ac29840c51a5af3ddac6056c9d) 

The position of the Transform and the corresponding GameObject

#### `public glm::vec3 `[`rotation`](#struct_d_core_1_1_component_system_1_1_transform_component_a989597d2302d2a70e1100a8a8c89fda5_1a989597d2302d2a70e1100a8a8c89fda5) 

The rotation of the Transform and the corresponding GameObject

#### `public glm::vec3 `[`scale`](#struct_d_core_1_1_component_system_1_1_transform_component_a237ba1c0072b88eca97676fab599908c_1a237ba1c0072b88eca97676fab599908c) 

The scale value of the Transform and the corresponding GameObject

#### `public  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1a0e4d8f7e3f897da744934193ae961c18)`() = default` 

#### `public  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1a7d0052b25cafb3ed7860b64d4c028e6f)`(const `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` &) = default` 

#### `public inline  `[`TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component_1ae2f5a4e10abd69c2686193bed8954022)`(const glm::vec3 & pos,const glm::vec3 & rot,const glm::vec3 &)` 

#### `public glm::mat4 `[`getModelMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_a5fc531fdaba497dfb2013edce34cb094_1a5fc531fdaba497dfb2013edce34cb094)`()` 

This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).

#### Returns
Model matrix (with parent transform)

#### `public glm::mat4 `[`getScaleMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_a44f46dc4d93527e5d971dadf1f4d75b2_1a44f46dc4d93527e5d971dadf1f4d75b2)`()` 

This method returns a matrix that scales the object using this Transform

#### Returns
The scale matrix

#### `public glm::mat4 `[`getRotationMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_abf71ce5f341d605fb72c120733728320_1abf71ce5f341d605fb72c120733728320)`()` 

This method returns a matrix that rotates the object using this Transform

#### Returns
The rotation matrix

#### `public glm::mat4 `[`getPosMatrix`](#struct_d_core_1_1_component_system_1_1_transform_component_ad27ecc8cd01fdf0bae5364c13132cf5b_1ad27ecc8cd01fdf0bae5364c13132cf5b)`()` 

This method returns a matrix that positions the object using this Transform

#### Returns
The position matrix

# namespace `DCore::Example` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::Example::DreamroamScene`](#class_d_core_1_1_example_1_1_dreamroam_scene) | 

# class `DCore::Example::DreamroamScene` 

```
class DCore::Example::DreamroamScene
  : public DCore::ComponentSystem::AScene
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`DreamroamScene`](#class_d_core_1_1_example_1_1_dreamroam_scene_1a3f97df4276fb8232c9349144bfbbf242)`()` | 
`public virtual void `[`start`](#class_d_core_1_1_example_1_1_dreamroam_scene_a471fd303a4708b08d3a4ea4c6f6bfe18_1a471fd303a4708b08d3a4ea4c6f6bfe18)`()` | This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.
`public virtual void `[`update`](#class_d_core_1_1_example_1_1_dreamroam_scene_a317a513962ec27b9f8e170335e8da419_1a317a513962ec27b9f8e170335e8da419)`(double dt)` | This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

## Members

#### `public  `[`DreamroamScene`](#class_d_core_1_1_example_1_1_dreamroam_scene_1a3f97df4276fb8232c9349144bfbbf242)`()` 

#### `public virtual void `[`start`](#class_d_core_1_1_example_1_1_dreamroam_scene_a471fd303a4708b08d3a4ea4c6f6bfe18_1a471fd303a4708b08d3a4ea4c6f6bfe18)`()` 

This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.

#### `public virtual void `[`update`](#class_d_core_1_1_example_1_1_dreamroam_scene_a317a513962ec27b9f8e170335e8da419_1a317a513962ec27b9f8e170335e8da419)`(double dt)` 

This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

#### Parameters
* `dt` Delta Time of the frame in seconds

# namespace `DCore::Meshes` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::Meshes::Geometry`](#class_d_core_1_1_meshes_1_1_geometry) | TODO replace this by a mesh component we can attatch to an entity...
`class `[`DCore::Meshes::GeometryLoader`](#class_d_core_1_1_meshes_1_1_geometry_loader) | 
`class `[`DCore::Meshes::GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store) | 

# class `DCore::Meshes::Geometry` 

TODO replace this by a mesh component we can attatch to an entity...

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry_1a6194151def9f47dda17d29e7a3ab48e3)`(const lava::geometry::SharedGeometry geometry)` | 
`public void `[`draw`](#class_d_core_1_1_meshes_1_1_geometry_1a56c1551d1f2ff3c8addad25d1a7ba9e2)`(lava::InlineSubpass & pass)` | 

## Members

#### `public  `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry_1a6194151def9f47dda17d29e7a3ab48e3)`(const lava::geometry::SharedGeometry geometry)` 

#### `public void `[`draw`](#class_d_core_1_1_meshes_1_1_geometry_1a56c1551d1f2ff3c8addad25d1a7ba9e2)`(lava::InlineSubpass & pass)` 

# class `DCore::Meshes::GeometryLoader` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`GeometryLoader`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a097298280328323f2f19bf8c5339c010)`()` | 
`public void `[`loadRawMulti`](#class_d_core_1_1_meshes_1_1_geometry_loader_a778d9b368691d4d914df2b5a509ca519_1a778d9b368691d4d914df2b5a509ca519)`(const std::string & filename,std::vector< std::vector< `[`VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes)` >> & verticesPerMesh,std::vector< std::vector< uint32_t >> & indicesPerMesh,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | Loads all meshes inside the given file separated and stores the vertex data and indices inside the given vectors. 'verticesPerMesh' and 'indicesPerMesh' will first be cleared, then filled with the data read from the file.
`public void `[`loadRawCombined`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a69bf2b6698454ac329e5cc129270c9fb)`(const std::string & filename,std::vector< `[`VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes)` > & vertices,std::vector< uint32_t > & indices)` | 
`public std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`meshesFromFile`](#class_d_core_1_1_meshes_1_1_geometry_loader_1aee8401497ae0d8d3eec0b9e218345b43)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | 
`public std::shared_ptr< lava::geometry::GeometryData > `[`singleMeshFromFile`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a0fdf81e745398fb778858ddf0a356284)`(const std::string & filename)` | 
`public template<>`  <br/>`inline std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`loadMulti`](#class_d_core_1_1_meshes_1_1_geometry_loader_1ae6dda85797038b69f530dc0863433c49)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | 
`public template<>`  <br/>`inline std::shared_ptr< lava::geometry::GeometryData > `[`loadCombined`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a466f8072deb544a2e9c3c43ab7cd312e)`(std::string const & filename)` | 
`public void `[`printNodeInfo_recursive`](#class_d_core_1_1_meshes_1_1_geometry_loader_1ac43feebbb35daa031a603d45255bebbd)`(const aiScene * scene,const aiNode * node) const` | 
`public void `[`printSceneInfo`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a5039e0f522233669e33cb09f1038fec4)`(const aiScene * scene) const` | 
`typedef `[`VertexCB`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a9fa7f7511b84143b29043564265c6ccd) | 

## Members

#### `public  `[`GeometryLoader`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a097298280328323f2f19bf8c5339c010)`()` 

#### `public void `[`loadRawMulti`](#class_d_core_1_1_meshes_1_1_geometry_loader_a778d9b368691d4d914df2b5a509ca519_1a778d9b368691d4d914df2b5a509ca519)`(const std::string & filename,std::vector< std::vector< `[`VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes)` >> & verticesPerMesh,std::vector< std::vector< uint32_t >> & indicesPerMesh,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

Loads all meshes inside the given file separated and stores the vertex data and indices inside the given vectors. 'verticesPerMesh' and 'indicesPerMesh' will first be cleared, then filled with the data read from the file.

#### `public void `[`loadRawCombined`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a69bf2b6698454ac329e5cc129270c9fb)`(const std::string & filename,std::vector< `[`VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes)` > & vertices,std::vector< uint32_t > & indices)` 

#### `public std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`meshesFromFile`](#class_d_core_1_1_meshes_1_1_geometry_loader_1aee8401497ae0d8d3eec0b9e218345b43)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

#### `public std::shared_ptr< lava::geometry::GeometryData > `[`singleMeshFromFile`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a0fdf81e745398fb778858ddf0a356284)`(const std::string & filename)` 

#### `public template<>`  <br/>`inline std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`loadMulti`](#class_d_core_1_1_meshes_1_1_geometry_loader_1ae6dda85797038b69f530dc0863433c49)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

#### `public template<>`  <br/>`inline std::shared_ptr< lava::geometry::GeometryData > `[`loadCombined`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a466f8072deb544a2e9c3c43ab7cd312e)`(std::string const & filename)` 

#### `public void `[`printNodeInfo_recursive`](#class_d_core_1_1_meshes_1_1_geometry_loader_1ac43feebbb35daa031a603d45255bebbd)`(const aiScene * scene,const aiNode * node) const` 

#### `public void `[`printSceneInfo`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a5039e0f522233669e33cb09f1038fec4)`(const aiScene * scene) const` 

#### `typedef `[`VertexCB`](#class_d_core_1_1_meshes_1_1_geometry_loader_1a9fa7f7511b84143b29043564265c6ccd) 

# class `DCore::Meshes::GeometryStore` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store_1a5bea5cb9e95e210d501fd8541c06c2d6)`(lava::SharedDevice device)` | 
`public void `[`registerGeometry`](#class_d_core_1_1_meshes_1_1_geometry_store_1a662ad163346b390a48862e9f7a06395d)`(std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > obj,std::string name)` | 
`public void `[`registerGeometryFromData`](#class_d_core_1_1_meshes_1_1_geometry_store_1a1902b5f6784925acca46a53933ac34f5)`(lava::geometry::SharedGeometryData geomData,std::string name)` | 
`public void `[`registerGeometryFromFileSingle`](#class_d_core_1_1_meshes_1_1_geometry_store_1a9b890cdf2a66a42f4b0770f526b0385a)`(std::string filePath,std::string name)` | 
`public void `[`registerGeometryFromFileMulti`](#class_d_core_1_1_meshes_1_1_geometry_store_1ac1a8882862871bce334a6be7f6fe873f)`(std::string filePath,std::string namePrefix)` | 
`public inline std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`getGeometryWithName`](#class_d_core_1_1_meshes_1_1_geometry_store_1a5e81a215a5180312692fad90747e5d05)`(std::string name) const` | 
`public inline size_t `[`getLayerCountWithName`](#class_d_core_1_1_meshes_1_1_geometry_store_1ac350ae57e0d99ba0498bfae929e4694a)`(std::string name) const` | 

## Members

#### `public  `[`GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store_1a5bea5cb9e95e210d501fd8541c06c2d6)`(lava::SharedDevice device)` 

#### `public void `[`registerGeometry`](#class_d_core_1_1_meshes_1_1_geometry_store_1a662ad163346b390a48862e9f7a06395d)`(std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > obj,std::string name)` 

#### `public void `[`registerGeometryFromData`](#class_d_core_1_1_meshes_1_1_geometry_store_1a1902b5f6784925acca46a53933ac34f5)`(lava::geometry::SharedGeometryData geomData,std::string name)` 

#### `public void `[`registerGeometryFromFileSingle`](#class_d_core_1_1_meshes_1_1_geometry_store_1a9b890cdf2a66a42f4b0770f526b0385a)`(std::string filePath,std::string name)` 

#### `public void `[`registerGeometryFromFileMulti`](#class_d_core_1_1_meshes_1_1_geometry_store_1ac1a8882862871bce334a6be7f6fe873f)`(std::string filePath,std::string namePrefix)` 

#### `public inline std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`getGeometryWithName`](#class_d_core_1_1_meshes_1_1_geometry_store_1a5e81a215a5180312692fad90747e5d05)`(std::string name) const` 

#### `public inline size_t `[`getLayerCountWithName`](#class_d_core_1_1_meshes_1_1_geometry_store_1ac350ae57e0d99ba0498bfae929e4694a)`(std::string name) const` 

# namespace `DCore::Rendering` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::Rendering::DefaultRenderer`](#class_d_core_1_1_rendering_1_1_default_renderer) | Renderer for non-textured meshes.
`class `[`DCore::Rendering::DefaultTexturedRenderer`](#class_d_core_1_1_rendering_1_1_default_textured_renderer) | Renderer for textured objects.
`class `[`DCore::Rendering::GraphicsPipelineFactory`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_factory) | Factory for all different renderers.
`class `[`DCore::Rendering::RendererBase`](#class_d_core_1_1_rendering_1_1_renderer_base) | 
`class `[`DCore::Rendering::RenderingSystem`](#class_d_core_1_1_rendering_1_1_rendering_system) | 
`class `[`DCore::Rendering::RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base) | 
`struct `[`DCore::Rendering::CameraDataForwardPass`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass) | 
`struct `[`DCore::Rendering::CameraDataPrePass`](#struct_d_core_1_1_rendering_1_1_camera_data_pre_pass) | 
`struct `[`DCore::Rendering::PushConstants`](#struct_d_core_1_1_rendering_1_1_push_constants) | 
`struct `[`DCore::Rendering::RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component) | 
`struct `[`DCore::Rendering::VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes) | 

# class `DCore::Rendering::DefaultRenderer` 

```
class DCore::Rendering::DefaultRenderer
  : public DCore::Rendering::RendererBase
```  

Renderer for non-textured meshes.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::DefaultTexturedRenderer` 

```
class DCore::Rendering::DefaultTexturedRenderer
  : public DCore::Rendering::RendererBase
```  

Renderer for textured objects.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::GraphicsPipelineFactory` 

Factory for all different renderers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::RendererBase` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`RendererBase`](#class_d_core_1_1_rendering_1_1_renderer_base_1a9f699892f39e527cb890b08e2a63350a)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` | 
`public inline virtual  `[`~RendererBase`](#class_d_core_1_1_rendering_1_1_renderer_base_1a2b519c9f7fe9a5a4e91f8672673c3392)`()` | 
`public void `[`prepareRendering`](#class_d_core_1_1_rendering_1_1_renderer_base_1a4655eafa1e009cc3c7013cadf53c3b6a)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` | 
`public void `[`renderGameObjects`](#class_d_core_1_1_rendering_1_1_renderer_base_1a9c04a907face2fc84897c52ce5defacc)`(const std::vector< std::tuple< `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component) &, [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` & >> & gos)` | 
`protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_d_core_1_1_rendering_1_1_renderer_base_1a5a3d4dae1f8db27b1eb02febce7ceac6) | 
`protected lava::SharedPipelineLayout `[`mLayout`](#class_d_core_1_1_rendering_1_1_renderer_base_1adec103350b3301f829b8e2e3d4b5b570) | 
`protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_d_core_1_1_rendering_1_1_renderer_base_1a4a2c90c6a5f206bf6ed375b8af438682) | 
`protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_d_core_1_1_rendering_1_1_renderer_base_1af787cca69c878dff46caf4de8fe0a7e9) | 
`protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_d_core_1_1_rendering_1_1_renderer_base_1ac6a53352d37a9226d9d92193f20d081d) | 

## Members

#### `public  explicit `[`RendererBase`](#class_d_core_1_1_rendering_1_1_renderer_base_1a9f699892f39e527cb890b08e2a63350a)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` 

#### `public inline virtual  `[`~RendererBase`](#class_d_core_1_1_rendering_1_1_renderer_base_1a2b519c9f7fe9a5a4e91f8672673c3392)`()` 

#### `public void `[`prepareRendering`](#class_d_core_1_1_rendering_1_1_renderer_base_1a4655eafa1e009cc3c7013cadf53c3b6a)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` 

#### `public void `[`renderGameObjects`](#class_d_core_1_1_rendering_1_1_renderer_base_1a9c04a907face2fc84897c52ce5defacc)`(const std::vector< std::tuple< `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component) &, [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` & >> & gos)` 

#### `protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_d_core_1_1_rendering_1_1_renderer_base_1a5a3d4dae1f8db27b1eb02febce7ceac6) 

#### `protected lava::SharedPipelineLayout `[`mLayout`](#class_d_core_1_1_rendering_1_1_renderer_base_1adec103350b3301f829b8e2e3d4b5b570) 

#### `protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_d_core_1_1_rendering_1_1_renderer_base_1a4a2c90c6a5f206bf6ed375b8af438682) 

#### `protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_d_core_1_1_rendering_1_1_renderer_base_1af787cca69c878dff46caf4de8fe0a7e9) 

#### `protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_d_core_1_1_rendering_1_1_renderer_base_1ac6a53352d37a9226d9d92193f20d081d) 

# class `DCore::Rendering::RenderingSystem` 

```
class DCore::Rendering::RenderingSystem
  : public DCore::Rendering::RenderingSystemBase
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`RenderingSystem`](#class_d_core_1_1_rendering_1_1_rendering_system_1ab0b874c6310b97f7b51cff12ed76d963)`(lava::SharedDevice device,lava::SharedDescriptorSetLayout textureLayout,std::shared_ptr< lava::features::GlfwOutput > glfwOutput,std::shared_ptr< lava::features::GlfwWindow > glfwWindow)` | 
`public  `[`~RenderingSystem`](#class_d_core_1_1_rendering_1_1_rendering_system_1adfc9c721f1646e7167176c54081c626b)`() = default` | 
`public virtual void `[`Render`](#class_d_core_1_1_rendering_1_1_rendering_system_1a9f58f44334c6da2163f7ab4d48c93d2f)`(entt::basic_view< entt::entity, entt::exclude_t<>, `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component), [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` > entities)` | 
`public virtual void `[`Resize`](#class_d_core_1_1_rendering_1_1_rendering_system_1a695964cbc4dd8a98ca904246e126285d)`(int width,int height)` | 
`public inline virtual lava::camera::SharedGenericCamera `[`getCamera`](#class_d_core_1_1_rendering_1_1_rendering_system_1a5933b8a6f5def4c8accc7a9526f0a891)`()` | 

## Members

#### `public  `[`RenderingSystem`](#class_d_core_1_1_rendering_1_1_rendering_system_1ab0b874c6310b97f7b51cff12ed76d963)`(lava::SharedDevice device,lava::SharedDescriptorSetLayout textureLayout,std::shared_ptr< lava::features::GlfwOutput > glfwOutput,std::shared_ptr< lava::features::GlfwWindow > glfwWindow)` 

#### `public  `[`~RenderingSystem`](#class_d_core_1_1_rendering_1_1_rendering_system_1adfc9c721f1646e7167176c54081c626b)`() = default` 

#### `public virtual void `[`Render`](#class_d_core_1_1_rendering_1_1_rendering_system_1a9f58f44334c6da2163f7ab4d48c93d2f)`(entt::basic_view< entt::entity, entt::exclude_t<>, `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component), [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` > entities)` 

#### `public virtual void `[`Resize`](#class_d_core_1_1_rendering_1_1_rendering_system_1a695964cbc4dd8a98ca904246e126285d)`(int width,int height)` 

#### `public inline virtual lava::camera::SharedGenericCamera `[`getCamera`](#class_d_core_1_1_rendering_1_1_rendering_system_1a5933b8a6f5def4c8accc7a9526f0a891)`()` 

# class `DCore::Rendering::RenderingSystemBase` 

```
class DCore::Rendering::RenderingSystemBase
  : public DCore::ComponentSystem::SystemBase< RenderComponent, TransformComponent >
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1aa52b303b528e5a6cd0b3b6ee372703af)`() = default` | 
`public  `[`~RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a7c1565deddfb104ecbead1d74bd702d3)`() = default` | 
`public inline virtual void `[`Render`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a9cc52a8e2c5c8081e81ce966d8f0a392)`(entt::basic_view< entt::entity, entt::exclude_t<>, `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component), [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` > entities)` | 
`public inline virtual void `[`Resize`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a1e8b533abea3279d1123c0590945e103)`(int width,int height)` | 
`public lava::camera::SharedGenericCamera `[`getCamera`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1ab3dbd250ceeb66e06691a9568f35347a)`()` | 

## Members

#### `public  `[`RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1aa52b303b528e5a6cd0b3b6ee372703af)`() = default` 

#### `public  `[`~RenderingSystemBase`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a7c1565deddfb104ecbead1d74bd702d3)`() = default` 

#### `public inline virtual void `[`Render`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a9cc52a8e2c5c8081e81ce966d8f0a392)`(entt::basic_view< entt::entity, entt::exclude_t<>, `[`RenderComponent](#struct_d_core_1_1_rendering_1_1_render_component), [TransformComponent`](#struct_d_core_1_1_component_system_1_1_transform_component)` > entities)` 

#### `public inline virtual void `[`Resize`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1a1e8b533abea3279d1123c0590945e103)`(int width,int height)` 

#### `public lava::camera::SharedGenericCamera `[`getCamera`](#class_d_core_1_1_rendering_1_1_rendering_system_base_1ab3dbd250ceeb66e06691a9568f35347a)`()` 

# struct `DCore::Rendering::CameraDataForwardPass` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1a81b73f7789379525bc60d8541219a3e8) | 
`public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1af9d78361a47f9bf883f710290755217d) | 
`public glm::mat4 `[`depthViewProj`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1a6b65115124d2e27707d42c2b40adc395) | 

## Members

#### `public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1a81b73f7789379525bc60d8541219a3e8) 

#### `public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1af9d78361a47f9bf883f710290755217d) 

#### `public glm::mat4 `[`depthViewProj`](#struct_d_core_1_1_rendering_1_1_camera_data_forward_pass_1a6b65115124d2e27707d42c2b40adc395) 

# struct `DCore::Rendering::CameraDataPrePass` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_pre_pass_1a08a2bcd62327385eb8fa81b8123fb48c) | 
`public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_pre_pass_1ab0f4f21f2f8e6fb0488717c256c2771d) | 

## Members

#### `public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_pre_pass_1a08a2bcd62327385eb8fa81b8123fb48c) 

#### `public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_pre_pass_1ab0f4f21f2f8e6fb0488717c256c2771d) 

# struct `DCore::Rendering::PushConstants` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`modelMatrix`](#struct_d_core_1_1_rendering_1_1_push_constants_1ac0e8d9d8b1e639ac008ec2fb64b13f9f) | 
`public glm::mat4 `[`normalMatrix`](#struct_d_core_1_1_rendering_1_1_push_constants_1ad0dec15549923449556f6e387662f4a7) | 
`public float `[`alpha`](#struct_d_core_1_1_rendering_1_1_push_constants_1af4067f3e621905807715999c13c6e23c) | 

## Members

#### `public glm::mat4 `[`modelMatrix`](#struct_d_core_1_1_rendering_1_1_push_constants_1ac0e8d9d8b1e639ac008ec2fb64b13f9f) 

#### `public glm::mat4 `[`normalMatrix`](#struct_d_core_1_1_rendering_1_1_push_constants_1ad0dec15549923449556f6e387662f4a7) 

#### `public float `[`alpha`](#struct_d_core_1_1_rendering_1_1_push_constants_1af4067f3e621905807715999c13c6e23c) 

# struct `DCore::Rendering::RenderComponent` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`geometryObj`](#struct_d_core_1_1_rendering_1_1_render_component_1ab190779cef11ac91643794aa45c0eb7c) | 
`public bool `[`isTransparent`](#struct_d_core_1_1_rendering_1_1_render_component_1a87502c4beef243b5001230e3b6d104c4) | 
`public float `[`alpha`](#struct_d_core_1_1_rendering_1_1_render_component_1ae87276ea190b0a0c2b60db8660e8756a) | 
`public bool `[`hasTexture`](#struct_d_core_1_1_rendering_1_1_render_component_1a9dd4f0c107796c782907854be93da99d) | 
`public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`textureObj`](#struct_d_core_1_1_rendering_1_1_render_component_1ae93e32ef17a8995c67da847b4f55cd3d) | 
`public bool `[`active`](#struct_d_core_1_1_rendering_1_1_render_component_1a26108e27e96ac2fcca425d78523755c6) | 
`public bool `[`isThrowingShadow`](#struct_d_core_1_1_rendering_1_1_render_component_1a47667f32b2a4fd01b6930601a93af516) | 
`public  `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component_1a27a1adb9bcc2e56182341ae3b0b24b8b)`() = default` | 
`public  `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component_1af0de77deb283e9512a7c66ea85b6d594)`(const `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component)` &) = default` | 

## Members

#### `public std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`geometryObj`](#struct_d_core_1_1_rendering_1_1_render_component_1ab190779cef11ac91643794aa45c0eb7c) 

#### `public bool `[`isTransparent`](#struct_d_core_1_1_rendering_1_1_render_component_1a87502c4beef243b5001230e3b6d104c4) 

#### `public float `[`alpha`](#struct_d_core_1_1_rendering_1_1_render_component_1ae87276ea190b0a0c2b60db8660e8756a) 

#### `public bool `[`hasTexture`](#struct_d_core_1_1_rendering_1_1_render_component_1a9dd4f0c107796c782907854be93da99d) 

#### `public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`textureObj`](#struct_d_core_1_1_rendering_1_1_render_component_1ae93e32ef17a8995c67da847b4f55cd3d) 

#### `public bool `[`active`](#struct_d_core_1_1_rendering_1_1_render_component_1a26108e27e96ac2fcca425d78523755c6) 

#### `public bool `[`isThrowingShadow`](#struct_d_core_1_1_rendering_1_1_render_component_1a47667f32b2a4fd01b6930601a93af516) 

#### `public  `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component_1a27a1adb9bcc2e56182341ae3b0b24b8b)`() = default` 

#### `public  `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component_1af0de77deb283e9512a7c66ea85b6d594)`(const `[`RenderComponent`](#struct_d_core_1_1_rendering_1_1_render_component)` &) = default` 

# struct `DCore::Rendering::VertexAttributes` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::vec3 `[`position`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a2e87efb197fe42ff688b35f569e2c9ea) | 
`public glm::vec3 `[`normal`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a6ea07acb851c810fd8684a4d814d5b11) | 
`public glm::vec3 `[`tangent`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a9e69b68ce185ee6c7a35260978f59e1a) | 
`public glm::vec2 `[`texCoord`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1ac01983f6fa3dc329a7c1059c0757e39f) | 
`public glm::vec4 `[`color`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a09b46e8a31766d17b5d0c91422542e56) | 

## Members

#### `public glm::vec3 `[`position`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a2e87efb197fe42ff688b35f569e2c9ea) 

#### `public glm::vec3 `[`normal`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a6ea07acb851c810fd8684a4d814d5b11) 

#### `public glm::vec3 `[`tangent`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a9e69b68ce185ee6c7a35260978f59e1a) 

#### `public glm::vec2 `[`texCoord`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1ac01983f6fa3dc329a7c1059c0757e39f) 

#### `public glm::vec4 `[`color`](#struct_d_core_1_1_rendering_1_1_vertex_attributes_1a09b46e8a31766d17b5d0c91422542e56) 

# namespace `DCore::Textures` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::Textures::Texture`](#class_d_core_1_1_textures_1_1_texture) | 
`class `[`DCore::Textures::TextureStore`](#class_d_core_1_1_textures_1_1_texture_store) | 

# class `DCore::Textures::Texture` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Texture`](#class_d_core_1_1_textures_1_1_texture_1a1c4d733f622ba2cf092cdd2d37fa8ad9)`(lava::SharedDescriptorSet descriptorSet)` | 
`public inline lava::SharedDescriptorSet `[`getDescriptorSet`](#class_d_core_1_1_textures_1_1_texture_1afacd53253f78611dabcbbdc1582a1368)`()` | 

## Members

#### `public  `[`Texture`](#class_d_core_1_1_textures_1_1_texture_1a1c4d733f622ba2cf092cdd2d37fa8ad9)`(lava::SharedDescriptorSet descriptorSet)` 

#### `public inline lava::SharedDescriptorSet `[`getDescriptorSet`](#class_d_core_1_1_textures_1_1_texture_1afacd53253f78611dabcbbdc1582a1368)`()` 

# class `DCore::Textures::TextureStore` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a5faa7af45ca80f42d80c38ee6f45531a)`(lava::SharedDevice device)` | 
`public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a896214fbe95e96b69382764136d1dbd5)`(lava::SharedDevice device,std::vector< std::pair< std::string, std::string >> imageTexturePathsAndNames)` | 
`public  `[`~TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a15a3cccbdaf62d8ae70d403b851704a2)`()` | 
`public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`getTextureWithName`](#class_d_core_1_1_textures_1_1_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` | 
`public lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_d_core_1_1_textures_1_1_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` | 

## Members

#### `public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a5faa7af45ca80f42d80c38ee6f45531a)`(lava::SharedDevice device)` 

#### `public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a896214fbe95e96b69382764136d1dbd5)`(lava::SharedDevice device,std::vector< std::pair< std::string, std::string >> imageTexturePathsAndNames)` 

#### `public  `[`~TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a15a3cccbdaf62d8ae70d403b851704a2)`()` 

#### `public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`getTextureWithName`](#class_d_core_1_1_textures_1_1_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` 

#### `public lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_d_core_1_1_textures_1_1_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` 

# namespace `lava::pipeline` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline) | A Forward+ Rendering Pipeline with post-processing support It provides features such as shadow mapping

# class `lava::pipeline::AdvancedRenderingPipeline` 

A Forward+ Rendering Pipeline with post-processing support It provides features such as shadow mapping

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public SharedDescriptorSetLayout `[`mForwardDescriptorLayout`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a9df04d252ad16fa802d458bf48b2dc48) | 
`public SharedDescriptorSet `[`mForwardDescriptor`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1aa9789650676c510c0c5ebe272810d6d7) | 
`public SharedDescriptorSetLayout `[`mOutputDescriptorLayout`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a2e30467f83a28a6f2cc36f1ad9ec6ac4) | 
`public SharedDescriptorSet `[`mOutputDescriptor`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ae8839e603a01d8d6c14a4ac61e0432af) | 
`public bool `[`mFXAA`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a0944cff1a82728e095dce8f847a1ac48) | 
`public bool `[`mTransparentPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a5000f6170c3b9ff7dc4959c2e87870ec) | 
`public float `[`mDitheringStrength`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a515092b1f232c134413c15b71b16c5d6) | 
`public SharedDevice `[`mDevice`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a44920d76276798f7e3ac017b8d8c41c5) | 
`public vk::Format `[`mOutputFormat`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a193a92c36ae1799653421d5fccdb29f7) | 
`public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1acac023a389b11bb0a2709bfab11443e9)`(Camera)` | 
`public  `[`LAVA_GETTER`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1acc3cf8cccdee40f52fbe1e7d1152bcb5)`(Width)` | 
`public  `[`LAVA_GETTER`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a3f22787e215a2bff65f48e40a0a0f7b2)`(Height)` | 
`public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ab352096587657c0fb4418e31d2849677)`(FXAA)` | 
`public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ab1115b74126dc5ebb051b924960f6048)`(DitheringStrength)` | 
`public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1af42a6c1dd9e414cd4325fa122753d193)`(TransparentPass)` | 
`public int `[`getOutputWidth`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ad439c6056eb3e4cf7643fa06e070673d)`() const` | 
`public int `[`getOutputHeight`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a3bc345d87a1cddef6991f177981c237a)`() const` | 
`public  `[`AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a2ef1d1c8071939c697856524624e8329)`(SharedDevice const & device,GenericFormat outputFormat)` | 
`public void `[`resize`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1af49d70314aa2dd31be69e908097a9c8e)`(int w,int h)` | Resizes the internal pipeline size.
`public void `[`assignCamera`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_a19caa69565b7b3d6211495bcf1ef9dfa_1a19caa69565b7b3d6211495bcf1ef9dfa)`(camera::SharedGenericCamera const & cam,bool useCamViewport)` | Updates the camera If useCamViewport is true, also resizes the pipeline
`public void `[`render`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_a51a5fe665107400269ce2eba976da1f8_1a51a5fe665107400269ce2eba976da1f8)`(lava::RecordingCommandBuffer & cmd,lava::SharedFramebuffer const & fbo,const std::function< void(lava::pipeline::AdvancedRenderPass const &pass)> & renderFunc)` | executes the whole rendering pipeline
`public inline SharedRenderPass const  & `[`outputPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1aa2be9635a6d0a5f575f13bf1714791e8)`() const` | Use this to create the FBOs for the Pipeline to output to.
`public inline SharedRenderPass const  & `[`prePass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a0cf45d26d2ad982caf4fc8f501595f5e)`() const` | Use this to create the Pipelines to render the shadow pass.
`public inline SharedRenderPass const  & `[`forwardPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1afbf56fa324abb5d2b20e34caf66cfaaf)`() const` | Use this to create the Pipelines to render the forward pass.

## Members

#### `public SharedDescriptorSetLayout `[`mForwardDescriptorLayout`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a9df04d252ad16fa802d458bf48b2dc48) 

#### `public SharedDescriptorSet `[`mForwardDescriptor`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1aa9789650676c510c0c5ebe272810d6d7) 

#### `public SharedDescriptorSetLayout `[`mOutputDescriptorLayout`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a2e30467f83a28a6f2cc36f1ad9ec6ac4) 

#### `public SharedDescriptorSet `[`mOutputDescriptor`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ae8839e603a01d8d6c14a4ac61e0432af) 

#### `public bool `[`mFXAA`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a0944cff1a82728e095dce8f847a1ac48) 

#### `public bool `[`mTransparentPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a5000f6170c3b9ff7dc4959c2e87870ec) 

#### `public float `[`mDitheringStrength`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a515092b1f232c134413c15b71b16c5d6) 

#### `public SharedDevice `[`mDevice`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a44920d76276798f7e3ac017b8d8c41c5) 

#### `public vk::Format `[`mOutputFormat`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a193a92c36ae1799653421d5fccdb29f7) 

#### `public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1acac023a389b11bb0a2709bfab11443e9)`(Camera)` 

#### `public  `[`LAVA_GETTER`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1acc3cf8cccdee40f52fbe1e7d1152bcb5)`(Width)` 

#### `public  `[`LAVA_GETTER`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a3f22787e215a2bff65f48e40a0a0f7b2)`(Height)` 

#### `public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ab352096587657c0fb4418e31d2849677)`(FXAA)` 

#### `public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ab1115b74126dc5ebb051b924960f6048)`(DitheringStrength)` 

#### `public  `[`LAVA_PROPERTY`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1af42a6c1dd9e414cd4325fa122753d193)`(TransparentPass)` 

#### `public int `[`getOutputWidth`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1ad439c6056eb3e4cf7643fa06e070673d)`() const` 

#### `public int `[`getOutputHeight`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a3bc345d87a1cddef6991f177981c237a)`() const` 

#### `public  `[`AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a2ef1d1c8071939c697856524624e8329)`(SharedDevice const & device,GenericFormat outputFormat)` 

#### `public void `[`resize`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1af49d70314aa2dd31be69e908097a9c8e)`(int w,int h)` 

Resizes the internal pipeline size.

#### `public void `[`assignCamera`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_a19caa69565b7b3d6211495bcf1ef9dfa_1a19caa69565b7b3d6211495bcf1ef9dfa)`(camera::SharedGenericCamera const & cam,bool useCamViewport)` 

Updates the camera If useCamViewport is true, also resizes the pipeline

#### `public void `[`render`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_a51a5fe665107400269ce2eba976da1f8_1a51a5fe665107400269ce2eba976da1f8)`(lava::RecordingCommandBuffer & cmd,lava::SharedFramebuffer const & fbo,const std::function< void(lava::pipeline::AdvancedRenderPass const &pass)> & renderFunc)` 

executes the whole rendering pipeline

#### Parameters
* `renderFunc` function to call for every renderpass. Use the provided pass information

#### `public inline SharedRenderPass const  & `[`outputPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1aa2be9635a6d0a5f575f13bf1714791e8)`() const` 

Use this to create the FBOs for the Pipeline to output to.

#### `public inline SharedRenderPass const  & `[`prePass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a0cf45d26d2ad982caf4fc8f501595f5e)`() const` 

Use this to create the Pipelines to render the shadow pass.

#### `public inline SharedRenderPass const  & `[`forwardPass`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1afbf56fa324abb5d2b20e34caf66cfaaf)`() const` 

Use this to create the Pipelines to render the forward pass.

# namespace `UtilsLava` 

Partially taken from the Vulkan Cookbook: [https://github.com/PacktPublishing/Vulkan-Cookbook](https://github.com/PacktPublishing/Vulkan-Cookbook)

which is licensed under MIT License:

MIT License

Copyright (c) 2017 Packt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public lava::SharedImage `[`loadCreateAndUploadImg`](#namespace_utils_lava_1a213313b1a78c1ee476d9bc856cffaa75)`(const std::string & filePath,lava::SharedDevice device,bool generateMipmaps)`            | 
`public lava::SharedImage `[`loadCreateAndUploadImgForTexture_default`](#namespace_utils_lava_1a32dc14a8d7d4f2e83e2eb7d2c47c4567)`(const std::string & filePath,lava::SharedDevice device)`            | 
`public bool `[`createBuffer`](#namespace_utils_lava_1a36e9f1e89e4e6b57c88cf6a12c834b40)`(VkDevice logical_device,VkDeviceSize size,VkBufferUsageFlags usage,VkBuffer & buffer)`            | 

## Members

#### `public lava::SharedImage `[`loadCreateAndUploadImg`](#namespace_utils_lava_1a213313b1a78c1ee476d9bc856cffaa75)`(const std::string & filePath,lava::SharedDevice device,bool generateMipmaps)` 

#### `public lava::SharedImage `[`loadCreateAndUploadImgForTexture_default`](#namespace_utils_lava_1a32dc14a8d7d4f2e83e2eb7d2c47c4567)`(const std::string & filePath,lava::SharedDevice device)` 

#### `public bool `[`createBuffer`](#namespace_utils_lava_1a36e9f1e89e4e6b57c88cf6a12c834b40)`(VkDevice logical_device,VkDeviceSize size,VkBufferUsageFlags usage,VkBuffer & buffer)` 

# class `GlobalSettings` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `stbi_io_callbacks` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int(* `[`read`](#structstbi__io__callbacks_1a623e46b3a2a019611601409926283a88) | 
`public void(* `[`skip`](#structstbi__io__callbacks_1a257aac5480a90a6c4b8fbe86c1b01068) | 
`public int(* `[`eof`](#structstbi__io__callbacks_1a319639db2f76e715eed7a7a974136832) | 

## Members

#### `public int(* `[`read`](#structstbi__io__callbacks_1a623e46b3a2a019611601409926283a88) 

#### `public void(* `[`skip`](#structstbi__io__callbacks_1a257aac5480a90a6c4b8fbe86c1b01068) 

#### `public int(* `[`eof`](#structstbi__io__callbacks_1a319639db2f76e715eed7a7a974136832) 

Generated by [Moxygen](https://sourcey.com/moxygen)
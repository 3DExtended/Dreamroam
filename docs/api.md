# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`DCore::Components`](#namespace_d_core_1_1_components) | 
`namespace `[`DCore::ComponentSystem`](#namespace_d_core_1_1_component_system) | [ComponentSystem](#namespace_d_core_1_1_component_system) is the namespace for the component system of this engine. It provides classes to which implement ECS functionalities.
`namespace `[`DCore::Example`](#namespace_d_core_1_1_example) | 
`namespace `[`DCore::Meshes`](#namespace_d_core_1_1_meshes) | 
`namespace `[`DCore::Rendering`](#namespace_d_core_1_1_rendering) | 
`namespace `[`DCore::Textures`](#namespace_d_core_1_1_textures) | 
`namespace `[`lava::pipeline`](#namespacelava_1_1pipeline) | 
`namespace `[`UtilsLava`](#namespace_utils_lava) | Partially taken from the Vulkan Cookbook: [https://github.com/PacktPublishing/Vulkan-Cookbook](https://github.com/PacktPublishing/Vulkan-Cookbook)
`class `[`GlobalSettings`](#class_global_settings) | 
`struct `[`stbi_io_callbacks`](#structstbi__io__callbacks) | 

# namespace `DCore::Components` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::Components::RenderComponent`](#class_d_core_1_1_components_1_1_render_component) | 

# class `DCore::Components::RenderComponent` 

```
class DCore::Components::RenderComponent
  : public DCore::ComponentSystem::AComponent
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`geometryObj`](#class_d_core_1_1_components_1_1_render_component_1ac3f4908cdf0e2e86d0cd6983cfe17d5b) | 
`public bool `[`isTransparent`](#class_d_core_1_1_components_1_1_render_component_1a5bced5c35fcad40fee355339fcabfe55) | 
`public float `[`alpha`](#class_d_core_1_1_components_1_1_render_component_1a0e905b72e97a5afd15fd9a6f6763b393) | 
`public bool `[`hasTexture`](#class_d_core_1_1_components_1_1_render_component_1a987d2cc4a2ff8771d7e7e875045ed043) | 
`public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`textureObj`](#class_d_core_1_1_components_1_1_render_component_1ae7a4d3e36c43a11f623887b2830af3d7) | 
`public bool `[`active`](#class_d_core_1_1_components_1_1_render_component_1aeec6a5934221414a5139f49ca4e73272) | 
`public bool `[`isThrowingShadow`](#class_d_core_1_1_components_1_1_render_component_1a14dffdcaf02994032cd40a9f9658db49) | 
`public inline  `[`RenderComponent`](#class_d_core_1_1_components_1_1_render_component_1aac39f1556be9f68a431ce977480c4d94)`()` | 

## Members

#### `public std::shared_ptr< `[`Geometry`](#class_d_core_1_1_meshes_1_1_geometry)` > `[`geometryObj`](#class_d_core_1_1_components_1_1_render_component_1ac3f4908cdf0e2e86d0cd6983cfe17d5b) 

#### `public bool `[`isTransparent`](#class_d_core_1_1_components_1_1_render_component_1a5bced5c35fcad40fee355339fcabfe55) 

#### `public float `[`alpha`](#class_d_core_1_1_components_1_1_render_component_1a0e905b72e97a5afd15fd9a6f6763b393) 

#### `public bool `[`hasTexture`](#class_d_core_1_1_components_1_1_render_component_1a987d2cc4a2ff8771d7e7e875045ed043) 

#### `public std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`textureObj`](#class_d_core_1_1_components_1_1_render_component_1ae7a4d3e36c43a11f623887b2830af3d7) 

#### `public bool `[`active`](#class_d_core_1_1_components_1_1_render_component_1aeec6a5934221414a5139f49ca4e73272) 

#### `public bool `[`isThrowingShadow`](#class_d_core_1_1_components_1_1_render_component_1a14dffdcaf02994032cd40a9f9658db49) 

#### `public inline  `[`RenderComponent`](#class_d_core_1_1_components_1_1_render_component_1aac39f1556be9f68a431ce977480c4d94)`()` 

# namespace `DCore::ComponentSystem` 

[ComponentSystem](#namespace_d_core_1_1_component_system) is the namespace for the component system of this engine. It provides classes to which implement ECS functionalities.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DCore::ComponentSystem::AComponent`](#class_d_core_1_1_component_system_1_1_a_component) | This class is abstract and has to be inherited. It provides the standard functions as start() or update() and when added to an active [GameObject](#class_d_core_1_1_component_system_1_1_game_object) instance is called by the engine. It also provides basic functionality to the engine like a ShowMouse function.
`class `[`DCore::ComponentSystem::AScene`](#class_d_core_1_1_component_system_1_1_a_scene) | This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e) or [update()](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec). Use your instance of this class in combination with the [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) to define your world.
`class `[`DCore::ComponentSystem::GameObject`](#class_d_core_1_1_component_system_1_1_game_object) | A gameobject is a object in the scene. It is used as a collection of components with some additional funcionallity: Each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) has a transform component which is used to store the position, the rotation and the scale of that object. GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).
`class `[`DCore::ComponentSystem::SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler) | A [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) is the manager of the game engine. It implements the singleton pattern and provides getters for the current scene, the switch scene method and more.
`class `[`DCore::ComponentSystem::Transform`](#class_d_core_1_1_component_system_1_1_transform) | This class is a part of each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.

# class `DCore::ComponentSystem::AComponent` 

This class is abstract and has to be inherited. It provides the standard functions as start() or update() and when added to an active [GameObject](#class_d_core_1_1_component_system_1_1_game_object) instance is called by the engine. It also provides basic functionality to the engine like a ShowMouse function.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`AComponent`](#class_d_core_1_1_component_system_1_1_a_component_1ac7e35a094c399f42b5f98f60e4623334)`()` | 
`public std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > `[`getCurrentScene`](#class_d_core_1_1_component_system_1_1_a_component_a14e745bfaee5215041126653e8a3a726_1a14e745bfaee5215041126653e8a3a726)`()` | Returns a handle to the active scene (to access their functionalities).
`public inline std::weak_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`getCurrentGameObject`](#class_d_core_1_1_component_system_1_1_a_component_ae454fe4879331e8dceef913590fbc11b_1ae454fe4879331e8dceef913590fbc11b)`()` | Returns a pointer to the gameObject the component is running on/connected to.
`public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_component_aba70c25a5e7d0ba865bf6f15e4186bbd_1aba70c25a5e7d0ba865bf6f15e4186bbd)`()` | Creates a new gameObject with name "". This [GameObject](#class_d_core_1_1_component_system_1_1_game_object) is introduced to the current scene.
`public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_component_adcdcb50556a8d45ac913005223bf56b2_1adcdcb50556a8d45ac913005223bf56b2)`(std::string name)` | Creates a new gameObject with a specified name. This [GameObject](#class_d_core_1_1_component_system_1_1_game_object) is introduced to the current scene.
`protected std::weak_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`gameObject`](#class_d_core_1_1_component_system_1_1_a_component_1a462a1e3afdcea8155464cc267ca0ed8b) | 

## Members

#### `public inline  `[`AComponent`](#class_d_core_1_1_component_system_1_1_a_component_1ac7e35a094c399f42b5f98f60e4623334)`()` 

#### `public std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > `[`getCurrentScene`](#class_d_core_1_1_component_system_1_1_a_component_a14e745bfaee5215041126653e8a3a726_1a14e745bfaee5215041126653e8a3a726)`()` 

Returns a handle to the active scene (to access their functionalities).

#### Returns
A pointer to the active/current scene.

#### `public inline std::weak_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`getCurrentGameObject`](#class_d_core_1_1_component_system_1_1_a_component_ae454fe4879331e8dceef913590fbc11b_1ae454fe4879331e8dceef913590fbc11b)`()` 

Returns a pointer to the gameObject the component is running on/connected to.

#### Returns
A pointer to the gameObject.

#### `public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_component_aba70c25a5e7d0ba865bf6f15e4186bbd_1aba70c25a5e7d0ba865bf6f15e4186bbd)`()` 

Creates a new gameObject with name "". This [GameObject](#class_d_core_1_1_component_system_1_1_game_object) is introduced to the current scene.

#### Returns
A pointer to the empty gameObject.

#### `public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_component_adcdcb50556a8d45ac913005223bf56b2_1adcdcb50556a8d45ac913005223bf56b2)`(std::string name)` 

Creates a new gameObject with a specified name. This [GameObject](#class_d_core_1_1_component_system_1_1_game_object) is introduced to the current scene.

#### Parameters
* `name` The name for the new [GameObject](#class_d_core_1_1_component_system_1_1_game_object)

#### Returns
A pointer to the empty gameObject with the name.

#### `protected std::weak_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`gameObject`](#class_d_core_1_1_component_system_1_1_a_component_1a462a1e3afdcea8155464cc267ca0ed8b) 

# class `DCore::ComponentSystem::AScene` 

This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e) or [update()](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec). Use your instance of this class in combination with the [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler) to define your world.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene_ad0eacf691dbc8240fdf3a42d450c1042_1ad0eacf691dbc8240fdf3a42d450c1042)`()` | Creates the rendering device instance.
`public  `[`~AScene`](#class_d_core_1_1_component_system_1_1_a_scene_1a9faf7f1a271327227e83627432d0b210)`()` | 
`public inline virtual void `[`start`](#class_d_core_1_1_component_system_1_1_a_scene_af9a267ab6c5fc9a80045f60516d3664e_1af9a267ab6c5fc9a80045f60516d3664e)`()` | This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.
`public inline virtual void `[`update`](#class_d_core_1_1_component_system_1_1_a_scene_a46a98a1674671c4f42271a6f21b7dfec_1a46a98a1674671c4f42271a6f21b7dfec)`(double dt)` | This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.
`public inline virtual void `[`destroy`](#class_d_core_1_1_component_system_1_1_a_scene_a420362ec1665e379fd3136b98c92c295_1a420362ec1665e379fd3136b98c92c295)`()` | This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.
`public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_scene_a3d7a50f9a2fe40a282c7a26f0a9df5f0_1a3d7a50f9a2fe40a282c7a26f0a9df5f0)`()` | Creates and registers a new game object. The name of this game object will be the empty string. Please note that you need to keep your own pointer to this object when you want to update it later.
`public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_scene_a220e42f764bd4fc37a73d76e4a48a0b9_1a220e42f764bd4fc37a73d76e4a48a0b9)`(const std::string name)` | Creates and registers a new game object. Please note that you need to keep your own pointer to this object when you want to update it later.
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

#### `public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_scene_a3d7a50f9a2fe40a282c7a26f0a9df5f0_1a3d7a50f9a2fe40a282c7a26f0a9df5f0)`()` 

Creates and registers a new game object. The name of this game object will be the empty string. Please note that you need to keep your own pointer to this object when you want to update it later.

#### Returns
A new gameObject instance.

#### `public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`instantiate`](#class_d_core_1_1_component_system_1_1_a_scene_a220e42f764bd4fc37a73d76e4a48a0b9_1a220e42f764bd4fc37a73d76e4a48a0b9)`(const std::string name)` 

Creates and registers a new game object. Please note that you need to keep your own pointer to this object when you want to update it later.

#### Parameters
* `name` The name of the gameObject in the scene.

#### Returns
A new gameObject instance.

#### `protected lava::SharedDevice `[`mDevice`](#class_d_core_1_1_component_system_1_1_a_scene_aea101e43d1950af16e725b7a53ec136b_1aea101e43d1950af16e725b7a53ec136b) 

The device which is used to render the scene. This will be used for a number of initialization procedures.

#### `protected std::shared_ptr< `[`GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store)` > `[`mGeometryStore`](#class_d_core_1_1_component_system_1_1_a_scene_a4082224d4bc85a7536a5f830a44bd446_1a4082224d4bc85a7536a5f830a44bd446) 

This GeometryStore is used to load meshes and push them to the GPU.

#### `protected std::shared_ptr< `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store)` > `[`mTextureStore`](#class_d_core_1_1_component_system_1_1_a_scene_a9f5432333052579e1af732c2ba94fd74_1a9f5432333052579e1af732c2ba94fd74) 

This TextureStore is used to load textures and push them to the GPU.

# class `DCore::ComponentSystem::GameObject` 

```
class DCore::ComponentSystem::GameObject
  : public std::enable_shared_from_this< GameObject >
```  

A gameobject is a object in the scene. It is used as a collection of components with some additional funcionallity: Each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) has a transform component which is used to store the position, the rotation and the scale of that object. GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).

Note that not every [GameObject](#class_d_core_1_1_component_system_1_1_game_object) has to be visible and support some kind of render. It can also be used to create handlers or some other singletons.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Transform`](#class_d_core_1_1_component_system_1_1_transform)` `[`transform`](#class_d_core_1_1_component_system_1_1_game_object_ae3a617195a8f8b70a72ad29745469a0c_1ae3a617195a8f8b70a72ad29745469a0c) | The [Transform](#class_d_core_1_1_component_system_1_1_transform) component is assigned to each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) to store position scale and rotation.
`public  `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object_a0348e3ee2e83d56eafca7a3547f432c4_1a0348e3ee2e83d56eafca7a3547f432c4)`()` | This creates a new [GameObject](#class_d_core_1_1_component_system_1_1_game_object) with the empty string as name.
`public  `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object_a0737657696b478c7962c2a6c2f5b1bd8_1a0737657696b478c7962c2a6c2f5b1bd8)`(std::string name)` | This creates a new [GameObject](#class_d_core_1_1_component_system_1_1_game_object) with a specified name.
`public void `[`addComponent`](#class_d_core_1_1_component_system_1_1_game_object_aa4f0f1a42d622fd6c96223083e6a573b_1aa4f0f1a42d622fd6c96223083e6a573b)`(std::shared_ptr< `[`AComponent`](#class_d_core_1_1_component_system_1_1_a_component)` > comp)` | This method is used to assign a component to the [GameObject](#class_d_core_1_1_component_system_1_1_game_object). Note that you have to create a lasting component (using the 'new' macro).
`public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`getParent`](#class_d_core_1_1_component_system_1_1_game_object_ad36e10b2d28b2f4e34326244048f786c_1ad36e10b2d28b2f4e34326244048f786c)`()` | This function returns the parent if existing. If not existing, this returns nullptr.
`public std::vector< std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > > `[`getChilds`](#class_d_core_1_1_component_system_1_1_game_object_a7053cf0979ec793600f5c128219f0ed8_1a7053cf0979ec793600f5c128219f0ed8)`()` | This returns a list of all child gameobjects that are assigned to this gameObject.
`public void `[`setParent`](#class_d_core_1_1_component_system_1_1_game_object_af3d7a870032a51dea2afeaf57814a452_1af3d7a870032a51dea2afeaf57814a452)`(std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > obj)` | Sets the parent for this gameObject
`public void `[`addChild`](#class_d_core_1_1_component_system_1_1_game_object_a616a561447caebf99e373ef69656748f_1a616a561447caebf99e373ef69656748f)`(std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > obj)` | Adds a child to this gameObject
`public template<>`  <br/>`T * `[`getComponent`](#class_d_core_1_1_component_system_1_1_game_object_1a3cd69f0f375e662c0d04e21d6593d6f0)`()` | 

## Members

#### `public `[`Transform`](#class_d_core_1_1_component_system_1_1_transform)` `[`transform`](#class_d_core_1_1_component_system_1_1_game_object_ae3a617195a8f8b70a72ad29745469a0c_1ae3a617195a8f8b70a72ad29745469a0c) 

The [Transform](#class_d_core_1_1_component_system_1_1_transform) component is assigned to each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) to store position scale and rotation.

Note that the Parent-Child-relation has impact on the calculations taking place in the transform instance.

#### `public  `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object_a0348e3ee2e83d56eafca7a3547f432c4_1a0348e3ee2e83d56eafca7a3547f432c4)`()` 

This creates a new [GameObject](#class_d_core_1_1_component_system_1_1_game_object) with the empty string as name.

Note that it is strongly advised to create a [GameObject](#class_d_core_1_1_component_system_1_1_game_object) using the instantiate() method offered by the Scene or the component class.

#### `public  `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object_a0737657696b478c7962c2a6c2f5b1bd8_1a0737657696b478c7962c2a6c2f5b1bd8)`(std::string name)` 

This creates a new [GameObject](#class_d_core_1_1_component_system_1_1_game_object) with a specified name.

#### Parameters
* `name` The name of the new [GameObject](#class_d_core_1_1_component_system_1_1_game_object)

Note that it is strongly advised to create a [GameObject](#class_d_core_1_1_component_system_1_1_game_object) using the instantiate() method offered by the Scene or the component class.

#### `public void `[`addComponent`](#class_d_core_1_1_component_system_1_1_game_object_aa4f0f1a42d622fd6c96223083e6a573b_1aa4f0f1a42d622fd6c96223083e6a573b)`(std::shared_ptr< `[`AComponent`](#class_d_core_1_1_component_system_1_1_a_component)` > comp)` 

This method is used to assign a component to the [GameObject](#class_d_core_1_1_component_system_1_1_game_object). Note that you have to create a lasting component (using the 'new' macro).

```cpp
auto comp = std::make_shared<RotateObjectComponent>();
  gameObject->addComponent(comp);
```

#### Parameters
* `comp` The component you want to add.

#### `public std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > `[`getParent`](#class_d_core_1_1_component_system_1_1_game_object_ad36e10b2d28b2f4e34326244048f786c_1ad36e10b2d28b2f4e34326244048f786c)`()` 

This function returns the parent if existing. If not existing, this returns nullptr.

#### Returns
The parent gameObject if existing, else nullptr

#### `public std::vector< std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > > `[`getChilds`](#class_d_core_1_1_component_system_1_1_game_object_a7053cf0979ec793600f5c128219f0ed8_1a7053cf0979ec793600f5c128219f0ed8)`()` 

This returns a list of all child gameobjects that are assigned to this gameObject.

#### Returns
A list of all childs, or an empty list

#### `public void `[`setParent`](#class_d_core_1_1_component_system_1_1_game_object_af3d7a870032a51dea2afeaf57814a452_1af3d7a870032a51dea2afeaf57814a452)`(std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > obj)` 

Sets the parent for this gameObject

#### Parameters
* `obj` the parent for this object

#### `public void `[`addChild`](#class_d_core_1_1_component_system_1_1_game_object_a616a561447caebf99e373ef69656748f_1a616a561447caebf99e373ef69656748f)`(std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` > obj)` 

Adds a child to this gameObject

#### Parameters
* `obj` The new child

#### `public template<>`  <br/>`T * `[`getComponent`](#class_d_core_1_1_component_system_1_1_game_object_1a3cd69f0f375e662c0d04e21d6593d6f0)`()` 

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
`public lava::SharedBuffer `[`mViewProjBufferPrePass`](#class_d_core_1_1_component_system_1_1_scene_handler_1afd3d3ed2b406aef321d27a4db7bd9c4c) | 
`public lava::SharedBuffer `[`mViewProjBufferForwardPass`](#class_d_core_1_1_component_system_1_1_scene_handler_1a094f3b8e2b5bfc6194368db088975e28) | 
`public lava::SharedDescriptorSetLayout `[`mViewProjDescriptorSetLayout`](#class_d_core_1_1_component_system_1_1_scene_handler_1af525113019761acf447d9dab7d447ab2) | 
`public lava::SharedDescriptorSet `[`mViewProjDescriptorForward`](#class_d_core_1_1_component_system_1_1_scene_handler_1aca84aa35b701c428519950c771d74a16) | 
`public lava::SharedDescriptorSet `[`mViewProjDescriptorPre`](#class_d_core_1_1_component_system_1_1_scene_handler_1a342739d3084aba151aa7194516dbd1d3) | 
`public std::vector< std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > > `[`scenes`](#class_d_core_1_1_component_system_1_1_scene_handler_1a963129a7fdfeb03f44ecfcb807d3fae2) | 
`public std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > `[`curScene`](#class_d_core_1_1_component_system_1_1_scene_handler_1a1da1b2dbd24ded4068cd57cd5bf4269b) | 
`public std::shared_ptr< lava::features::GlfwOutput > `[`mGlfwOutput`](#class_d_core_1_1_component_system_1_1_scene_handler_1a8842e9c77258cd504313e47025d4df59) | 
`public std::shared_ptr< lava::features::Validation > `[`mValidation`](#class_d_core_1_1_component_system_1_1_scene_handler_1a3f79a79d27cddb2b4c6ff70bda217395) | 
`public std::shared_ptr< lava::features::GlfwWindow > `[`mWindow`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab6ffd0bc5b010ac5caeb4d411cf67db5) | 
`public lava::SharedDevice `[`mDevice`](#class_d_core_1_1_component_system_1_1_scene_handler_1ad50227bd534e8ff0023162822398fbd9) | 
`public lava::SharedPipelineLayout `[`mPlLayout`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae3ade7eed67982f398c1b7a67735334c) | 
`public std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mPipeline`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae533376b34de4725eefaa5ed93e21275) | 
`public std::vector< lava::SharedFramebuffer > `[`companionWindowFBO`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4acf4782b3fa11d3a347322c6271ad7c) | 
`public std::shared_ptr< lava::features::GlfwOutput > `[`getGlfwOutput`](#class_d_core_1_1_component_system_1_1_scene_handler_1a06af644644384175f49eeb3a328801ba)`() const` | 
`public void `[`run`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` | 
`public void `[`updateCamera`](#class_d_core_1_1_component_system_1_1_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` | 
`public void `[`setupPipeline`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa840550cfbac55ffbf68775f8b194192)`(const lava::SharedDescriptorSetLayout textureLayout)` | 
`public void `[`getFrustumCorners`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa1bb88527ddca127ac396d1e3d703e65)`(std::vector< glm::vec4 > & corners,glm::mat4 projection)` | 
`public std::tuple< glm::mat4, glm::vec3, glm::vec3 > `[`rotateCameraFrustrumCornersToLightSpace`](#class_d_core_1_1_component_system_1_1_scene_handler_1a0a21e13bbaa0593aa3d6583da619ac95)`(glm::vec3 forward,glm::vec3 camPosition,std::vector< glm::vec4 > corners,glm::vec3 upDirection)` | 
`public void `[`setupGlfwCallbacks`](#class_d_core_1_1_component_system_1_1_scene_handler_1a8a72d73b454dd9de9b96adebe938c7d9)`()` | 
`public  `[`SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_a99fe4ea2e3e102ec3beeb448b6878cc5_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` | Creates a new instance of the scene handler. Should only be called ONCE by the main function.
`public  `[`~SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mOpaqueUntextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a302ba452f9e507d30d2a427179b5f596) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mOpaqueTextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a7073a6b24c46558474ef828d6c031f8c) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mTransparendUntextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4515d227d8fe4d38c0bf72ec84b55a7f) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mTransparendTextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab910e78c6e8401f27e479b6de9e16bbc) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mShadowMap`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4449a85008106fe0c09b5b01df771615) | 

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

#### `public lava::SharedBuffer `[`mViewProjBufferPrePass`](#class_d_core_1_1_component_system_1_1_scene_handler_1afd3d3ed2b406aef321d27a4db7bd9c4c) 

#### `public lava::SharedBuffer `[`mViewProjBufferForwardPass`](#class_d_core_1_1_component_system_1_1_scene_handler_1a094f3b8e2b5bfc6194368db088975e28) 

#### `public lava::SharedDescriptorSetLayout `[`mViewProjDescriptorSetLayout`](#class_d_core_1_1_component_system_1_1_scene_handler_1af525113019761acf447d9dab7d447ab2) 

#### `public lava::SharedDescriptorSet `[`mViewProjDescriptorForward`](#class_d_core_1_1_component_system_1_1_scene_handler_1aca84aa35b701c428519950c771d74a16) 

#### `public lava::SharedDescriptorSet `[`mViewProjDescriptorPre`](#class_d_core_1_1_component_system_1_1_scene_handler_1a342739d3084aba151aa7194516dbd1d3) 

#### `public std::vector< std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > > `[`scenes`](#class_d_core_1_1_component_system_1_1_scene_handler_1a963129a7fdfeb03f44ecfcb807d3fae2) 

#### `public std::shared_ptr< `[`AScene`](#class_d_core_1_1_component_system_1_1_a_scene)` > `[`curScene`](#class_d_core_1_1_component_system_1_1_scene_handler_1a1da1b2dbd24ded4068cd57cd5bf4269b) 

#### `public std::shared_ptr< lava::features::GlfwOutput > `[`mGlfwOutput`](#class_d_core_1_1_component_system_1_1_scene_handler_1a8842e9c77258cd504313e47025d4df59) 

#### `public std::shared_ptr< lava::features::Validation > `[`mValidation`](#class_d_core_1_1_component_system_1_1_scene_handler_1a3f79a79d27cddb2b4c6ff70bda217395) 

#### `public std::shared_ptr< lava::features::GlfwWindow > `[`mWindow`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab6ffd0bc5b010ac5caeb4d411cf67db5) 

#### `public lava::SharedDevice `[`mDevice`](#class_d_core_1_1_component_system_1_1_scene_handler_1ad50227bd534e8ff0023162822398fbd9) 

#### `public lava::SharedPipelineLayout `[`mPlLayout`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae3ade7eed67982f398c1b7a67735334c) 

#### `public std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mPipeline`](#class_d_core_1_1_component_system_1_1_scene_handler_1ae533376b34de4725eefaa5ed93e21275) 

#### `public std::vector< lava::SharedFramebuffer > `[`companionWindowFBO`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4acf4782b3fa11d3a347322c6271ad7c) 

#### `public std::shared_ptr< lava::features::GlfwOutput > `[`getGlfwOutput`](#class_d_core_1_1_component_system_1_1_scene_handler_1a06af644644384175f49eeb3a328801ba)`() const` 

#### `public void `[`run`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` 

#### `public void `[`updateCamera`](#class_d_core_1_1_component_system_1_1_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` 

#### `public void `[`setupPipeline`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa840550cfbac55ffbf68775f8b194192)`(const lava::SharedDescriptorSetLayout textureLayout)` 

#### `public void `[`getFrustumCorners`](#class_d_core_1_1_component_system_1_1_scene_handler_1aa1bb88527ddca127ac396d1e3d703e65)`(std::vector< glm::vec4 > & corners,glm::mat4 projection)` 

#### `public std::tuple< glm::mat4, glm::vec3, glm::vec3 > `[`rotateCameraFrustrumCornersToLightSpace`](#class_d_core_1_1_component_system_1_1_scene_handler_1a0a21e13bbaa0593aa3d6583da619ac95)`(glm::vec3 forward,glm::vec3 camPosition,std::vector< glm::vec4 > corners,glm::vec3 upDirection)` 

#### `public void `[`setupGlfwCallbacks`](#class_d_core_1_1_component_system_1_1_scene_handler_1a8a72d73b454dd9de9b96adebe938c7d9)`()` 

#### `public  `[`SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_a99fe4ea2e3e102ec3beeb448b6878cc5_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` 

Creates a new instance of the scene handler. Should only be called ONCE by the main function.

This should not be used to create a new instance. Instead, please use the GetInstance method.

This needs to be public in order to create a new instance using std::make_shared in the GetInstance method.

#### Returns
A new [SceneHandler](#class_d_core_1_1_component_system_1_1_scene_handler)

#### `public  `[`~SceneHandler`](#class_d_core_1_1_component_system_1_1_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mOpaqueUntextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a302ba452f9e507d30d2a427179b5f596) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mOpaqueTextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a7073a6b24c46558474ef828d6c031f8c) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mTransparendUntextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4515d227d8fe4d38c0bf72ec84b55a7f) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mTransparendTextured`](#class_d_core_1_1_component_system_1_1_scene_handler_1ab910e78c6e8401f27e479b6de9e16bbc) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer)` > `[`mShadowMap`](#class_d_core_1_1_component_system_1_1_scene_handler_1a4449a85008106fe0c09b5b01df771615) 

# class `DCore::ComponentSystem::Transform` 

This class is a part of each [GameObject](#class_d_core_1_1_component_system_1_1_game_object) which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::vec3 `[`position`](#class_d_core_1_1_component_system_1_1_transform_a51c54982dc0577f07cde3c7d289deed8_1a51c54982dc0577f07cde3c7d289deed8) | The position of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)
`public glm::vec3 `[`rotation`](#class_d_core_1_1_component_system_1_1_transform_a5ad9bc3b642bec246394ee96964910a2_1a5ad9bc3b642bec246394ee96964910a2) | The rotation of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)
`public glm::vec3 `[`scale`](#class_d_core_1_1_component_system_1_1_transform_ac3a0302859efda7d3ac858294ac2f8bf_1ac3a0302859efda7d3ac858294ac2f8bf) | The scale value of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)
`public inline  `[`Transform`](#class_d_core_1_1_component_system_1_1_transform_afa4756474d8e50d98b0bbbf5b6658bc8_1afa4756474d8e50d98b0bbbf5b6658bc8)`(glm::vec3 pos,glm::vec3 rot,glm::vec3 scale)` | This creates a new [Transform](#class_d_core_1_1_component_system_1_1_transform) object where position and rotation can be specified (by default they are 0). This constructor can also be used with a specified scale value (which by default is 1).
`public glm::mat4 `[`getModelMatrix`](#class_d_core_1_1_component_system_1_1_transform_af0671190bf3f3b4e5cdd8ccb23c05a7a_1af0671190bf3f3b4e5cdd8ccb23c05a7a)`()` | This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).
`public glm::mat4 `[`getScaleMatrix`](#class_d_core_1_1_component_system_1_1_transform_adbeb9e27f8f0616336c7101c2d925ee3_1adbeb9e27f8f0616336c7101c2d925ee3)`()` | This method returns a matrix that scales the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)
`public glm::mat4 `[`getRotationMatrix`](#class_d_core_1_1_component_system_1_1_transform_a716f060a18db568786ae023e8c02597c_1a716f060a18db568786ae023e8c02597c)`()` | This method returns a matrix that rotates the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)
`public glm::mat4 `[`getPosMatrix`](#class_d_core_1_1_component_system_1_1_transform_a39100fc47750475ca69529a346885a28_1a39100fc47750475ca69529a346885a28)`()` | This method returns a matrix that positions the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)
`protected `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` * `[`gameObject`](#class_d_core_1_1_component_system_1_1_transform_1a1aa4d93351c974a8408f3234d884028e) | 

## Members

#### `public glm::vec3 `[`position`](#class_d_core_1_1_component_system_1_1_transform_a51c54982dc0577f07cde3c7d289deed8_1a51c54982dc0577f07cde3c7d289deed8) 

The position of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)

#### `public glm::vec3 `[`rotation`](#class_d_core_1_1_component_system_1_1_transform_a5ad9bc3b642bec246394ee96964910a2_1a5ad9bc3b642bec246394ee96964910a2) 

The rotation of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)

#### `public glm::vec3 `[`scale`](#class_d_core_1_1_component_system_1_1_transform_ac3a0302859efda7d3ac858294ac2f8bf_1ac3a0302859efda7d3ac858294ac2f8bf) 

The scale value of the [Transform](#class_d_core_1_1_component_system_1_1_transform) and the corresponding [GameObject](#class_d_core_1_1_component_system_1_1_game_object)

#### `public inline  `[`Transform`](#class_d_core_1_1_component_system_1_1_transform_afa4756474d8e50d98b0bbbf5b6658bc8_1afa4756474d8e50d98b0bbbf5b6658bc8)`(glm::vec3 pos,glm::vec3 rot,glm::vec3 scale)` 

This creates a new [Transform](#class_d_core_1_1_component_system_1_1_transform) object where position and rotation can be specified (by default they are 0). This constructor can also be used with a specified scale value (which by default is 1).

#### Parameters
* `pos` The three dimensional position of the object

* `rot` The three dimensional rotation of the object

* `scale` The three dimensional scale of the object

Note that this class can be used without a [GameObject](#class_d_core_1_1_component_system_1_1_game_object) but will in this case not be used in the scene.

#### `public glm::mat4 `[`getModelMatrix`](#class_d_core_1_1_component_system_1_1_transform_af0671190bf3f3b4e5cdd8ccb23c05a7a_1af0671190bf3f3b4e5cdd8ccb23c05a7a)`()` 

This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).

#### Returns
Model matrix (with parent transform)

#### `public glm::mat4 `[`getScaleMatrix`](#class_d_core_1_1_component_system_1_1_transform_adbeb9e27f8f0616336c7101c2d925ee3_1adbeb9e27f8f0616336c7101c2d925ee3)`()` 

This method returns a matrix that scales the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)

#### Returns
The scale matrix

#### `public glm::mat4 `[`getRotationMatrix`](#class_d_core_1_1_component_system_1_1_transform_a716f060a18db568786ae023e8c02597c_1a716f060a18db568786ae023e8c02597c)`()` 

This method returns a matrix that rotates the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)

#### Returns
The rotation matrix

#### `public glm::mat4 `[`getPosMatrix`](#class_d_core_1_1_component_system_1_1_transform_a39100fc47750475ca69529a346885a28_1a39100fc47750475ca69529a346885a28)`()` 

This method returns a matrix that positions the object using this [Transform](#class_d_core_1_1_component_system_1_1_transform)

#### Returns
The position matrix

#### `protected `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` * `[`gameObject`](#class_d_core_1_1_component_system_1_1_transform_1a1aa4d93351c974a8408f3234d884028e) 

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
`class `[`DCore::Meshes::Geometry`](#class_d_core_1_1_meshes_1_1_geometry) | 
`class `[`DCore::Meshes::GeometryLoader`](#class_d_core_1_1_meshes_1_1_geometry_loader) | 
`class `[`DCore::Meshes::GeometryStore`](#class_d_core_1_1_meshes_1_1_geometry_store) | 

# class `DCore::Meshes::Geometry` 

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
`class `[`DCore::Rendering::DefaultRenderer`](#class_d_core_1_1_rendering_1_1_default_renderer) | 
`class `[`DCore::Rendering::DefaultTexturedRenderer`](#class_d_core_1_1_rendering_1_1_default_textured_renderer) | 
`class `[`DCore::Rendering::GraphicsPipelineFactory`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_factory) | 
`class `[`DCore::Rendering::GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer) | 
`struct `[`DCore::Rendering::CameraData`](#struct_d_core_1_1_rendering_1_1_camera_data) | 
`struct `[`DCore::Rendering::PushConstants`](#struct_d_core_1_1_rendering_1_1_push_constants) | 
`struct `[`DCore::Rendering::ShadowMVP`](#struct_d_core_1_1_rendering_1_1_shadow_m_v_p) | 
`struct `[`DCore::Rendering::VertexAttributes`](#struct_d_core_1_1_rendering_1_1_vertex_attributes) | 

# class `DCore::Rendering::DefaultRenderer` 

```
class DCore::Rendering::DefaultRenderer
  : public DCore::Rendering::GraphicsPipelineRenderer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::DefaultTexturedRenderer` 

```
class DCore::Rendering::DefaultTexturedRenderer
  : public DCore::Rendering::GraphicsPipelineRenderer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::GraphicsPipelineFactory` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DCore::Rendering::GraphicsPipelineRenderer` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a62793a25bff6253222047558fcdc3680)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` | 
`public inline virtual  `[`~GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1ae502a4f31168364595bb3eef4e33f741)`()` | 
`public void `[`prepareRendering`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1ab00f69af656d6889d15613f627fc5267)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` | 
`public void `[`renderGameObjects`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a42bda88dfd216fc11da6a4f027d1facc)`(const std::vector< std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` >> gos)` | 
`protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a347a9e8363e6e3a29cdf50668824ae29) | 
`protected lava::SharedPipelineLayout `[`mLayout`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a68bd3fe4cc4bd953d5f8ae72b8bb3734) | 
`protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a75817b6a63f889bb31f75fd50e40dc9e) | 
`protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a308e3a00807bd2cf410db4e1d047ab42) | 
`protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a9f4f9ab652862ff98f13b446be87d706) | 

## Members

#### `public  explicit `[`GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a62793a25bff6253222047558fcdc3680)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` 

#### `public inline virtual  `[`~GraphicsPipelineRenderer`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1ae502a4f31168364595bb3eef4e33f741)`()` 

#### `public void `[`prepareRendering`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1ab00f69af656d6889d15613f627fc5267)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` 

#### `public void `[`renderGameObjects`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a42bda88dfd216fc11da6a4f027d1facc)`(const std::vector< std::shared_ptr< `[`GameObject`](#class_d_core_1_1_component_system_1_1_game_object)` >> gos)` 

#### `protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a347a9e8363e6e3a29cdf50668824ae29) 

#### `protected lava::SharedPipelineLayout `[`mLayout`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a68bd3fe4cc4bd953d5f8ae72b8bb3734) 

#### `protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a75817b6a63f889bb31f75fd50e40dc9e) 

#### `protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a308e3a00807bd2cf410db4e1d047ab42) 

#### `protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_d_core_1_1_rendering_1_1_graphics_pipeline_renderer_1a9f4f9ab652862ff98f13b446be87d706) 

# struct `DCore::Rendering::CameraData` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_1a65b2129199c448031ec24a6cf68f2850) | 
`public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_1a329f075a588e0bc4fc6b0cda6193161c) | 

## Members

#### `public glm::mat4 `[`view`](#struct_d_core_1_1_rendering_1_1_camera_data_1a65b2129199c448031ec24a6cf68f2850) 

#### `public glm::mat4 `[`proj`](#struct_d_core_1_1_rendering_1_1_camera_data_1a329f075a588e0bc4fc6b0cda6193161c) 

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

# struct `DCore::Rendering::ShadowMVP` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`depthMVP`](#struct_d_core_1_1_rendering_1_1_shadow_m_v_p_1a417f171610e89bb19ddcf42b2f3cdb19) | 

## Members

#### `public glm::mat4 `[`depthMVP`](#struct_d_core_1_1_rendering_1_1_shadow_m_v_p_1a417f171610e89bb19ddcf42b2f3cdb19) 

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
`public inline std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`getTextureWithName`](#class_d_core_1_1_textures_1_1_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` | 
`public inline lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_d_core_1_1_textures_1_1_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` | 

## Members

#### `public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a5faa7af45ca80f42d80c38ee6f45531a)`(lava::SharedDevice device)` 

#### `public  `[`TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a896214fbe95e96b69382764136d1dbd5)`(lava::SharedDevice device,std::vector< std::pair< std::string, std::string >> imageTexturePathsAndNames)` 

#### `public  `[`~TextureStore`](#class_d_core_1_1_textures_1_1_texture_store_1a15a3cccbdaf62d8ae70d403b851704a2)`()` 

#### `public inline std::shared_ptr< `[`Texture`](#class_d_core_1_1_textures_1_1_texture)` > `[`getTextureWithName`](#class_d_core_1_1_textures_1_1_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` 

#### `public inline lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_d_core_1_1_textures_1_1_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` 

# namespace `lava::pipeline` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline) | A Forward+ Rendering Pipeline with post-processing support (at some point in the future)

# class `lava::pipeline::AdvancedRenderingPipeline` 

A Forward+ Rendering Pipeline with post-processing support (at some point in the future)

Features (at some point in the future):

* Shadow Mapping

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
`public lava::SharedImage `[`loadCreateAndUploadImg`](#namespace_utils_lava_1a77b2a72a9102e81b2778663d413182e9)`(std::string filePath,lava::SharedDevice device,bool generateMipmaps)`            | 
`public lava::SharedImage `[`loadCreateAndUploadImgForTexture_default`](#namespace_utils_lava_1af9db2920fce02d413dcda079988ea6e7)`(std::string filePath,lava::SharedDevice device)`            | 
`public bool `[`createBuffer`](#namespace_utils_lava_1a36e9f1e89e4e6b57c88cf6a12c834b40)`(VkDevice logical_device,VkDeviceSize size,VkBufferUsageFlags usage,VkBuffer & buffer)`            | 

## Members

#### `public lava::SharedImage `[`loadCreateAndUploadImg`](#namespace_utils_lava_1a77b2a72a9102e81b2778663d413182e9)`(std::string filePath,lava::SharedDevice device,bool generateMipmaps)` 

#### `public lava::SharedImage `[`loadCreateAndUploadImgForTexture_default`](#namespace_utils_lava_1af9db2920fce02d413dcda079988ea6e7)`(std::string filePath,lava::SharedDevice device)` 

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
# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`lava::pipeline`](#namespacelava_1_1pipeline) | 
`namespace `[`UtilsLava`](#namespace_utils_lava) | Partially taken from the Vulkan Cookbook: [https://github.com/PacktPublishing/Vulkan-Cookbook](https://github.com/PacktPublishing/Vulkan-Cookbook)
`class `[`AComponent`](#class_a_component) | This class is abstract and has to be inherited. It provides the standard functions as start() or update() and when added to an active [GameObject](#class_game_object) instance is called by the engine. It also provides basic functionality to the engine like a ShowMouse function.
`class `[`AScene`](#class_a_scene) | This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_a_scene_1a77ac53926122cd9db819e1e4cad5c182) or [update()](#class_a_scene_1a5a95b5d991630b8e5477b501577e1c7d). Use your instance of this class in combination with the [SceneHandler](#class_scene_handler) to define your world.
`class `[`DefaultRenderer`](#class_default_renderer) | 
`class `[`DefaultTexturedRenderer`](#class_default_textured_renderer) | 
`class `[`DreamroamScene`](#class_dreamroam_scene) | 
`class `[`GameObject`](#class_game_object) | A gameobject is a object in the scene. It is used as a collection of components with some additional funcionallity: Each [GameObject](#class_game_object) has a transform component which is used to store the position, the rotation and the scale of that object. GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).
`class `[`Geometry`](#class_geometry) | 
`class `[`GeometryLoader`](#class_geometry_loader) | 
`class `[`GeometryStore`](#class_geometry_store) | 
`class `[`GlobalSettings`](#class_global_settings) | 
`class `[`GraphicsPipelineFactory`](#class_graphics_pipeline_factory) | 
`class `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer) | 
`class `[`RenderComponent`](#class_render_component) | 
`class `[`SceneHandler`](#class_scene_handler) | A [SceneHandler](#class_scene_handler) is the manager of the game engine. It implements the singleton pattern and provides getters for the current scene, the switch scene method and more.
`class `[`Texture`](#class_texture) | 
`class `[`TextureStore`](#class_texture_store) | 
`class `[`Transform`](#class_transform) | This class is a part of each [GameObject](#class_game_object) which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.
`struct `[`CameraData`](#struct_camera_data) | 
`struct `[`PushConstants`](#struct_push_constants) | 
`struct `[`ShadowMVP`](#struct_shadow_m_v_p) | 
`struct `[`stbi_io_callbacks`](#structstbi__io__callbacks) | 
`struct `[`VertexAttributes`](#struct_vertex_attributes) | 

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
`public void `[`assignCamera`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a19caa69565b7b3d6211495bcf1ef9dfa)`(camera::SharedGenericCamera const & cam,bool useCamViewport)` | Updates the camera If useCamViewport is true, also resizes the pipeline
`public void `[`render`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a51a5fe665107400269ce2eba976da1f8)`(lava::RecordingCommandBuffer & cmd,lava::SharedFramebuffer const & fbo,const std::function< void(lava::pipeline::AdvancedRenderPass const &pass)> & renderFunc)` | executes the whole rendering pipeline
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

#### `public void `[`assignCamera`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a19caa69565b7b3d6211495bcf1ef9dfa)`(camera::SharedGenericCamera const & cam,bool useCamViewport)` 

Updates the camera If useCamViewport is true, also resizes the pipeline

#### `public void `[`render`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline_1a51a5fe665107400269ce2eba976da1f8)`(lava::RecordingCommandBuffer & cmd,lava::SharedFramebuffer const & fbo,const std::function< void(lava::pipeline::AdvancedRenderPass const &pass)> & renderFunc)` 

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

# class `AComponent` 

This class is abstract and has to be inherited. It provides the standard functions as start() or update() and when added to an active [GameObject](#class_game_object) instance is called by the engine. It also provides basic functionality to the engine like a ShowMouse function.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`AComponent`](#class_a_component_1affb8eddec2a8559d01998ccb95007306)`()` | 
`public std::shared_ptr< `[`AScene`](#class_a_scene)` > `[`getCurrentScene`](#class_a_component_1a66d7c748d7db8125a28a5b5641714fe7)`()` | Returns a handle to the active scene (to access their functionalities).
`public inline std::weak_ptr< `[`GameObject`](#class_game_object)` > `[`getCurrentGameObject`](#class_a_component_1a00bbf3fc2aa779cd6e85406fbe02b4f6)`()` | Returns a pointer to the gameObject the component is running on/connected to.
`public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_component_1a723a99202afb60896458b6ad1b8f2449)`()` | Creates a new gameObject with name "". This [GameObject](#class_game_object) is introduced to the current scene.
`public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_component_1a4c31cec99b7d38057cb8dfdc0b202acd)`(std::string name)` | Creates a new gameObject with a specified name. This [GameObject](#class_game_object) is introduced to the current scene.
`protected std::weak_ptr< `[`GameObject`](#class_game_object)` > `[`gameObject`](#class_a_component_1ae73bad0484e1d9d68c3a0a278f33730a) | 

## Members

#### `public inline  `[`AComponent`](#class_a_component_1affb8eddec2a8559d01998ccb95007306)`()` 

#### `public std::shared_ptr< `[`AScene`](#class_a_scene)` > `[`getCurrentScene`](#class_a_component_1a66d7c748d7db8125a28a5b5641714fe7)`()` 

Returns a handle to the active scene (to access their functionalities).

#### Returns
A pointer to the active/current scene.

#### `public inline std::weak_ptr< `[`GameObject`](#class_game_object)` > `[`getCurrentGameObject`](#class_a_component_1a00bbf3fc2aa779cd6e85406fbe02b4f6)`()` 

Returns a pointer to the gameObject the component is running on/connected to.

#### Returns
A pointer to the gameObject.

#### `public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_component_1a723a99202afb60896458b6ad1b8f2449)`()` 

Creates a new gameObject with name "". This [GameObject](#class_game_object) is introduced to the current scene.

#### Returns
A pointer to the empty gameObject.

#### `public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_component_1a4c31cec99b7d38057cb8dfdc0b202acd)`(std::string name)` 

Creates a new gameObject with a specified name. This [GameObject](#class_game_object) is introduced to the current scene.

#### Parameters
* `name` The name for the new [GameObject](#class_game_object)

#### Returns
A pointer to the empty gameObject with the name.

#### `protected std::weak_ptr< `[`GameObject`](#class_game_object)` > `[`gameObject`](#class_a_component_1ae73bad0484e1d9d68c3a0a278f33730a) 

# class `AScene` 

This class is abstract and has to be inherited. It provides the standard functions as [start()](#class_a_scene_1a77ac53926122cd9db819e1e4cad5c182) or [update()](#class_a_scene_1a5a95b5d991630b8e5477b501577e1c7d). Use your instance of this class in combination with the [SceneHandler](#class_scene_handler) to define your world.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`AScene`](#class_a_scene_1ad0eacf691dbc8240fdf3a42d450c1042)`()` | Creates the rendering device instance.
`public  `[`~AScene`](#class_a_scene_1a9faf7f1a271327227e83627432d0b210)`()` | 
`public inline virtual void `[`start`](#class_a_scene_1a77ac53926122cd9db819e1e4cad5c182)`()` | This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.
`public inline virtual void `[`update`](#class_a_scene_1a5a95b5d991630b8e5477b501577e1c7d)`(double dt)` | This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.
`public inline virtual void `[`destroy`](#class_a_scene_1a815f7bed74e832cd100d6857d4df2ab5)`()` | This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.
`public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_scene_1a3d7a50f9a2fe40a282c7a26f0a9df5f0)`()` | Creates and registers a new game object. The name of this game object will be the empty string. Please note that you need to keep your own pointer to this object when you want to update it later.
`public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_scene_1a220e42f764bd4fc37a73d76e4a48a0b9)`(const std::string name)` | Creates and registers a new game object. Please note that you need to keep your own pointer to this object when you want to update it later.
`protected lava::SharedDevice `[`mDevice`](#class_a_scene_1aef5b18b6523d09749dd9e68ac22f44dc) | The device which is used to render the scene. This will be used for a number of initialization procedures.
`protected std::shared_ptr< `[`GeometryStore`](#class_geometry_store)` > `[`mGeometryStore`](#class_a_scene_1a37764fc0c39169109fb285383a67eae8) | This [GeometryStore](#class_geometry_store) is used to load meshes and push them to the GPU.
`protected std::shared_ptr< `[`TextureStore`](#class_texture_store)` > `[`mTextureStore`](#class_a_scene_1af3491c84b7452454dcb62613271e4938) | This [TextureStore](#class_texture_store) is used to load textures and push them to the GPU.

## Members

#### `public  `[`AScene`](#class_a_scene_1ad0eacf691dbc8240fdf3a42d450c1042)`()` 

Creates the rendering device instance.

#### `public  `[`~AScene`](#class_a_scene_1a9faf7f1a271327227e83627432d0b210)`()` 

#### `public inline virtual void `[`start`](#class_a_scene_1a77ac53926122cd9db819e1e4cad5c182)`()` 

This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.

#### `public inline virtual void `[`update`](#class_a_scene_1a5a95b5d991630b8e5477b501577e1c7d)`(double dt)` 

This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

#### Parameters
* `dt` Delta Time of the frame in seconds

#### `public inline virtual void `[`destroy`](#class_a_scene_1a815f7bed74e832cd100d6857d4df2ab5)`()` 

This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.

#### `public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_scene_1a3d7a50f9a2fe40a282c7a26f0a9df5f0)`()` 

Creates and registers a new game object. The name of this game object will be the empty string. Please note that you need to keep your own pointer to this object when you want to update it later.

#### Returns
A new gameObject instance.

#### `public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`instantiate`](#class_a_scene_1a220e42f764bd4fc37a73d76e4a48a0b9)`(const std::string name)` 

Creates and registers a new game object. Please note that you need to keep your own pointer to this object when you want to update it later.

#### Parameters
* `name` The name of the gameObject in the scene.

#### Returns
A new gameObject instance.

#### `protected lava::SharedDevice `[`mDevice`](#class_a_scene_1aef5b18b6523d09749dd9e68ac22f44dc) 

The device which is used to render the scene. This will be used for a number of initialization procedures.

#### `protected std::shared_ptr< `[`GeometryStore`](#class_geometry_store)` > `[`mGeometryStore`](#class_a_scene_1a37764fc0c39169109fb285383a67eae8) 

This [GeometryStore](#class_geometry_store) is used to load meshes and push them to the GPU.

#### `protected std::shared_ptr< `[`TextureStore`](#class_texture_store)` > `[`mTextureStore`](#class_a_scene_1af3491c84b7452454dcb62613271e4938) 

This [TextureStore](#class_texture_store) is used to load textures and push them to the GPU.

# class `DefaultRenderer` 

```
class DefaultRenderer
  : public GraphicsPipelineRenderer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DefaultTexturedRenderer` 

```
class DefaultTexturedRenderer
  : public GraphicsPipelineRenderer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `DreamroamScene` 

```
class DreamroamScene
  : public AScene
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`DreamroamScene`](#class_dreamroam_scene_1a3f97df4276fb8232c9349144bfbbf242)`()` | 
`public virtual void `[`start`](#class_dreamroam_scene_1a471fd303a4708b08d3a4ea4c6f6bfe18)`()` | This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.
`public virtual void `[`update`](#class_dreamroam_scene_1a317a513962ec27b9f8e170335e8da419)`(double dt)` | This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

## Members

#### `public  `[`DreamroamScene`](#class_dreamroam_scene_1a3f97df4276fb8232c9349144bfbbf242)`()` 

#### `public virtual void `[`start`](#class_dreamroam_scene_1a471fd303a4708b08d3a4ea4c6f6bfe18)`()` 

This is called right after the sceneHandler switches to the new scene. Use this to register your gameObjects, textures and components.

#### `public virtual void `[`update`](#class_dreamroam_scene_1a317a513962ec27b9f8e170335e8da419)`(double dt)` 

This is called for each frame while the scene is loaded. Can be used to call all entity systems. Note: This function should not be used to run the games logic. However, at the current time this is all you got.

#### Parameters
* `dt` Delta Time of the frame in seconds

# class `GameObject` 

```
class GameObject
  : public std::enable_shared_from_this< GameObject >
```  

A gameobject is a object in the scene. It is used as a collection of components with some additional funcionallity: Each [GameObject](#class_game_object) has a transform component which is used to store the position, the rotation and the scale of that object. GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).

Note that not every [GameObject](#class_game_object) has to be visible and support some kind of render. It can also be used to create handlers or some other singletons.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Transform`](#class_transform)` `[`transform`](#class_game_object_1ad2de7705e8d1d7b5d0014448dd13f99a) | The [Transform](#class_transform) component is assigned to each [GameObject](#class_game_object) to store position scale and rotation.
`public  `[`GameObject`](#class_game_object_1a0348e3ee2e83d56eafca7a3547f432c4)`()` | This creates a new [GameObject](#class_game_object) with the empty string as name.
`public  `[`GameObject`](#class_game_object_1a0737657696b478c7962c2a6c2f5b1bd8)`(std::string name)` | This creates a new [GameObject](#class_game_object) with a specified name.
`public void `[`addComponent`](#class_game_object_1aa4f0f1a42d622fd6c96223083e6a573b)`(std::shared_ptr< `[`AComponent`](#class_a_component)` > comp)` | This method is used to assign a component to the [GameObject](#class_game_object). Note that you have to create a lasting component (using the 'new' macro).
`public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`getParent`](#class_game_object_1ad36e10b2d28b2f4e34326244048f786c)`()` | This function returns the parent if existing. If not existing, this returns nullptr.
`public std::vector< std::shared_ptr< `[`GameObject`](#class_game_object)` > > `[`getChilds`](#class_game_object_1a7053cf0979ec793600f5c128219f0ed8)`()` | This returns a list of all child gameobjects that are assigned to this gameObject.
`public void `[`setParent`](#class_game_object_1af3d7a870032a51dea2afeaf57814a452)`(std::shared_ptr< `[`GameObject`](#class_game_object)` > obj)` | Sets the parent for this gameObject
`public void `[`addChild`](#class_game_object_1a616a561447caebf99e373ef69656748f)`(std::shared_ptr< `[`GameObject`](#class_game_object)` > obj)` | Adds a child to this gameObject
`public template<>`  <br/>`T * `[`getComponent`](#class_game_object_1a7a91297b8801e1c8ce10462c754c573a)`()` | 

## Members

#### `public `[`Transform`](#class_transform)` `[`transform`](#class_game_object_1ad2de7705e8d1d7b5d0014448dd13f99a) 

The [Transform](#class_transform) component is assigned to each [GameObject](#class_game_object) to store position scale and rotation.

Note that the Parent-Child-relation has impact on the calculations taking place in the transform instance.

#### `public  `[`GameObject`](#class_game_object_1a0348e3ee2e83d56eafca7a3547f432c4)`()` 

This creates a new [GameObject](#class_game_object) with the empty string as name.

Note that it is strongly advised to create a [GameObject](#class_game_object) using the instantiate() method offered by the Scene or the component class.

#### `public  `[`GameObject`](#class_game_object_1a0737657696b478c7962c2a6c2f5b1bd8)`(std::string name)` 

This creates a new [GameObject](#class_game_object) with a specified name.

#### Parameters
* `name` The name of the new [GameObject](#class_game_object)

Note that it is strongly advised to create a [GameObject](#class_game_object) using the instantiate() method offered by the Scene or the component class.

#### `public void `[`addComponent`](#class_game_object_1aa4f0f1a42d622fd6c96223083e6a573b)`(std::shared_ptr< `[`AComponent`](#class_a_component)` > comp)` 

This method is used to assign a component to the [GameObject](#class_game_object). Note that you have to create a lasting component (using the 'new' macro).

```cpp
auto comp = std::make_shared<RotateObjectComponent>();
  gameObject->addComponent(comp);
```

#### Parameters
* `comp` The component you want to add.

#### `public std::shared_ptr< `[`GameObject`](#class_game_object)` > `[`getParent`](#class_game_object_1ad36e10b2d28b2f4e34326244048f786c)`()` 

This function returns the parent if existing. If not existing, this returns nullptr.

#### Returns
The parent gameObject if existing, else nullptr

#### `public std::vector< std::shared_ptr< `[`GameObject`](#class_game_object)` > > `[`getChilds`](#class_game_object_1a7053cf0979ec793600f5c128219f0ed8)`()` 

This returns a list of all child gameobjects that are assigned to this gameObject.

#### Returns
A list of all childs, or an empty list

#### `public void `[`setParent`](#class_game_object_1af3d7a870032a51dea2afeaf57814a452)`(std::shared_ptr< `[`GameObject`](#class_game_object)` > obj)` 

Sets the parent for this gameObject

#### Parameters
* `obj` the parent for this object

#### `public void `[`addChild`](#class_game_object_1a616a561447caebf99e373ef69656748f)`(std::shared_ptr< `[`GameObject`](#class_game_object)` > obj)` 

Adds a child to this gameObject

#### Parameters
* `obj` The new child

#### `public template<>`  <br/>`T * `[`getComponent`](#class_game_object_1a7a91297b8801e1c8ce10462c754c573a)`()` 

# class `Geometry` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Geometry`](#class_geometry_1a6194151def9f47dda17d29e7a3ab48e3)`(const lava::geometry::SharedGeometry geometry)` | 
`public void `[`draw`](#class_geometry_1a56c1551d1f2ff3c8addad25d1a7ba9e2)`(lava::InlineSubpass & pass)` | 

## Members

#### `public  `[`Geometry`](#class_geometry_1a6194151def9f47dda17d29e7a3ab48e3)`(const lava::geometry::SharedGeometry geometry)` 

#### `public void `[`draw`](#class_geometry_1a56c1551d1f2ff3c8addad25d1a7ba9e2)`(lava::InlineSubpass & pass)` 

# class `GeometryLoader` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`GeometryLoader`](#class_geometry_loader_1a097298280328323f2f19bf8c5339c010)`()` | 
`public void `[`loadRawMulti`](#class_geometry_loader_1a778d9b368691d4d914df2b5a509ca519)`(const std::string & filename,std::vector< std::vector< `[`VertexAttributes`](#struct_vertex_attributes)` >> & verticesPerMesh,std::vector< std::vector< uint32_t >> & indicesPerMesh,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | Loads all meshes inside the given file separated and stores the vertex data and indices inside the given vectors. 'verticesPerMesh' and 'indicesPerMesh' will first be cleared, then filled with the data read from the file.
`public void `[`loadRawCombined`](#class_geometry_loader_1a69bf2b6698454ac329e5cc129270c9fb)`(const std::string & filename,std::vector< `[`VertexAttributes`](#struct_vertex_attributes)` > & vertices,std::vector< uint32_t > & indices)` | 
`public std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`meshesFromFile`](#class_geometry_loader_1aee8401497ae0d8d3eec0b9e218345b43)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | 
`public std::shared_ptr< lava::geometry::GeometryData > `[`singleMeshFromFile`](#class_geometry_loader_1a0fdf81e745398fb778858ddf0a356284)`(const std::string & filename)` | 
`public template<>`  <br/>`inline std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`loadMulti`](#class_geometry_loader_1aa859fe90b77e25112ae6a9bfb9e1f4cf)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` | 
`public template<>`  <br/>`inline std::shared_ptr< lava::geometry::GeometryData > `[`loadCombined`](#class_geometry_loader_1a08fc5eeae256ea0256268c9fc8ae8cd7)`(std::string const & filename)` | 
`public void `[`printNodeInfo_recursive`](#class_geometry_loader_1ac43feebbb35daa031a603d45255bebbd)`(const aiScene * scene,const aiNode * node) const` | 
`public void `[`printSceneInfo`](#class_geometry_loader_1a5039e0f522233669e33cb09f1038fec4)`(const aiScene * scene) const` | 
`typedef `[`VertexCB`](#class_geometry_loader_1ab54c693c5a9bf455acd43e39ad7ee08f) | 

## Members

#### `public  `[`GeometryLoader`](#class_geometry_loader_1a097298280328323f2f19bf8c5339c010)`()` 

#### `public void `[`loadRawMulti`](#class_geometry_loader_1a778d9b368691d4d914df2b5a509ca519)`(const std::string & filename,std::vector< std::vector< `[`VertexAttributes`](#struct_vertex_attributes)` >> & verticesPerMesh,std::vector< std::vector< uint32_t >> & indicesPerMesh,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

Loads all meshes inside the given file separated and stores the vertex data and indices inside the given vectors. 'verticesPerMesh' and 'indicesPerMesh' will first be cleared, then filled with the data read from the file.

#### `public void `[`loadRawCombined`](#class_geometry_loader_1a69bf2b6698454ac329e5cc129270c9fb)`(const std::string & filename,std::vector< `[`VertexAttributes`](#struct_vertex_attributes)` > & vertices,std::vector< uint32_t > & indices)` 

#### `public std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`meshesFromFile`](#class_geometry_loader_1aee8401497ae0d8d3eec0b9e218345b43)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

#### `public std::shared_ptr< lava::geometry::GeometryData > `[`singleMeshFromFile`](#class_geometry_loader_1a0fdf81e745398fb778858ddf0a356284)`(const std::string & filename)` 

#### `public template<>`  <br/>`inline std::vector< std::shared_ptr< lava::geometry::GeometryData > > `[`loadMulti`](#class_geometry_loader_1aa859fe90b77e25112ae6a9bfb9e1f4cf)`(const std::string & filename,std::vector< unsigned int > & meshMaterialIndices,std::vector< std::string > & meshNames)` 

#### `public template<>`  <br/>`inline std::shared_ptr< lava::geometry::GeometryData > `[`loadCombined`](#class_geometry_loader_1a08fc5eeae256ea0256268c9fc8ae8cd7)`(std::string const & filename)` 

#### `public void `[`printNodeInfo_recursive`](#class_geometry_loader_1ac43feebbb35daa031a603d45255bebbd)`(const aiScene * scene,const aiNode * node) const` 

#### `public void `[`printSceneInfo`](#class_geometry_loader_1a5039e0f522233669e33cb09f1038fec4)`(const aiScene * scene) const` 

#### `typedef `[`VertexCB`](#class_geometry_loader_1ab54c693c5a9bf455acd43e39ad7ee08f) 

# class `GeometryStore` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`GeometryStore`](#class_geometry_store_1a5bea5cb9e95e210d501fd8541c06c2d6)`(lava::SharedDevice device)` | 
`public void `[`registerGeometry`](#class_geometry_store_1a662ad163346b390a48862e9f7a06395d)`(std::shared_ptr< `[`Geometry`](#class_geometry)` > obj,std::string name)` | 
`public void `[`registerGeometryFromData`](#class_geometry_store_1a1902b5f6784925acca46a53933ac34f5)`(lava::geometry::SharedGeometryData geomData,std::string name)` | 
`public void `[`registerGeometryFromFileSingle`](#class_geometry_store_1a9b890cdf2a66a42f4b0770f526b0385a)`(std::string filePath,std::string name)` | 
`public void `[`registerGeometryFromFileMulti`](#class_geometry_store_1ac1a8882862871bce334a6be7f6fe873f)`(std::string filePath,std::string namePrefix)` | 
`public inline std::shared_ptr< `[`Geometry`](#class_geometry)` > `[`getGeometryWithName`](#class_geometry_store_1a2cbce96ac819c35787a6f524281b6191)`(std::string name) const` | 
`public inline size_t `[`getLayerCountWithName`](#class_geometry_store_1a6ce5a8c11d179ac4346a66a3e25a9205)`(std::string name) const` | 

## Members

#### `public  `[`GeometryStore`](#class_geometry_store_1a5bea5cb9e95e210d501fd8541c06c2d6)`(lava::SharedDevice device)` 

#### `public void `[`registerGeometry`](#class_geometry_store_1a662ad163346b390a48862e9f7a06395d)`(std::shared_ptr< `[`Geometry`](#class_geometry)` > obj,std::string name)` 

#### `public void `[`registerGeometryFromData`](#class_geometry_store_1a1902b5f6784925acca46a53933ac34f5)`(lava::geometry::SharedGeometryData geomData,std::string name)` 

#### `public void `[`registerGeometryFromFileSingle`](#class_geometry_store_1a9b890cdf2a66a42f4b0770f526b0385a)`(std::string filePath,std::string name)` 

#### `public void `[`registerGeometryFromFileMulti`](#class_geometry_store_1ac1a8882862871bce334a6be7f6fe873f)`(std::string filePath,std::string namePrefix)` 

#### `public inline std::shared_ptr< `[`Geometry`](#class_geometry)` > `[`getGeometryWithName`](#class_geometry_store_1a2cbce96ac819c35787a6f524281b6191)`(std::string name) const` 

#### `public inline size_t `[`getLayerCountWithName`](#class_geometry_store_1a6ce5a8c11d179ac4346a66a3e25a9205)`(std::string name) const` 

# class `GlobalSettings` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `GraphicsPipelineFactory` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `GraphicsPipelineRenderer` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer_1a62793a25bff6253222047558fcdc3680)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` | 
`public inline virtual  `[`~GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer_1aa7e659e0a4869f2da0281c46115b7ca4)`()` | 
`public void `[`prepareRendering`](#class_graphics_pipeline_renderer_1ab00f69af656d6889d15613f627fc5267)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` | 
`public void `[`renderGameObjects`](#class_graphics_pipeline_renderer_1a42bda88dfd216fc11da6a4f027d1facc)`(const std::vector< std::shared_ptr< `[`GameObject`](#class_game_object)` >> gos)` | 
`protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_graphics_pipeline_renderer_1ac7e9d1bad6eea99617a338af88cd0dfa) | 
`protected lava::SharedPipelineLayout `[`mLayout`](#class_graphics_pipeline_renderer_1a4c795533113527fcfe985789976f5dd5) | 
`protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_graphics_pipeline_renderer_1a3d7d4442a63777c5845b9e7436cf2f49) | 
`protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_graphics_pipeline_renderer_1a385aefa7694f34e07a35ddedbc094ddd) | 
`protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_graphics_pipeline_renderer_1a72319a385bd7f43510aa307b19ba8619) | 

## Members

#### `public  explicit `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer_1a62793a25bff6253222047558fcdc3680)`(std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` >,lava::SharedGraphicsPipeline pipeline,lava::SharedPipelineLayout layout)` 

#### `public inline virtual  `[`~GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer_1aa7e659e0a4869f2da0281c46115b7ca4)`()` 

#### `public void `[`prepareRendering`](#class_graphics_pipeline_renderer_1ab00f69af656d6889d15613f627fc5267)`(lava::InlineSubpass * sub,lava::SharedDescriptorSet cameraDescriptor)` 

#### `public void `[`renderGameObjects`](#class_graphics_pipeline_renderer_1a42bda88dfd216fc11da6a4f027d1facc)`(const std::vector< std::shared_ptr< `[`GameObject`](#class_game_object)` >> gos)` 

#### `protected lava::SharedGraphicsPipeline `[`mPipeline`](#class_graphics_pipeline_renderer_1ac7e9d1bad6eea99617a338af88cd0dfa) 

#### `protected lava::SharedPipelineLayout `[`mLayout`](#class_graphics_pipeline_renderer_1a4c795533113527fcfe985789976f5dd5) 

#### `protected lava::SharedDescriptorSet `[`mCameraDescriptor`](#class_graphics_pipeline_renderer_1a3d7d4442a63777c5845b9e7436cf2f49) 

#### `protected lava::InlineSubpass * `[`mCurrentSubpass`](#class_graphics_pipeline_renderer_1a385aefa7694f34e07a35ddedbc094ddd) 

#### `protected std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mAdvancedPipeline`](#class_graphics_pipeline_renderer_1a72319a385bd7f43510aa307b19ba8619) 

# class `RenderComponent` 

```
class RenderComponent
  : public AComponent
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::shared_ptr< `[`Geometry`](#class_geometry)` > `[`geometryObj`](#class_render_component_1ac60b5fcc566b997b315e51e20f5a37b7) | 
`public bool `[`isTransparent`](#class_render_component_1a632e431f784021dd6d069d7b35d9289f) | 
`public float `[`alpha`](#class_render_component_1a49a96127f299b2b44bbb7e7514abec93) | 
`public bool `[`hasTexture`](#class_render_component_1a78d27d9b9b0aa15ca56c7132ae385fbd) | 
`public std::shared_ptr< `[`Texture`](#class_texture)` > `[`textureObj`](#class_render_component_1aa6ff03003d3b7a9a77f1a9a1436b394b) | 
`public bool `[`active`](#class_render_component_1a26c2a45bd339072f8bf418e0ad3dd98f) | 
`public bool `[`isThrowingShadow`](#class_render_component_1ae1ec1b9131de90ac9f5d5fdfb6973c51) | 
`public inline  `[`RenderComponent`](#class_render_component_1a1bfbe186278dc7528788aea84f976b6c)`()` | 

## Members

#### `public std::shared_ptr< `[`Geometry`](#class_geometry)` > `[`geometryObj`](#class_render_component_1ac60b5fcc566b997b315e51e20f5a37b7) 

#### `public bool `[`isTransparent`](#class_render_component_1a632e431f784021dd6d069d7b35d9289f) 

#### `public float `[`alpha`](#class_render_component_1a49a96127f299b2b44bbb7e7514abec93) 

#### `public bool `[`hasTexture`](#class_render_component_1a78d27d9b9b0aa15ca56c7132ae385fbd) 

#### `public std::shared_ptr< `[`Texture`](#class_texture)` > `[`textureObj`](#class_render_component_1aa6ff03003d3b7a9a77f1a9a1436b394b) 

#### `public bool `[`active`](#class_render_component_1a26c2a45bd339072f8bf418e0ad3dd98f) 

#### `public bool `[`isThrowingShadow`](#class_render_component_1ae1ec1b9131de90ac9f5d5fdfb6973c51) 

#### `public inline  `[`RenderComponent`](#class_render_component_1a1bfbe186278dc7528788aea84f976b6c)`()` 

# class `SceneHandler` 

A [SceneHandler](#class_scene_handler) is the manager of the game engine. It implements the singleton pattern and provides getters for the current scene, the switch scene method and more.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double `[`mMouseX`](#class_scene_handler_1a829a9d52683e93cf2cb0bf37ae51d194) | 
`public double `[`mMouseY`](#class_scene_handler_1aaf4572e90087d0c406465c3099adb15d) | 
`public int `[`mWindowWidth`](#class_scene_handler_1a698a688e22bdbbd4b8ad03147d11f32e) | 
`public int `[`mWindowHeight`](#class_scene_handler_1a6ab512a2254b1b01706bdef15111df80) | 
`public bool `[`mCatchCursor`](#class_scene_handler_1ab18850859017a119206c62b3f40a1b01) | 
`public float `[`mCameraMoveSpeed`](#class_scene_handler_1a318b61d9af2a9b42fff3ba1faec42e67) | 
`public float `[`mCameraMoveSpeedFactor`](#class_scene_handler_1a2dbea8a15da1bdd78592ca7689e63a95) | 
`public float `[`mCameraTurnSpeed`](#class_scene_handler_1a8f09c4ba42bfc8c0ef4ae972469180fb) | 
`public float `[`mCameraScrollSpeed`](#class_scene_handler_1ab71d9eae296d073b352ea1f0f8120172) | 
`public double `[`mMouseLastX`](#class_scene_handler_1a9618375e5a0e0746af3f660cf0709403) | 
`public double `[`mMouseLastY`](#class_scene_handler_1acfbd93128f91f1585424fbcc271d3187) | 
`public double `[`mDoubleClickTime`](#class_scene_handler_1a6631a32ebc9f232d6abe435f527d75cf) | 
`public int `[`mClickCount`](#class_scene_handler_1abdd1c0307b9c904f78c388cc81d39300) | 
`public int `[`mClickButton`](#class_scene_handler_1a5a91f3ba9bc1c7d8463b766ce3656013) | 
`public glm::vec2 `[`mClickPos`](#class_scene_handler_1acfc6eefc21d2046cacb45e894626f186) | 
`public lava::Stopwatch `[`mClickTimer`](#class_scene_handler_1afa02d0aa30a03110892e244834fd98c6) | 
`public lava::SharedBuffer `[`mViewProjBufferPrePass`](#class_scene_handler_1acf57d37593efd7efc9c880e7cbbb8063) | 
`public lava::SharedBuffer `[`mViewProjBufferForwardPass`](#class_scene_handler_1ae2ca388bf940a76c08858a19edb17b39) | 
`public lava::SharedDescriptorSetLayout `[`mViewProjDescriptorSetLayout`](#class_scene_handler_1ac50957c22e522b22887c5288ab8dca9c) | 
`public lava::SharedDescriptorSet `[`mViewProjDescriptorForward`](#class_scene_handler_1a09fa5a0b2d385e685a26e13e75e608ea) | 
`public lava::SharedDescriptorSet `[`mViewProjDescriptorPre`](#class_scene_handler_1a481718eae6ca13bb3a10f903ac8cb38f) | 
`public std::vector< std::shared_ptr< `[`AScene`](#class_a_scene)` > > `[`scenes`](#class_scene_handler_1a18817e9d063650351a324cee37a8ac9b) | 
`public std::shared_ptr< `[`AScene`](#class_a_scene)` > `[`curScene`](#class_scene_handler_1a3b612a0f6ab8ad02f44ee2f63cbbfb59) | 
`public std::shared_ptr< lava::features::GlfwOutput > `[`mGlfwOutput`](#class_scene_handler_1ac3cfa8f0105e72c77b0d5fe73790b904) | 
`public std::shared_ptr< lava::features::Validation > `[`mValidation`](#class_scene_handler_1a1a4a1ae6095df5337ccc4dd57defd4f0) | 
`public std::shared_ptr< lava::features::GlfwWindow > `[`mWindow`](#class_scene_handler_1a602eb5925c576d9111f2310edc4e2290) | 
`public lava::SharedDevice `[`mDevice`](#class_scene_handler_1a4b645c2de9bf152438bf71a87f78269d) | 
`public lava::SharedPipelineLayout `[`mPlLayout`](#class_scene_handler_1a9c8e8a116e5ea0723a9e423b73483549) | 
`public std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mPipeline`](#class_scene_handler_1a6cb9f8c0635432ba570e11ba84925915) | 
`public std::vector< lava::SharedFramebuffer > `[`companionWindowFBO`](#class_scene_handler_1a54d71b92bded351fd4b51a25283acb6d) | 
`public std::shared_ptr< lava::features::GlfwOutput > `[`getGlfwOutput`](#class_scene_handler_1a06af644644384175f49eeb3a328801ba)`() const` | 
`public void `[`run`](#class_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` | 
`public void `[`updateCamera`](#class_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` | 
`public void `[`setupPipeline`](#class_scene_handler_1aa840550cfbac55ffbf68775f8b194192)`(const lava::SharedDescriptorSetLayout textureLayout)` | 
`public void `[`getFrustumCorners`](#class_scene_handler_1aa1bb88527ddca127ac396d1e3d703e65)`(std::vector< glm::vec4 > & corners,glm::mat4 projection)` | 
`public std::tuple< glm::mat4, glm::vec3, glm::vec3 > `[`rotateCameraFrustrumCornersToLightSpace`](#class_scene_handler_1a0a21e13bbaa0593aa3d6583da619ac95)`(glm::vec3 forward,glm::vec3 camPosition,std::vector< glm::vec4 > corners,glm::vec3 upDirection)` | 
`public void `[`setupGlfwCallbacks`](#class_scene_handler_1a8a72d73b454dd9de9b96adebe938c7d9)`()` | 
`public  `[`SceneHandler`](#class_scene_handler_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` | Creates a new instance of the scene handler. Should only be called ONCE by the main function.
`public  `[`~SceneHandler`](#class_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mOpaqueUntextured`](#class_scene_handler_1a80f27534c6a05848b05cbbb824b8b2e8) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mOpaqueTextured`](#class_scene_handler_1abd556642a27208d31c9e5acff5e5b897) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mTransparendUntextured`](#class_scene_handler_1a3824fcb4f45c85ade0c416e966e6b3bb) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mTransparendTextured`](#class_scene_handler_1aeb44d8bd709153fdbd356b377a9deaa0) | 
`protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mShadowMap`](#class_scene_handler_1ad589a512a998bda62c9036e586973088) | 

## Members

#### `public double `[`mMouseX`](#class_scene_handler_1a829a9d52683e93cf2cb0bf37ae51d194) 

#### `public double `[`mMouseY`](#class_scene_handler_1aaf4572e90087d0c406465c3099adb15d) 

#### `public int `[`mWindowWidth`](#class_scene_handler_1a698a688e22bdbbd4b8ad03147d11f32e) 

#### `public int `[`mWindowHeight`](#class_scene_handler_1a6ab512a2254b1b01706bdef15111df80) 

#### `public bool `[`mCatchCursor`](#class_scene_handler_1ab18850859017a119206c62b3f40a1b01) 

#### `public float `[`mCameraMoveSpeed`](#class_scene_handler_1a318b61d9af2a9b42fff3ba1faec42e67) 

#### `public float `[`mCameraMoveSpeedFactor`](#class_scene_handler_1a2dbea8a15da1bdd78592ca7689e63a95) 

#### `public float `[`mCameraTurnSpeed`](#class_scene_handler_1a8f09c4ba42bfc8c0ef4ae972469180fb) 

#### `public float `[`mCameraScrollSpeed`](#class_scene_handler_1ab71d9eae296d073b352ea1f0f8120172) 

#### `public double `[`mMouseLastX`](#class_scene_handler_1a9618375e5a0e0746af3f660cf0709403) 

#### `public double `[`mMouseLastY`](#class_scene_handler_1acfbd93128f91f1585424fbcc271d3187) 

#### `public double `[`mDoubleClickTime`](#class_scene_handler_1a6631a32ebc9f232d6abe435f527d75cf) 

#### `public int `[`mClickCount`](#class_scene_handler_1abdd1c0307b9c904f78c388cc81d39300) 

#### `public int `[`mClickButton`](#class_scene_handler_1a5a91f3ba9bc1c7d8463b766ce3656013) 

#### `public glm::vec2 `[`mClickPos`](#class_scene_handler_1acfc6eefc21d2046cacb45e894626f186) 

#### `public lava::Stopwatch `[`mClickTimer`](#class_scene_handler_1afa02d0aa30a03110892e244834fd98c6) 

#### `public lava::SharedBuffer `[`mViewProjBufferPrePass`](#class_scene_handler_1acf57d37593efd7efc9c880e7cbbb8063) 

#### `public lava::SharedBuffer `[`mViewProjBufferForwardPass`](#class_scene_handler_1ae2ca388bf940a76c08858a19edb17b39) 

#### `public lava::SharedDescriptorSetLayout `[`mViewProjDescriptorSetLayout`](#class_scene_handler_1ac50957c22e522b22887c5288ab8dca9c) 

#### `public lava::SharedDescriptorSet `[`mViewProjDescriptorForward`](#class_scene_handler_1a09fa5a0b2d385e685a26e13e75e608ea) 

#### `public lava::SharedDescriptorSet `[`mViewProjDescriptorPre`](#class_scene_handler_1a481718eae6ca13bb3a10f903ac8cb38f) 

#### `public std::vector< std::shared_ptr< `[`AScene`](#class_a_scene)` > > `[`scenes`](#class_scene_handler_1a18817e9d063650351a324cee37a8ac9b) 

#### `public std::shared_ptr< `[`AScene`](#class_a_scene)` > `[`curScene`](#class_scene_handler_1a3b612a0f6ab8ad02f44ee2f63cbbfb59) 

#### `public std::shared_ptr< lava::features::GlfwOutput > `[`mGlfwOutput`](#class_scene_handler_1ac3cfa8f0105e72c77b0d5fe73790b904) 

#### `public std::shared_ptr< lava::features::Validation > `[`mValidation`](#class_scene_handler_1a1a4a1ae6095df5337ccc4dd57defd4f0) 

#### `public std::shared_ptr< lava::features::GlfwWindow > `[`mWindow`](#class_scene_handler_1a602eb5925c576d9111f2310edc4e2290) 

#### `public lava::SharedDevice `[`mDevice`](#class_scene_handler_1a4b645c2de9bf152438bf71a87f78269d) 

#### `public lava::SharedPipelineLayout `[`mPlLayout`](#class_scene_handler_1a9c8e8a116e5ea0723a9e423b73483549) 

#### `public std::shared_ptr< `[`lava::pipeline::AdvancedRenderingPipeline`](#classlava_1_1pipeline_1_1_advanced_rendering_pipeline)` > `[`mPipeline`](#class_scene_handler_1a6cb9f8c0635432ba570e11ba84925915) 

#### `public std::vector< lava::SharedFramebuffer > `[`companionWindowFBO`](#class_scene_handler_1a54d71b92bded351fd4b51a25283acb6d) 

#### `public std::shared_ptr< lava::features::GlfwOutput > `[`getGlfwOutput`](#class_scene_handler_1a06af644644384175f49eeb3a328801ba)`() const` 

#### `public void `[`run`](#class_scene_handler_1aa9ec234700b37ef3c8ba2c3530708305)`()` 

#### `public void `[`updateCamera`](#class_scene_handler_1a64a8d0f828f9637a98ac0a888e9314d6)`(double elapsedSeconds)` 

#### `public void `[`setupPipeline`](#class_scene_handler_1aa840550cfbac55ffbf68775f8b194192)`(const lava::SharedDescriptorSetLayout textureLayout)` 

#### `public void `[`getFrustumCorners`](#class_scene_handler_1aa1bb88527ddca127ac396d1e3d703e65)`(std::vector< glm::vec4 > & corners,glm::mat4 projection)` 

#### `public std::tuple< glm::mat4, glm::vec3, glm::vec3 > `[`rotateCameraFrustrumCornersToLightSpace`](#class_scene_handler_1a0a21e13bbaa0593aa3d6583da619ac95)`(glm::vec3 forward,glm::vec3 camPosition,std::vector< glm::vec4 > corners,glm::vec3 upDirection)` 

#### `public void `[`setupGlfwCallbacks`](#class_scene_handler_1a8a72d73b454dd9de9b96adebe938c7d9)`()` 

#### `public  `[`SceneHandler`](#class_scene_handler_1a99fe4ea2e3e102ec3beeb448b6878cc5)`()` 

Creates a new instance of the scene handler. Should only be called ONCE by the main function.

This should not be used to create a new instance. Instead, please use the GetInstance method.

This needs to be public in order to create a new instance using std::make_shared in the GetInstance method.

#### Returns
A new [SceneHandler](#class_scene_handler)

#### `public  `[`~SceneHandler`](#class_scene_handler_1a2c9ece9bef2822697e77167ec3c5107e)`()` 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mOpaqueUntextured`](#class_scene_handler_1a80f27534c6a05848b05cbbb824b8b2e8) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mOpaqueTextured`](#class_scene_handler_1abd556642a27208d31c9e5acff5e5b897) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mTransparendUntextured`](#class_scene_handler_1a3824fcb4f45c85ade0c416e966e6b3bb) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mTransparendTextured`](#class_scene_handler_1aeb44d8bd709153fdbd356b377a9deaa0) 

#### `protected std::shared_ptr< `[`GraphicsPipelineRenderer`](#class_graphics_pipeline_renderer)` > `[`mShadowMap`](#class_scene_handler_1ad589a512a998bda62c9036e586973088) 

# class `Texture` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Texture`](#class_texture_1a1c4d733f622ba2cf092cdd2d37fa8ad9)`(lava::SharedDescriptorSet descriptorSet)` | 
`public inline lava::SharedDescriptorSet `[`getDescriptorSet`](#class_texture_1a66ad35369397b049ae3c9b127db8aa71)`()` | 

## Members

#### `public  `[`Texture`](#class_texture_1a1c4d733f622ba2cf092cdd2d37fa8ad9)`(lava::SharedDescriptorSet descriptorSet)` 

#### `public inline lava::SharedDescriptorSet `[`getDescriptorSet`](#class_texture_1a66ad35369397b049ae3c9b127db8aa71)`()` 

# class `TextureStore` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TextureStore`](#class_texture_store_1a5faa7af45ca80f42d80c38ee6f45531a)`(lava::SharedDevice device)` | 
`public  `[`TextureStore`](#class_texture_store_1a896214fbe95e96b69382764136d1dbd5)`(lava::SharedDevice device,std::vector< std::pair< std::string, std::string >> imageTexturePathsAndNames)` | 
`public  `[`~TextureStore`](#class_texture_store_1a15a3cccbdaf62d8ae70d403b851704a2)`()` | 
`public inline std::shared_ptr< `[`Texture`](#class_texture)` > `[`getTextureWithName`](#class_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` | 
`public inline lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` | 

## Members

#### `public  `[`TextureStore`](#class_texture_store_1a5faa7af45ca80f42d80c38ee6f45531a)`(lava::SharedDevice device)` 

#### `public  `[`TextureStore`](#class_texture_store_1a896214fbe95e96b69382764136d1dbd5)`(lava::SharedDevice device,std::vector< std::pair< std::string, std::string >> imageTexturePathsAndNames)` 

#### `public  `[`~TextureStore`](#class_texture_store_1a15a3cccbdaf62d8ae70d403b851704a2)`()` 

#### `public inline std::shared_ptr< `[`Texture`](#class_texture)` > `[`getTextureWithName`](#class_texture_store_1a8ab8700801b1cb3808ab4e4d0bd576a7)`(std::string name) const` 

#### `public inline lava::SharedDescriptorSetLayout `[`getTextureLayout`](#class_texture_store_1aae2530d3fee2723caa8426f3b731a6fd)`() const` 

# class `Transform` 

This class is a part of each [GameObject](#class_game_object) which stores rotation position and a three dimensional scale value for the object. It also provides a methods for creating (for the rendering of the object) the model matrix.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::vec3 `[`position`](#class_transform_1aa357f8eb780f4ef195027d1c636baa36) | The position of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)
`public glm::vec3 `[`rotation`](#class_transform_1aefd4a6bf41e01cf5898fd57430d93dea) | The rotation of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)
`public glm::vec3 `[`scale`](#class_transform_1acf6ab53778448fd2f2d8a367c14e7f95) | The scale value of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)
`public inline  `[`Transform`](#class_transform_1ad9212277021d58db6bccee91b7298f8f)`(glm::vec3 pos,glm::vec3 rot,glm::vec3 scale)` | This creates a new [Transform](#class_transform) object where position and rotation can be specified (by default they are 0). This constructor can also be used with a specified scale value (which by default is 1).
`public glm::mat4 `[`getModelMatrix`](#class_transform_1af0671190bf3f3b4e5cdd8ccb23c05a7a)`()` | This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).
`public glm::mat4 `[`getScaleMatrix`](#class_transform_1adbeb9e27f8f0616336c7101c2d925ee3)`()` | This method returns a matrix that scales the object using this [Transform](#class_transform)
`public glm::mat4 `[`getRotationMatrix`](#class_transform_1a716f060a18db568786ae023e8c02597c)`()` | This method returns a matrix that rotates the object using this [Transform](#class_transform)
`public glm::mat4 `[`getPosMatrix`](#class_transform_1a39100fc47750475ca69529a346885a28)`()` | This method returns a matrix that positions the object using this [Transform](#class_transform)
`protected `[`GameObject`](#class_game_object)` * `[`gameObject`](#class_transform_1aeae6186d24a6968ab1cc423e6275edd0) | 

## Members

#### `public glm::vec3 `[`position`](#class_transform_1aa357f8eb780f4ef195027d1c636baa36) 

The position of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)

#### `public glm::vec3 `[`rotation`](#class_transform_1aefd4a6bf41e01cf5898fd57430d93dea) 

The rotation of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)

#### `public glm::vec3 `[`scale`](#class_transform_1acf6ab53778448fd2f2d8a367c14e7f95) 

The scale value of the [Transform](#class_transform) and the corresponding [GameObject](#class_game_object)

#### `public inline  `[`Transform`](#class_transform_1ad9212277021d58db6bccee91b7298f8f)`(glm::vec3 pos,glm::vec3 rot,glm::vec3 scale)` 

This creates a new [Transform](#class_transform) object where position and rotation can be specified (by default they are 0). This constructor can also be used with a specified scale value (which by default is 1).

#### Parameters
* `pos` The three dimensional position of the object

* `rot` The three dimensional rotation of the object

* `scale` The three dimensional scale of the object

Note that this class can be used without a [GameObject](#class_game_object) but will in this case not be used in the scene.

#### `public glm::mat4 `[`getModelMatrix`](#class_transform_1af0671190bf3f3b4e5cdd8ccb23c05a7a)`()` 

This method returns a model matrix for this transform object. Therefore the position matrix the rotation matrix and the scale matrix is multiplied. The parent transform is used to calculate this matrix (if and only if existing).

#### Returns
Model matrix (with parent transform)

#### `public glm::mat4 `[`getScaleMatrix`](#class_transform_1adbeb9e27f8f0616336c7101c2d925ee3)`()` 

This method returns a matrix that scales the object using this [Transform](#class_transform)

#### Returns
The scale matrix

#### `public glm::mat4 `[`getRotationMatrix`](#class_transform_1a716f060a18db568786ae023e8c02597c)`()` 

This method returns a matrix that rotates the object using this [Transform](#class_transform)

#### Returns
The rotation matrix

#### `public glm::mat4 `[`getPosMatrix`](#class_transform_1a39100fc47750475ca69529a346885a28)`()` 

This method returns a matrix that positions the object using this [Transform](#class_transform)

#### Returns
The position matrix

#### `protected `[`GameObject`](#class_game_object)` * `[`gameObject`](#class_transform_1aeae6186d24a6968ab1cc423e6275edd0) 

# struct `CameraData` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`view`](#struct_camera_data_1a8de2d77a7cc255ff966ce6fc0b49a241) | 
`public glm::mat4 `[`proj`](#struct_camera_data_1a8dbe368104e1451a43537ef37076b54f) | 

## Members

#### `public glm::mat4 `[`view`](#struct_camera_data_1a8de2d77a7cc255ff966ce6fc0b49a241) 

#### `public glm::mat4 `[`proj`](#struct_camera_data_1a8dbe368104e1451a43537ef37076b54f) 

# struct `PushConstants` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`modelMatrix`](#struct_push_constants_1a5c0b750e93115e7baea7455974f7c780) | 
`public glm::mat4 `[`normalMatrix`](#struct_push_constants_1ad9c7f0a207a5dcf2ee4f97ecd82fcfad) | 
`public float `[`alpha`](#struct_push_constants_1a4bae60ad240d52473f0b6dcf130075e9) | 

## Members

#### `public glm::mat4 `[`modelMatrix`](#struct_push_constants_1a5c0b750e93115e7baea7455974f7c780) 

#### `public glm::mat4 `[`normalMatrix`](#struct_push_constants_1ad9c7f0a207a5dcf2ee4f97ecd82fcfad) 

#### `public float `[`alpha`](#struct_push_constants_1a4bae60ad240d52473f0b6dcf130075e9) 

# struct `ShadowMVP` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::mat4 `[`depthMVP`](#struct_shadow_m_v_p_1a8a917359bb4316a2ffdc4d72f68752ac) | 

## Members

#### `public glm::mat4 `[`depthMVP`](#struct_shadow_m_v_p_1a8a917359bb4316a2ffdc4d72f68752ac) 

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

# struct `VertexAttributes` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public glm::vec3 `[`position`](#struct_vertex_attributes_1af70e0ec9b328108063d37bddc191a34f) | 
`public glm::vec3 `[`normal`](#struct_vertex_attributes_1ac512c119920d0c7303206422c165c6d0) | 
`public glm::vec3 `[`tangent`](#struct_vertex_attributes_1a1ccbba61f80caa6c13cb326138436cdf) | 
`public glm::vec2 `[`texCoord`](#struct_vertex_attributes_1acdf67aa6acb70612060e13af4b923bfe) | 
`public glm::vec4 `[`color`](#struct_vertex_attributes_1a02161696fd49249aee9c66cec10ec797) | 

## Members

#### `public glm::vec3 `[`position`](#struct_vertex_attributes_1af70e0ec9b328108063d37bddc191a34f) 

#### `public glm::vec3 `[`normal`](#struct_vertex_attributes_1ac512c119920d0c7303206422c165c6d0) 

#### `public glm::vec3 `[`tangent`](#struct_vertex_attributes_1a1ccbba61f80caa6c13cb326138436cdf) 

#### `public glm::vec2 `[`texCoord`](#struct_vertex_attributes_1acdf67aa6acb70612060e13af4b923bfe) 

#### `public glm::vec4 `[`color`](#struct_vertex_attributes_1a02161696fd49249aee9c66cec10ec797) 

Generated by [Moxygen](https://sourcey.com/moxygen)
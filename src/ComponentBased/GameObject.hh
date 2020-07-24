#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <lava/fwd.hh>

#include "AComponent.hh"
#include "Transform.hh"

/// <summary>
/// A gameobject is a object in the scene.
/// It is used as a collection of components with some additional funcionallity:
/// Each GameObject has a transform component which is used to store the position,
/// the rotation and the scale of that object.
/// GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).
/// </summary>
/// <remarks>
/// Note that not every GameObject has to be visible and support some kind of render. It can also be used to create handlers or some other singletons.
/// </remarks>
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
  /// <summary>
  /// This creates a new GameObject with the empty string as name.
  /// </summary>
  /// <remarks>
  /// Note that it is strongly advised to create a GameObject using the instantiate() method offered by the Scene or the component class.
  /// </remarks>
  GameObject();

  /// <summary>
  /// This creates a new GameObject with a specified name.
  /// </summary>
  /// <param name="name">The name of the new GameObject</param>
  /// <remarks>
  /// Note that it is strongly advised to create a GameObject using the instantiate() method offered by the Scene or the component class.
  /// </remarks>
  GameObject(std::string name);

public:
  /// <summary>
  /// This method is used to assign a component to the GameObject.
  /// Note that you have to create a lasting component (using the 'new' macro).
  /// </summary>
  /// <example>
  /// <code>
  ///	auto comp = std::make_shared<RotateObjectComponent>();
  /// gameObject->addComponent(comp);
  /// </code>
  /// </example>
  /// <param name="comp">The component you want to add.</param>
  void addComponent(std::shared_ptr<AComponent> comp);

  /// <summary>
  /// The Transform component is assigned to each GameObject to store position scale and rotation.
  /// </summary>
  ///	<remarks>
  /// Note that the Parent-Child-relation has impact on the calculations taking place in the transform instance.
  /// </remarks>
  Transform transform;

  /// <summary>
  /// This function returns the parent if existing.
  /// If not existing, this returns nullptr.
  /// </summary>
  /// <returns>The parent gameObject if existing, else nullptr</returns>
  std::shared_ptr<GameObject> getParent();

  /// <summary>
  /// This returns a list of all child gameobjects that are assigned to this gameObject.
  /// </summary>
  /// <returns>A list of all childs, or an empty list</returns>
  std::vector<std::shared_ptr<GameObject>> getChilds();

  /// <summary>
  /// Sets the parent for this gameObject
  /// </summary>
  /// <param name="obj">the parent for this object</param>
  void setParent(std::shared_ptr<GameObject> obj);

  /// <summary>
  /// Adds a child to this gameObject
  /// </summary>
  /// <param name="obj">The new child</param>
  void addChild(std::shared_ptr<GameObject> obj);

  template <typename T>
  T *getComponent();

private:
  //The list of components for this gameObject
  std::vector<std::shared_ptr<AComponent>> components;

  friend class AScene; //The Scene is the one class that is allowed to call the following functions

  // Calls the awake function on each GameObjects
  void awake();

  // Calls the start function on each GameObjects
  void start();

  // Calls the update function on each GameObjects
  void update(double dt);

  // Calls the lateUpdate function on each GameObjects
  void lateUpdate();

  // Calls the destroy function on each GameObjects
  void destroy();

  //The name of the gameObject
  const std::string name = "";

  //A pointer to the parent of this gameObject
  std::shared_ptr<GameObject> parent = nullptr;

  //A list of gameobjects representing the childs
  std::vector<std::shared_ptr<GameObject>> childs = std::vector<std::shared_ptr<GameObject>>();

private:
  friend class AComponent; //A Component is allowed to access the currentGameObject to get a reference to it

  //A pointer to the current gameObject
  static std::shared_ptr<GameObject> currentGameObject;
};

template <typename T>
T *GameObject::getComponent()
{
  for (auto c : components)
  {
    if (auto cp = dynamic_cast<T *>(c.get()))
      return cp;
  }

  return nullptr;
}

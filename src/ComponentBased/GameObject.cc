#include "GameObject.hh"
#include "AComponent.hh"

#include <iostream>

#include <lava/fwd.hh>

using namespace lava;

std::shared_ptr<GameObject> GameObject::currentGameObject = nullptr;

GameObject::GameObject() : GameObject("")
{
}

GameObject::GameObject(std::string name)
    : name(name)
{
    transform = Transform();
    name = name;
    transform.gameObject = this;
}

void GameObject::awake()
{
    currentGameObject = shared_from_this();
    for (auto comp : components)
    {
        comp->awake();
    }
    for (auto child : childs)
    {
        child->awake();
    }

    currentGameObject = nullptr;
}

void GameObject::start()
{
    currentGameObject = shared_from_this();

    for (auto comp : components)
    {
        comp->start();
    }
    for (auto child : childs)
    {
        child->start();
    }
    currentGameObject = nullptr;
}

void GameObject::update(double dt)
{
    currentGameObject = shared_from_this();

    for (auto comp : components)
    {
        comp->update(dt);
    }
    for (auto child : childs)
    {
        child->update(dt);
    }
    currentGameObject = nullptr;
}

void GameObject::lateUpdate()
{
    currentGameObject = shared_from_this();

    for (auto comp : components)
    {
        comp->lateUpdate();
    }
    for (auto child : childs)
    {
        child->lateUpdate();
    }
    currentGameObject = nullptr;
}

void GameObject::destroy()
{
    currentGameObject = shared_from_this();

    //TODO remove all components
    for (auto comp : components)
    {
        comp->destroy();
    }
    for (auto child : childs)
    {
        child->destroy();
    }
    currentGameObject = nullptr;
}

void GameObject::addComponent(std::shared_ptr<AComponent> comp)
{
    components.push_back(comp);
    comp->gameObject = shared_from_this();
}

std::shared_ptr<GameObject> GameObject::getParent()
{
    return this->parent;
}

std::vector<std::shared_ptr<GameObject>> GameObject::getChilds()
{
    return childs;
}

void GameObject::setParent(std::shared_ptr<GameObject> obj)
{
    if (this->parent != nullptr)
    {
        std::cerr << "You are not supposed to have two parents!";
    }
    else
    {
        this->parent = obj;
        obj->childs.push_back(shared_from_this());
    }
}

void GameObject::addChild(std::shared_ptr<GameObject> obj)
{
    if (obj->parent != nullptr)
    {
        std::cerr << "You are not supposed to have two parents!";
    }
    else
    {
        childs.push_back(obj);
        obj->parent = shared_from_this();
    }
}

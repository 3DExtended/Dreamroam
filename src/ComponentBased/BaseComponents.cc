#include "BaseComponents.hh"

using namespace DCore::ComponentSystem;

glm::mat4 TransformComponent::getModelMatrix() {
    // TODO make it possible to set a parent on the entity
#if 0
	if (parent != nullptr)
	{
		return getPosMatrix() * getRotationMatrix() * getScaleMatrix() * parent->getModelMatrix();
	}
	else
	{
#endif
    return getPosMatrix() * getRotationMatrix() * getScaleMatrix();
    //}
}

glm::mat4 TransformComponent::getScaleMatrix() { return glm::scale(scale); }

glm::mat4 TransformComponent::getRotationMatrix() {
    glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
    glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

    glm::mat4 rotMat = rotX * rotY * rotZ;

    return rotMat;
}

glm::mat4 TransformComponent::getPosMatrix() {
    return glm::translate(position);
}
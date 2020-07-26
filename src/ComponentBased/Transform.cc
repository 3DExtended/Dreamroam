#include "Transform.hh"
#include "GameObject.hh"

using namespace DCore::ComponentSystem;

glm::mat4 Transform::getModelMatrix()
{
	if (gameObject != nullptr && gameObject->getParent() != nullptr)
	{
		return getPosMatrix() * getRotationMatrix() * getScaleMatrix() * gameObject->getParent()->transform.getModelMatrix();
	}
	else
	{
		return getPosMatrix() * getRotationMatrix() * getScaleMatrix();
	}
}

glm::mat4 Transform::getScaleMatrix()
{
	return glm::scale(scale);
}

glm::mat4 Transform::getRotationMatrix()
{
	glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 rotMat = rotX * rotY * rotZ;

	return rotMat;
}

glm::mat4 Transform::getPosMatrix()
{
	return glm::translate(position);
}
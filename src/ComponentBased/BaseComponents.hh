#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <string>

namespace DCore {
namespace ComponentSystem {
/// <summary>
/// This class is a part of each GameObject which stores rotation position and a
/// three dimensional scale value for the object. It also provides a methods for
/// creating (for the rendering of the object) the model matrix.
/// </summary>
struct TransformComponent {
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& pos, const glm::vec3& rot,
                       const glm::vec3&)
        : position(pos), rotation(rot), scale(scale) {}

    /// <summary>
    /// This method returns a model matrix for this transform object.
    /// Therefore the position matrix the rotation matrix and the scale matrix
    /// is multiplied. The parent transform is used to calculate this matrix (if
    /// and only if existing).
    /// </summary>
    /// <returns>Model matrix (with parent transform)</returns>
    glm::mat4 getModelMatrix();

    /// <summary>
    /// This method returns a matrix that scales the object using this Transform
    /// </summary>
    /// <returns>The scale matrix</returns>
    glm::mat4 getScaleMatrix();

    /// <summary>
    /// This method returns a matrix that rotates the object using this
    /// Transform
    /// </summary>
    /// <returns>The rotation matrix</returns>
    glm::mat4 getRotationMatrix();

    /// <summary>
    /// This method returns a matrix that positions the object using this
    /// Transform
    /// </summary>
    /// <returns>The position matrix</returns>
    glm::mat4 getPosMatrix();

    /// <summary>
    /// The position of the Transform and the corresponding GameObject
    /// </summary>
    glm::vec3 position = glm::vec3(0.0);

    /// <summary>
    /// The rotation of the Transform and the corresponding GameObject
    /// </summary>
    glm::vec3 rotation = glm::vec3(0.0);

    /// <summary>
    /// The scale value of the Transform and the corresponding GameObject
    /// </summary>
    glm::vec3 scale = glm::vec3(1.0);
};

/// <summary>
/// This component stores the name and the tags of the entity.
/// </summary>
struct TagComponent {
    /// <summary>
    /// The name of the entity this component is attatched to.
    /// </summary>
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag) : Tag(tag) {}
};
}  // namespace ComponentSystem
}  // namespace DCore
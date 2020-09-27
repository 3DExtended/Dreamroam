#pragma once
#include <entt/entt.hpp>
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
                       const glm::vec3& scale)
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
    /// Please note that those euler angles are in radians and not in degrees.
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

/// <summary>
/// This component is used to identify the player and allows to control an
/// assigned entity.
/// </summary>
struct PlayerComponent {
    PlayerComponent() = default;
    PlayerComponent(const PlayerComponent&) = default;

    float WalkSpeed = 5.0f;
    float RunSpeed = 20.0f;
};

/// <summary>
/// The projection mode used on a camera component.
/// </summary>
enum ProjectionMode {
    IsometricProjection = 0,
    PerspectiveProjectionDXReverse,  // maps to  1..0
};

/// <summary>
/// This component is used as a ingame camera. Please note, that the default
/// rendering behaviour requires exactly one camera which has the flag
/// "IsMainCamera" set to true. This camera is then used to retrieve view and
/// projection matrices from.
/// </summary>
struct CameraComponent {
    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;

    /// <summary>
    /// Sets the projection mode of this camera.
    /// </summary>
    /// <param name="_projection">The projection mode you want to set.</param>
    void setProjectionMode(ProjectionMode _projection) {
        mProjectionMode = _projection;
    }

    /// <summary>
    /// Returns the current projection mode.
    /// </summary>
    /// <returns>The current projection mode of this camera.</returns>
    ProjectionMode getProjectionMode() const { return mProjectionMode; }

    /// <summary>
    /// Defines, whether we use this camera as rendering camera for the user.
    /// If there are multiple entities with a camera component which have this
    /// flag set to true, the renderer will randomly decide, which camera to
    /// use.
    /// </summary>
    bool IsMainCamera = true;

    /// <summary>
    /// Sets the horizontal field of view for this camera.
    /// Note that the vertical field of view will be changed!
    /// </summary>
    /// <param name="_fovh">The horizontal field of view in degrees.</param>
    void setHorizontalFieldOfView(float _fovh);

    /// <summary>
    /// Returns the current horizontal field of view.
    /// </summary>
    /// <returns>Current horizontal field of view</returns>
    float getHorizontalFieldOfView() const { return mHorizontalFieldOfView; }

    /// <summary>
    /// Sets the vertical field of view for this camera.
    /// Note that the horizontal field of view will be changed!
    /// </summary>
    /// <param name="_fovv">The vertical field of view in degrees.</param>
    void setVerticalFieldOfView(float _fovv);

    /// <summary>
    /// Returns the current vertical field of view.
    /// </summary>
    /// <returns>Current vertical field of view</returns>
    float getVerticalFieldOfView() const;

    /// <summary>
    /// Set the aspect ratio of the camera. The horizontal FoV stays the same,
    /// the vertical FoV gets updated.
    /// </summary>
    /// <param name="_aspectRatio">New aspect ratio (width/height)</param>
    void setAspectRatio(float _aspectRatio) { mAspectRatio = _aspectRatio; }

    /// <summary>
    /// Returns the current aspect ratio (width/height) for this camera.
    /// </summary>
    /// <returns>Current aspect ratio (width/height)</returns>
    float getAspectRatio() const { return mAspectRatio; }

    /// <summary>
    /// Set the near clipping plane of the camera.
    /// The plane is defined only by a distance from the camera.
    /// </summary>
    /// <param name="_plane">New near clipping plane of the camera</param>
    void setNearClippingPlane(float _plane);

    /// <summary>
    /// Returns the current near clipping plane.
    /// </summary>
    /// <returns>Current near clipping plane</returns>
    float getNearClippingPlane() const { return mNearClippingPlane; }

    /// <summary>
    /// Set the far clipping plane of the camera.
    /// The plane is defined only by a distance from the camera.
    /// This distance might be inf!
    /// </summary>
    /// <param name="_plane">New far clipping plane of the camera.</param>
    void setFarClippingPlane(float _plane);

    /// <summary>
    /// Gets the far clip distance
    /// </summary>
    /// <returns>Far clip distance</returns>
    float getFarClippingPlane() const { return mFarClippingPlane; }

    /// <summary>
    /// Gets size of the viewport
    /// </summary>
    /// <returns>Size of viewport</returns>
    glm::uvec2 getViewportSize() const { return mViewportSize; }

    /// <summary>
    /// Gets width of the viewport
    /// </summary>
    /// <returns>Width of the viewport</returns>
    unsigned int getViewportWidth() const { return mViewportSize.x; }

    /// <summary>
    /// Gets height of the viewport
    /// </summary>
    /// <returns>Height of the viewport</returns>
    unsigned int getViewportHeight() const { return mViewportSize.y; }

    /// <summary>
    /// Sets new viewport size and calculates new aspect ratio
    /// </summary>
    /// <param name="_newWidth">New width of viewport</param>
    /// <param name="_newHeight">New height of viewport</param>
    void resize(int _newWidth, int _newHeight) {
        mViewportSize = glm::uvec2(_newWidth, _newHeight);
        setAspectRatio(_newWidth / (float)_newHeight);
    }

    /// <summary>
    /// Returns the projection matrix for this camera.
    /// </summary>
    /// <returns>Projection Matrix</returns>
    glm::mat4 getProjectionMatrix() const;

    /// <summary>
    /// The entity Id of the gameObject this camera should follow ingame.
    ///
    /// If not set, this camera will look and rotate around (0,0,0).
    /// </summary>
    entt::entity TargetEntityId{entt::null};

    /// <summary>
    /// Used by the ThirdPersonCameraControllerSystem to offset the camera
    /// from its target.
    /// </summary>
    glm::vec3 TargetOffset = glm::vec3(0.0f, .5f, 2.0f);

private:
    ProjectionMode mProjectionMode = PerspectiveProjectionDXReverse;
    float mHorizontalFieldOfView = 75.0f;
    float mAspectRatio = 4.f / 3.f;

    float mNearClippingPlane = .1f;                                    // 10cm
    float mFarClippingPlane = std::numeric_limits<float>::infinity();  // 5000m

    float mLookAtDistance = 500.0;
    glm::uvec2 mViewportSize;
};
}  // namespace ComponentSystem
}  // namespace DCore
#include "BaseComponents.hh"

#include <Utils/Base.hh>

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

void DCore::ComponentSystem::CameraComponent::setHorizontalFieldOfView(
    float _fovh) {
    DR_ASSERT(_fovh < 180.0f);
    DR_ASSERT(_fovh > 0.0f);
    mHorizontalFieldOfView = _fovh;
}

void DCore::ComponentSystem::CameraComponent::setVerticalFieldOfView(
    float _fovv) {
    DR_ASSERT(_fovv < 180.0f);
    DR_ASSERT(_fovv > 0.0f);

    // we only save the aspectRatio and the horizontal FoV
    // so if we change the vertical FoV, we change the aspectRatio

    // mAspectRatio = tan( glm::radians(0.5f * mHorizontalFieldOfView) ) /
    // tan( glm::radians(0.5f * _fovv) );

    float x = tan(glm::radians(0.5f * _fovv)) * mAspectRatio;
    mHorizontalFieldOfView = glm::degrees(2.0f * atan(x));
}

float DCore::ComponentSystem::CameraComponent::getVerticalFieldOfView() const {
    return glm::degrees(
        atan(tan(glm::radians(0.5f * mHorizontalFieldOfView)) / mAspectRatio) *
        2.0f);
}

void DCore::ComponentSystem::CameraComponent::setNearClippingPlane(
    float _plane) {
    DR_ASSERT(_plane > 0.0f);
    mNearClippingPlane = _plane;
}

void DCore::ComponentSystem::CameraComponent::setFarClippingPlane(
    float _plane) {
    DR_ASSERT(_plane > 0.0f);
    mFarClippingPlane = _plane;
}

glm::mat4 DCore::ComponentSystem::CameraComponent::getProjectionMatrix() const {
    glm::mat4 projectionMatrix{};  // identity matrix

    if (getProjectionMode() == IsometricProjection) {
        // we don't set the left/right/top/bottom values explicitly, so we want
        // that
        // all object at our focal distance appear the same in perspective and
        // isometric view
        float right = tan(glm::radians(getHorizontalFieldOfView() * 0.5f)) *
                      mLookAtDistance;
        float left = -right;
        float top = tan(glm::radians(getVerticalFieldOfView() * 0.5f)) *
                    mLookAtDistance;
        float bottom = -top;

        // we do the same here as a glOrtho call would do, but with flipped y
        projectionMatrix[0][0] = 2.0f / (right - left);
        projectionMatrix[1][1] = -2.0f / (top - bottom);
        projectionMatrix[2][2] =
            -2.0f / (mFarClippingPlane - mNearClippingPlane);
        projectionMatrix[0][3] = -(right + left) / (right - left);
        projectionMatrix[1][3] = -(top + bottom) / (top - bottom);
        projectionMatrix[2][3] = -(mFarClippingPlane + mNearClippingPlane) /
                                 (mFarClippingPlane - mNearClippingPlane);
        projectionMatrix[3][3] = 1.0;
    } else if (mProjectionMode == PerspectiveProjectionDXReverse) {
        if (std::isinf(mFarClippingPlane)) {
            float e = 1.0f / tan(glm::radians(getVerticalFieldOfView() * 0.5f));
            const float a = getAspectRatio();

            // infinite Perspective matrix reversed mapping to 1..0, but flip y
            projectionMatrix = {e / a, 0.0f, 0.0f,
                                0.0f,  //
                                0.0f,  -e,   0.0f,
                                0.0f,  //
                                0.0f,  0.0f, 0.0f,
                                -1.0f,  //
                                0.0f,  0.0f, mNearClippingPlane,
                                0.0f};
        } else {
            // TODO: convert this into a matrix with finite far distance but
            // from 0 to 1 instead of 1 to 0
            float e = 1.0f / tan(glm::radians(getVerticalFieldOfView() * 0.5f));
            const float a = getAspectRatio();

            // infinite Perspective matrix reversed mapping to 1..0, but flip y
            projectionMatrix = {e / a, 0.0f, 0.0f, 0.0f,   //
                                0.0f,  -e,   0.0f, 0.0f,   //
                                0.0f,  0.0f, 0.0f, -1.0f,  //
                                0.0f,  0.0f, 0.0f, 0.0f};

            projectionMatrix[2][2] =
                mFarClippingPlane / (mNearClippingPlane - mFarClippingPlane);
            projectionMatrix[3][2] = (mFarClippingPlane * mNearClippingPlane) /
                                     (mNearClippingPlane - mFarClippingPlane);
        }
    }

    else
        assert(0 && "unsupported projection mode");

    return projectionMatrix;
}
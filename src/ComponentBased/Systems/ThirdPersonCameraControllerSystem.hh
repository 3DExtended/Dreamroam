#pragma once
#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>
#include <ComponentBased/Systems/Base/SystemBase.hh>
#include <entt/entt.hpp>

namespace DCore {
namespace ComponentSystem {
class ThirdPersonCameraControllerSystem
    : public SystemBase<CameraComponent, TransformComponent> {
public:
    ThirdPersonCameraControllerSystem() = default;
    void LateUpdate(

        entt::basic_view<entt::entity, entt::exclude_t<>, CameraComponent,
                         TransformComponent>
            entities,
        double dt) override {
        for (auto entity : entities) {
            auto& [cameraComp, cameraTransform] =
                entities.get<CameraComponent, TransformComponent>(entity);

            // First load target transform details.
            auto targetEntity =
                this->GetEntityFromId(cameraComp.TargetEntityId);
            auto& targetTransform =
                targetEntity.GetComponent<TransformComponent>();

            glm::vec3 offset = cameraComp.TargetOffset;

            auto rotateTargetEntity =
                glm::rotate(targetTransform.rotation.y, glm::vec3(0, 1, 0));

            auto rotationMatrix = rotateTargetEntity;

            auto rotatedForwardVector =
                rotationMatrix * glm::vec4(offset.x, offset.y, offset.z, 0);

            cameraTransform.position =
                targetTransform.position +
                5.0f * glm::vec3(rotatedForwardVector.x, rotatedForwardVector.y,
                                 rotatedForwardVector.z);

            auto rotMatrix =
                glm::lookAt(cameraTransform.position, targetTransform.position,
                            glm::vec3(0, 1, 0));

            cameraTransform.rotation.y = -targetTransform.rotation.y;
            cameraTransform.rotation.x = asin(
                offset.y / sqrt(offset.z * offset.z + offset.y * offset.y));
        }
    }

    glm::vec2 lastScrollValue = glm::vec2(0);

    void Update(

        entt::basic_view<entt::entity, entt::exclude_t<>, CameraComponent,
                         TransformComponent>
            entities,
        double dt) override {
        for (auto entity : entities) {
            auto& [cameraComp, cameraTransform] =
                entities.get<CameraComponent, TransformComponent>(entity);

            auto scrolling = this->GetInput()->GetScrollWheel();

            auto deltaScrolling = scrolling - lastScrollValue;

            lastScrollValue = scrolling;

            cameraComp.TargetOffset = (glm::length(cameraComp.TargetOffset) +
                                       deltaScrolling.y / 25.0f) *
                                      glm::normalize(cameraComp.TargetOffset);
        }
    }

protected:
};
}  // namespace ComponentSystem
}  // namespace DCore
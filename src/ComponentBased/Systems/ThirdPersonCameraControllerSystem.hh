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
            auto [cameraComp, cameraTransform] =
                entities.get<CameraComponent, TransformComponent>(entity);

            // First load target transform details.
            auto targetEntity =
                this->GetEntityFromId(cameraComp.TargetEntityId);
            auto& targetTransform =
                targetEntity.GetComponent<TransformComponent>();

            cameraTransform.position =
                targetTransform.position + glm::vec3(2, 2, 0);

            auto rotMatrix =
                glm::lookAt(cameraTransform.position, targetTransform.position,
                            glm::vec3(0, 1, 0));

            auto eulerRotations = RotationMatrixToEulerAngles(rotMatrix);

            cameraTransform.rotation = eulerRotations;
        }
    }

    glm::vec3 RotationMatrixToEulerAngles(glm::mat4& R) {
        float sy = sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);

        bool singular = sy < 1e-6;  // If

        float x, y, z;
        if (!singular) {
            x = atan2(R[2][1], R[2][2]);
            y = atan2(-R[2][0], sy);
            z = atan2(R[1][0], R[0][0]);
        } else {
            x = atan2(-R[1][2], R[1][1]);
            y = atan2(-R[2][0], sy);
            z = 0;
        }
        return glm::vec3(x, y, z);
    }

protected:
};
}  // namespace ComponentSystem
}  // namespace DCore

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

            glm::vec3 offset(0, 0.5, 2);

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
            /*auto rotMatrix =
                glm::lookAt(cameraTransform.position, targetTransform.position,
                            glm::vec3(0, 1, 0));*/

            auto eulerRotations = RotationMatrixToEulerAngles(rotMatrix);
            //  cameraTransform.rotation = eulerRotations;
            cameraTransform.rotation.y = -targetTransform.rotation.y;
        }
    }

    glm::vec3 RotationMatrixToEulerAngles(glm::mat4& R) {
        float sy = sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);

        bool singular = sy < 1e-6;

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
        return glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
    }

protected:
};
}  // namespace ComponentSystem
}  // namespace DCore
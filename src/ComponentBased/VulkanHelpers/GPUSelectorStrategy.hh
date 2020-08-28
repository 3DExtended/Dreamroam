#pragma once
#include <lava/gpuselection/ISelectionStrategy.hh>

namespace DCore {
namespace ComponentSystem {
class GPUSelectorStrategy : public lava::ISelectionStrategy {
public:
    ~GPUSelectorStrategy() override {}
    GPUSelectorStrategy() {}

    vk::PhysicalDevice selectFrom(
        std::vector<vk::PhysicalDevice> const &phys) const override;

protected:
    vk::PhysicalDeviceType mPrimary = vk::PhysicalDeviceType::eDiscreteGpu;
    vk::PhysicalDeviceType mSecondary = vk::PhysicalDeviceType::eIntegratedGpu;
    vk::PhysicalDeviceType mTrinary = vk::PhysicalDeviceType::eCpu;
};

}  // namespace ComponentSystem
}  // namespace DCore

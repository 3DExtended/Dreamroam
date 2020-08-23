#include "GPUSelectorStrategy.hh"

namespace DCore {
namespace ComponentSystem {

vk::PhysicalDevice GPUSelectorStrategy::selectFrom(
    const std::vector<vk::PhysicalDevice> &phys) const {
    int secondaryDevId = -1;
    int trinaryDevId = -1;

    for (size_t i = 0; i < phys.size(); i++) {
        auto dev = phys[i];
        auto props = dev.getProperties();
        if (props.deviceType == mPrimary) {
            return dev;
        }

        if (props.deviceType == mSecondary) {
            secondaryDevId = i;
        }

        if (props.deviceType == mTrinary) {
            trinaryDevId = i;
        }
    }

    if (secondaryDevId != -1) return phys[secondaryDevId];
    if (trinaryDevId != -1) return phys[trinaryDevId];
    return {};
}

}  // namespace ComponentSystem
}  // namespace DCore

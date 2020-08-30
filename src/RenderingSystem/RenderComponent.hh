#pragma once
#include "MeshHandlers/Geometry.hh"
#include "TextureHandlers/Texture.hh"

using namespace DCore::Meshes;
using namespace DCore::Textures;
namespace DCore {
namespace Rendering {
struct RenderComponent {
    RenderComponent() = default;
    RenderComponent(bool isTransparent, float alpha, bool hasTexture,
                    std::shared_ptr<Texture> textureObj, bool active,
                    bool isThrowingShadow)
        : isTransparent(isTransparent),
          alpha(alpha),
          hasTexture(hasTexture),
          textureObj(textureObj),
          active(active),
          isThrowingShadow(isThrowingShadow){};
    RenderComponent(const RenderComponent&) = default;

    std::shared_ptr<Geometry> geometryObj = nullptr;

    bool isTransparent = false;
    float alpha = 1.0f;

    bool hasTexture = false;
    std::shared_ptr<Texture> textureObj = nullptr;

    bool active = true;

    bool isThrowingShadow = true;
};
}  // namespace Rendering
}  // namespace DCore

#pragma once
#include "MeshHandlers/Geometry.hh"
#include "TextureHandlers/Texture.hh"

using namespace DCore::Meshes;
using namespace DCore::Textures;
namespace DCore {
	namespace Rendering {
		struct RenderComponent
		{
			RenderComponent() = default;
			std::shared_ptr<Geometry> geometryObj = nullptr;

			bool isTransparent = false;
			float alpha = 1.0f;

			bool hasTexture = false;
			std::shared_ptr<Texture> textureObj = nullptr;

			bool active = true;

			bool isThrowingShadow = true;
		};
	}
}
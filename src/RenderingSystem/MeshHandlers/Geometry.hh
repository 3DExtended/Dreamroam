#pragma once

#include <lava-extras/geometry/Geometry.hh>
namespace DCore {
namespace Meshes {
/// <summary>
/// TODO replace this by a mesh component we can attatch to an entity...
/// </summary>
class Geometry {
public:
    Geometry(const lava::geometry::SharedGeometry geometry);
    Geometry(const Geometry&) = default;
    void draw(lava::InlineSubpass& pass);

private:
    lava::geometry::SharedGeometry mGeometry;
};
}  // namespace Meshes
}  // namespace DCore

#include "Geometry.hh"

using namespace DCore::Meshes;

Geometry::Geometry(const lava::geometry::SharedGeometry geometry)
    : mGeometry(geometry)
{
}

void Geometry::draw(lava::InlineSubpass &pass)
{
    mGeometry->draw(pass);
}

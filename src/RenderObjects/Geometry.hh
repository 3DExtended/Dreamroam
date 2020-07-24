#pragma once

#include <lava-extras/geometry/Geometry.hh>

class Geometry
{

  public:
    Geometry(const lava::geometry::SharedGeometry geometry);
    void draw(lava::InlineSubpass &pass);

  private:
    lava::geometry::SharedGeometry mGeometry;
};

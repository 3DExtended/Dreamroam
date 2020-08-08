#pragma once

#include <lava-extras/geometry/Geometry.hh>
namespace DCore {
    namespace Meshes {
        class Geometry
        {

        public:
            Geometry(const lava::geometry::SharedGeometry geometry);
            void draw(lava::InlineSubpass& pass);

        private:
            lava::geometry::SharedGeometry mGeometry;
        };
    }
}
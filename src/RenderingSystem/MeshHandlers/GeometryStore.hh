#pragma once
#include <lava-extras/geometry/Geometry.hh>
#include <lava-extras/geometry/IO.hh>
#include <lava/objects/Device.hh>
#include <map>
#include <string>

#include "GeometryLoader.hh"

namespace DCore {
namespace Meshes {
class Geometry;

class GeometryStore {
public:
    GeometryStore(lava::SharedDevice device);

    void registerGeometry(std::shared_ptr<Geometry> obj, std::string name);

    void registerGeometryFromData(lava::geometry::SharedGeometryData geomData,
                                  std::string name);

    void registerGeometryFromFileSingle(std::string filePath, std::string name);

    void registerGeometryFromFileMulti(std::string filePath,
                                       std::string namePrefix);

    inline std::shared_ptr<Geometry> getGeometryWithName(
        std::string name) const;
    // ^Geometrys define the geometry of an entity.
    //  They should be stored inside the entities RenderComponent.

    inline size_t getLayerCountWithName(std::string name) const;
    // ^Returns the number of layers on the corresponding geometry .
    //  It defaults to 1 layer per object.

private:
    lava::SharedDevice mDevice;
    GeometryLoader mGeometryImporter;
    std::map<std::string, std::shared_ptr<Geometry>> mGeometrys;
    std::map<std::string, size_t> mNumberOfLayersPer;
};

inline std::shared_ptr<Geometry> GeometryStore::getGeometryWithName(
    std::string name) const {
    return mGeometrys.at(name);
}

inline size_t GeometryStore::getLayerCountWithName(std::string name) const {
    auto it = mNumberOfLayersPer.find(name);
    if (it == mNumberOfLayersPer.end()) return 1;
    return it->second;
}
}  // namespace Meshes
}  // namespace DCore
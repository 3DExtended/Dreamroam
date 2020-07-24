#include "GeometryStore.hh"
#include <GlobalSettings.hh>
#include <Geometry/GeometryLoader.hh>
#include "Geometry.hh"
#include <RenderingSystem/PushConstants.hh>

#include <sstream>
#include <string>
#include <iostream>

#include <lava-extras/geometry/Geometry.hh>
#include <lava-extras/geometry/Cube.hh>
#include <lava-extras/geometry/Plane.hh>

GeometryStore::GeometryStore(
    lava::SharedDevice device)
    : mDevice(device)
{

    // Create all render objects.
    // Each render object can be used by multiple render components,
    // but only for rendering on the same device.
    {
        auto geometryData = lava::geometry::Cube<VertexAttributes>();
        std::shared_ptr<Geometry> sharedGeometryObj = std::make_shared<Geometry>(
            geometryData
                .uploadTo(mDevice));
        mGeometrys["cube"] = sharedGeometryObj;
    }
}

void GeometryStore::registerGeometry(
    std::shared_ptr<Geometry> obj,
    std::string name)
{
    mGeometrys[name] = obj;
}

void GeometryStore::registerGeometryFromData(
    lava::geometry::SharedGeometryData geomData,
    std::string name)
{
    std::shared_ptr<Geometry> sharedGeometryObj =
        std::make_shared<Geometry>(
            geomData->uploadTo(mDevice));
    mGeometrys[name] = sharedGeometryObj;
}

void GeometryStore::registerGeometryFromFileSingle(
    std::string filePath,
    std::string name)
{
    auto geometryData = mGeometryImporter.loadCombined<>(filePath);
    std::shared_ptr<Geometry> sharedGeometryObj =
        std::make_shared<Geometry>(
            geometryData->uploadTo(mDevice));
    mGeometrys[name] = sharedGeometryObj;
}

void GeometryStore::registerGeometryFromFileMulti(
    std::string filePath,
    std::string namePrefix)
{

    std::vector<unsigned int> materialIndices;
    std::vector<std::string> meshNames;
    auto geometryDataParts =
        mGeometryImporter.loadMulti<VertexAttributes>(
            filePath,
            materialIndices,
            meshNames);

    for (unsigned int i = 0; i < geometryDataParts.size(); ++i)
    {
        std::shared_ptr<Geometry> sharedGeometryObj = std::make_shared<Geometry>(
            geometryDataParts.at(i)
                ->uploadTo(mDevice));

        if (meshNames[i] == "")
        {
            // @todo Use assimp version which does read the names.
            std::cout << "GeometryStore: registerGeometryFromFileMulti(...) - mesh name could not be read."
                      << std::endl
                      << "Falling back to default name."
                      << std::endl;
            std::stringstream ss;
            ss << i;
            meshNames[i] = ss.str();
        }

        std::stringstream ss;
        ss << namePrefix << meshNames[i];
        std::string s = ss.str();

        std::cout << "adding geometry : " << s << std::endl;
        mGeometrys[s] = sharedGeometryObj;
    }
    mNumberOfLayersPer[namePrefix] = geometryDataParts.size();
}

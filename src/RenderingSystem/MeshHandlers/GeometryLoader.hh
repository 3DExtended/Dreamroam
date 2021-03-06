#pragma once

#include <RenderingSystem/PushConstants.hh>
#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <lava-extras/geometry/Geometry.hh>
#include <lava-extras/geometry/IO.hh>
#include <lava-extras/geometry/fwd.hh>
#include <lava/common/property.hh>
#include <vector>

// Based on lava-extras/geometry/IO.
// TODO: This class might need some cleanup.

struct aiScene;
struct aiNode;
using namespace DCore::Rendering;

namespace DCore {
namespace Meshes {
class GeometryLoader {
private:
    /// vec3 aTangent is available
    bool mCalculateTangents = true;

    /// No quads.
    bool mTriangulate = true;

    /// vec3 aNormal is available
    /// (normals in the dataset have priority)
    bool mGenerateSmoothNormal = true;

    /// per face, non-smooth normals
    bool mGenerateFaceNormal = false;

    /// Collapses scene structures
    bool mPreTransformVertices = true;

    /// vec2 aTexCoord is available (hopefully)
    bool mGenerateUvCoords = true;

    bool mFlipUvCoords = true;

public:
    GeometryLoader();

    using VertexCB =
        std::function<void(glm::vec3 /* position */, glm::vec3 /* normal */,
                           glm::vec3 /* tangent */, glm::vec3 /* texcoord */,
                           glm::vec4 /* color */)>;

    /// Loads all meshes inside the given file separated and stores the vertex
    /// data and indices inside the given vectors. 'verticesPerMesh' and
    /// 'indicesPerMesh' will first be cleared, then filled with the data read
    /// from the file.
    void loadRawMulti(
        const std::string& filename,
        std::vector<std::vector<VertexAttributes>>& verticesPerMesh,
        std::vector<std::vector<uint32_t>>& indicesPerMesh,
        std::vector<unsigned int>& meshMaterialIndices,
        std::vector<std::string>& meshNames);

    void loadRawCombined(const std::string& filename,
                         std::vector<VertexAttributes>& vertices,
                         std::vector<uint32_t>& indices);

    std::vector<std::shared_ptr<lava::geometry::GeometryData>> meshesFromFile(
        const std::string& filename,
        std::vector<unsigned int>& meshMaterialIndices,
        std::vector<std::string>& meshNames);

    std::shared_ptr<lava::geometry::GeometryData> singleMeshFromFile(
        const std::string& filename);

    template <class VertexT = lava::geometry::DefaultVertex>
    std::vector<std::shared_ptr<lava::geometry::GeometryData>> loadMulti(
        const std::string& filename,
        std::vector<unsigned int>& meshMaterialIndices,
        std::vector<std::string>& meshNames) {
        return meshesFromFile(filename, meshMaterialIndices, meshNames);
    }

    template <class VertexT = lava::geometry::DefaultVertex>
    std::shared_ptr<lava::geometry::GeometryData> loadCombined(
        std::string const& filename) {
        return singleMeshFromFile(filename);
    }

    void printNodeInfo_recursive(const aiScene* scene,
                                 const aiNode* node) const;
    void printSceneInfo(const aiScene* scene) const;
};
}  // namespace Meshes
}  // namespace DCore
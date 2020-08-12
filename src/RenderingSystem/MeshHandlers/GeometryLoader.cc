#include "GeometryLoader.hh"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <Utils/Base.hh>
#include <assimp/Importer.hpp>
#include <fstream>
#include <glm/vec4.hpp>
#include <iomanip>
#include <lava/common/log.hh>

using namespace DCore::Meshes;
using namespace DCore::Rendering;

static glm::vec3 aiCast(aiVector3D const& v) { return {v.x, v.y, v.z}; }
static glm::vec4 aiCast(aiColor4D const& v) { return {v.r, v.g, v.b, v.a}; }

GeometryLoader::GeometryLoader() {}

void GeometryLoader::loadRawMulti(
    const std::string& filename,
    std::vector<std::vector<VertexAttributes>>& verticesPerMesh,
    std::vector<std::vector<uint32_t>>& indicesPerMesh,
    std::vector<unsigned int>& meshMaterialIndices,
    std::vector<std::string>& meshNames) {
    if (!std::ifstream(filename).good()) {
        std::cout << "Error loading `" << filename << "'.";
        std::cout << "  File not found/not readable";
        return;
    }

    verticesPerMesh.clear();
    indicesPerMesh.clear();

    uint32_t flags = aiProcess_SortByPType;

    if (mTriangulate) flags |= aiProcess_Triangulate;
    if (mCalculateTangents) flags |= aiProcess_CalcTangentSpace;
    if (mGenerateSmoothNormal) flags |= aiProcess_GenSmoothNormals;
    if (mGenerateFaceNormal) flags |= aiProcess_GenNormals;
    if (mGenerateUvCoords) flags |= aiProcess_GenUVCoords;
    if (mPreTransformVertices) flags |= aiProcess_PreTransformVertices;
    if (mFlipUvCoords) flags |= aiProcess_FlipUVs;

    Assimp::Importer importer;
    auto scene = importer.ReadFile(filename, flags);

    if (!scene) {
        std::cout << "Error loading `" << filename << "' with Assimp.";
        std::cout << "  " << importer.GetErrorString();
        return;
    }

    if (!scene->HasMeshes()) {
        std::cout << "File `" << filename << "' has no meshes.";
        return;
    }

    // printSceneInfo(scene);

    for (auto i = 0u; i < scene->mNumMeshes; ++i) {
        auto const& mesh = scene->mMeshes[i];

        meshMaterialIndices.push_back(mesh->mMaterialIndex);
        meshNames.push_back(mesh->mName.C_Str());

        std::vector<uint32_t> indicesCurrentMesh;

        // add faces
        auto fCnt = mesh->mNumFaces;
        for (auto f = 0u; f < fCnt; ++f) {
            auto const& face = mesh->mFaces[f];
            if (face.mNumIndices != 3) {
                std::cout << "File `" << filename << "':.";
                std::cout << "  non-3 faces not implemented/supported "
                          << face.mNumIndices;
                continue;
            }

            for (auto fi = 0u; fi < face.mNumIndices; ++fi) {
                indicesCurrentMesh.push_back(face.mIndices[fi]);
            }
        }

        indicesPerMesh.push_back(indicesCurrentMesh);

        std::vector<VertexAttributes> verticesCurrentMesh;

        // add vertices
        auto vCnt = mesh->mNumVertices;
        for (auto v = 0u; v < vCnt; ++v) {
            auto pos = aiCast(mesh->mVertices[v]);
            auto normal = mesh->HasNormals() ? aiCast(mesh->mNormals[v])
                                             : glm::vec3(0.0f);
            auto tangent = mesh->HasTangentsAndBitangents()
                               ? aiCast(mesh->mTangents[v])
                               : glm::vec3(0.0f);
            auto texCoord = mesh->HasTextureCoords(0)
                                ? aiCast(mesh->mTextureCoords[0][v])
                                : glm::vec2(0.f);
            auto colors = mesh->HasVertexColors(0) ? aiCast(mesh->mColors[0][v])
                                                   : glm::vec4(1.f);

            verticesCurrentMesh.push_back(
                {pos, normal, tangent, texCoord, colors});
            // cb(pos, normal, tangent, texCoord, colors);
        }

        verticesPerMesh.push_back(verticesCurrentMesh);
    }
}

void GeometryLoader::printNodeInfo_recursive(const aiScene* scene,
                                             const aiNode* node) const {
    std::cout << "- Node info: -" << std::endl;
    std::cout << "Node name: " << node->mName.C_Str() << std::endl;

    for (auto j = 0u; j < node->mNumMeshes; ++j) {
        auto mesh = scene->mMeshes[node->mMeshes[j]];
        std::cout << "Node mesh (name/material index): " << mesh->mName.C_Str()
                  << " / " << mesh->mMaterialIndex << std::endl;
    }

    if (node->mNumChildren > 0) {
        std::cout << "Child nodes:" << std::endl;

        for (auto i = 0u; i < node->mNumChildren; ++i) {
            auto childNode = node->mChildren[i];
            printNodeInfo_recursive(scene, childNode);
        }
    } else {
        std::cout << "Node is leaf." << std::endl;
    }

    std::cout << "- Node info end -" << std::endl << std::endl;
}

void GeometryLoader::printSceneInfo(const aiScene* scene) const {
    std::cout << "---- ----------- ----" << std::endl;
    std::cout << "---- Scene info: ----" << std::endl << std::endl;
    printNodeInfo_recursive(scene, scene->mRootNode);
    std::cout << "--- Scene info end ---" << std::endl;
    std::cout << "--- -------------- ---" << std::endl << std::endl;
}

void GeometryLoader::loadRawCombined(
    const std::string& filename, std::vector<VertexAttributes>& verticesResult,
    std::vector<uint32_t>& indicesResult) {
    std::vector<std::vector<VertexAttributes>> verticesPerMesh;
    std::vector<std::vector<uint32_t>> indicesPerMesh;
    std::vector<unsigned int> materialIndexPerMesh;  // not used afterwards
    std::vector<std::string> namePerMesh;            // not used afterwards

    loadRawMulti(filename, verticesPerMesh, indicesPerMesh,
                 materialIndexPerMesh, namePerMesh);

    DR_ASSERT(verticesPerMesh.size() == indicesPerMesh.size());
    DR_ASSERT(verticesPerMesh.size() == materialIndexPerMesh.size());
    DR_ASSERT(verticesPerMesh.size() == namePerMesh.size());

    // Clear and resize the result vectors:
    size_t finalNumberVertices = 0;
    size_t finalNumberIndices = 0;
    for (size_t i = 0; i < verticesPerMesh.size(); ++i) {
        finalNumberVertices += verticesPerMesh[i].size();
        finalNumberIndices += indicesPerMesh[i].size();
    }
    verticesResult.clear();
    indicesResult.clear();
    verticesResult.reserve(finalNumberVertices);
    indicesResult.reserve(finalNumberIndices);

    size_t indexOffset = 0;
    for (size_t i = 0; i < verticesPerMesh.size(); ++i) {
        auto verticesCurrentMesh = verticesPerMesh[i];
        auto indicesCurrentMesh = indicesPerMesh[i];

        auto itVertices = verticesCurrentMesh.begin();
        auto itIndices = indicesCurrentMesh.begin();

        for (size_t j = 0; j < verticesCurrentMesh.size(); ++j) {
            verticesResult.push_back(*itVertices);
            indicesResult.push_back((uint32_t)((*itIndices) + indexOffset));
            ++itVertices;
            ++itIndices;
        }

        indexOffset += verticesPerMesh[i].size();
    }
}

std::vector<std::shared_ptr<lava::geometry::GeometryData>>
GeometryLoader::meshesFromFile(const std::string& filename,
                               std::vector<unsigned int>& meshMaterialIndices,
                               std::vector<std::string>& meshNames) {
    std::vector<std::vector<VertexAttributes>> verticesPerMesh;
    std::vector<std::vector<uint32_t>> indicesPerMesh;

    meshMaterialIndices.clear();
    meshNames.clear();

    loadRawMulti(filename, verticesPerMesh, indicesPerMesh, meshMaterialIndices,
                 meshNames);

    DR_ASSERT(verticesPerMesh.size() == indicesPerMesh.size());
    DR_ASSERT(verticesPerMesh.size() == meshMaterialIndices.size());
    DR_ASSERT(verticesPerMesh.size() == meshNames.size());

    std::vector<std::shared_ptr<lava::geometry::GeometryData>>
        geometryDataPointers;

    for (auto i = 0u; i < verticesPerMesh.size(); ++i) {
        auto currentGeomDataPtr =
            std::make_shared<lava::geometry::GeometryData>();
        geometryDataPointers.push_back(currentGeomDataPtr);

        VertexAttributes::putAttributes(currentGeomDataPtr->info());
        currentGeomDataPtr->setIndices(indicesPerMesh[i]);
        currentGeomDataPtr->setBindingData(0, verticesPerMesh[i]);
    }

    return geometryDataPointers;
}

std::shared_ptr<lava::geometry::GeometryData>
GeometryLoader::singleMeshFromFile(const std::string& filename) {
    std::vector<VertexAttributes> vertices;
    std::vector<uint32_t> indices;

    loadRawCombined(filename, vertices, indices);

    auto currentGeomDataPtr = std::make_shared<lava::geometry::GeometryData>();

    VertexAttributes::putAttributes(currentGeomDataPtr->info());
    currentGeomDataPtr->setIndices(indices);
    currentGeomDataPtr->setBindingData(0, vertices);

    return currentGeomDataPtr;
}
#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <vector>
#include <glm/glm.hpp>

#include "core/Singleton.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

class MeshLoader : public Singleton<MeshLoader>
{
public:
    MeshLoader() = default;
    ~MeshLoader() = default;

    Mesh* Load(const char* path);

private:
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Mesh> m_Meshes;
};

#endif // MESH_LOADER_H

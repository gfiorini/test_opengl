#include "model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

//void processMesh(aiMesh* mesh, const aiScene* scene) {
//    std::vector<float> vertices;
//    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//        // Extract vertex positions
//        vertices.push_back(mesh->mVertices[i].x);
//        vertices.push_back(mesh->mVertices[i].y);
//        vertices.push_back(mesh->mVertices[i].z);
//
//        // Extract normals
//        if (mesh->HasNormals()) {
//            vertices.push_back(mesh->mNormals[i].x);
//            vertices.push_back(mesh->mNormals[i].y);
//            vertices.push_back(mesh->mNormals[i].z);
//        }
//
//        // Extract texture coordinates
//        if (mesh->mTextureCoords[0]) {
//            vertices.push_back(mesh->mTextureCoords[0][i].x);
//            vertices.push_back(mesh->mTextureCoords[0][i].y);
//        } else {
//            vertices.push_back(0.0f);
//            vertices.push_back(0.0f);
//        }
//    }
//    std::cout << "Processed " << vertices.size() / 8 << " vertices.\n";
//}

types::Buffer processMesh(aiMesh* mesh){

    types::Vertex vertices[] = {
            {{-0, 0, 0}, {0, 0}, {0, 0, 1}},
            {{100, -0, 0}, {1, 0}, {1, 0, 0}},
            {{100, 100, 0}, {1, 1}, {1, 1, 1},},
            {{0, 100, 0}, {0, 1}, {0, 1, 1}},
    };

    unsigned int vertexIndices[]{
            0, 1, 2, // first triangle
            0, 2, 3 // second triangle
    };

    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    auto va = std::make_unique<VertexArray>() ;
    va->AddBuffer(vbo, vbl);

    auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 6) ;
    return types::Buffer (std::move(ibo), std::move(va));
}

aiMesh* extractMesh(aiNode* node, const aiScene* scene, const char *name) {
    // Process each mesh in the node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "Processing mesh: " << mesh->mName.C_Str() << "\n";
        if (strcmp(mesh->mName.C_Str(), name) == 0){
            return mesh;
        }
    }

    // Process each child node recursively
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        extractMesh(node->mChildren[i], scene, name);
    }
    return nullptr;
}

types::Buffer loadCubeFromFBX() {
    Assimp::Importer importer;
    const char *file = "res/models/cube.fbx";
    const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs |
                                                                    aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error: " << importer.GetErrorString() << "\n";
    }

    std::cout << "Successfully loaded FBX file: " << file << std::endl;

    // Process the root node
    aiMesh* mesh =  extractMesh(scene->mRootNode, scene, "Cube");
    if (mesh){
        types::Vertex vertices[] = {
                {{-0, 0, 0}, {0, 0}, {0, 0, 1}},
                {{100, -0, 0}, {1, 0}, {1, 0, 0}},
                {{100, 100, 0}, {1, 1}, {1, 1, 1},},
                {{0, 100, 0}, {0, 1}, {0, 1, 1}},
        };

        unsigned int vertexIndices[]{
                0, 1, 2, // first triangle
                0, 2, 3 // second triangle
        };

        VertexBuffer vbo(vertices, sizeof(vertices));
        VertexBufferLayout vbl;
        vbl.Push<float>(3);
        vbl.Push<float>(2);
        vbl.Push<float>(3);

        auto va = std::make_unique<VertexArray>() ;
        va->AddBuffer(vbo, vbl);

        auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 6) ;
        return types::Buffer (std::move(ibo), std::move(va));
    } else {
        return {};
    }
}

types::Buffer loadCubeTextureable() {


    types::Vertex vertices[] = {

            // face A
            {{-50, -50, 50}, {0, 0}, {0, 0, 1}}, // 0
            {{50, -50, 50}, {1, 0}, {1, 0, 0}}, // 1
            {{50, 50, 50}, {1, 1}, {1, 1, 1},}, // 2
            {{-50, 50, 50}, {0, 1}, {0, 1, 1}}, // 3

            // face B
            {{50, -50, 50}, {0, 0}, {1, 0, 0}}, // 4
            {{50, -50, -50}, {1, 0}, {1, 0, 0}}, // 5
            {{50, 50, -50}, {1, 1}, {0, 1, 1}}, // 6
            {{50, 50, 50}, {0, 1}, {1, 1, 1},}, // 7

            // face C
            {{-50, -50, 50}, {0, 0}, {0, 0, 1}}, // 8
            {{50, -50, 50}, {1, 0}, {1, 0, 0}}, // 9
            {{50, -50, -50}, {1, 1}, {1, 1, 1},}, // 10
            {{-50, -50, -50}, {0, 1}, {0, 1, 1}}, // 11

//
//            // face D
            {{-50, -50, -50}, {0, 0}, {0, 0, 1}}, // 12
            {{50, -50, -50}, {1, 0}, {1, 0, 0}}, // 13
            {{50, 50, -50}, {1, 1}, {1, 1, 1},}, // 14
            {{-50, 50, -50}, {0, 1}, {0, 1, 1}}, // 15

            // face E
            {{-50, -50, 50}, {0, 0}, {1, 0, 0}}, // 16
            {{-50, -50, -50}, {1, 0}, {1, 0, 0}}, // 17
            {{-50, 50, -50}, {1, 1}, {0, 1, 1}}, // 18
            {{-50, 50, 50}, {0, 1}, {1, 1, 1},}, // 19

            // face F
            {{-50, 50, 50}, {0, 0}, {0, 0, 1}}, // 20
            {{50, 50, 50}, {1, 0}, {1, 0, 0}}, // 21
            {{50, 50, -50}, {1, 1}, {1, 1, 1},}, // 22
            {{-50, 50, -50}, {0, 1}, {0, 1, 1}}, // 23
    };


    unsigned int vertexIndices[]{

            // Face A
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 10, 9,
            8, 11, 10,

            12, 15, 14,
            12, 14, 13,

            18, 16, 19,
            18, 17, 16,

            20, 21, 22,
            20, 22, 23

    };
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    auto va = std::make_unique<VertexArray>() ;
    va->AddBuffer(vbo, vbl);

    auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 36) ;
    return types::Buffer (std::move(ibo), std::move(va));
}
// objectTable.h
#pragma once
#include <glad/glad.h>
#include <cmath>
#include <vector>

struct MeshData
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint>  indices;
};

// triangle
inline const MeshData triangle = {
    {
        -0.9f, -0.9f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.1f, -0.9f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.9f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f
    },
    { 0, 1, 2 }
};

inline const MeshData square = {
    {
         -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,   0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f
    },
    { 0, 1, 2,  2, 3, 0 }
};

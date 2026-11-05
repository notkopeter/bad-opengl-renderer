// GLTools.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "settings.h"
#include "objectTable.h"

struct Mesh
{
    GLuint  VAO = 0;
    GLuint  VBO = 0;
    GLuint  EBO = 0;
    GLsizei indexCount = 0;
    glm::mat4 model = glm::mat4(1.0f);
};

inline std::vector<Mesh> objects;

inline void GLInit()
{
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSwapInterval(0);
}
inline GLuint createShader(const char* vertex_shader, const char* fragment_shader)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
inline Mesh createMesh(const MeshData& data)
{
    Mesh m;
    m.indexCount = (GLsizei)data.indices.size();

    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);
    glGenBuffers(1, &m.EBO);

    glBindVertexArray(m.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 data.vertices.size() * sizeof(GLfloat),
                 data.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indices.size() * sizeof(GLuint),
                 data.indices.data(), GL_STATIC_DRAW);

    const GLsizei STRIDE = 8 * sizeof(GLfloat);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE, (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);                      // VAO first,
    glBindBuffer(GL_ARRAY_BUFFER, 0);          // then the buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return m;
}
inline void drawMesh(const Mesh& m, GLint modelLoc)
{
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m.model));
    glBindVertexArray(m.VAO);
    glDrawElements(GL_TRIANGLES, m.indexCount, GL_UNSIGNED_INT, 0);
}
inline void drawMeshes(GLuint shaderProgram)
{
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    for (const Mesh& m : objects)
        drawMesh(m, modelLoc);
}
inline void destroyMesh(Mesh& m)
{
    glDeleteVertexArrays(1, &m.VAO);
    glDeleteBuffers(1, &m.VBO);
    glDeleteBuffers(1, &m.EBO);
    m = Mesh{};
}
inline void destroyMeshes()
{
    for (Mesh& m : objects)
        destroyMesh(m);
    objects.clear();
}
inline GLuint assignTextures(GLuint shaderProgram)
{
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("TEXTURES/grid.png", &widthImg, &heightImg, &numColCh, 4);
    if (!bytes)
    {
        std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
        return 0;
    }


    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);

    glEnable(GL_DEPTH_TEST);

    return texture;
}
inline void genMatrices(GLuint shaderProgram)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(00.0f, 0.0f, -2.5f));
    proj = glm::perspective(glm::radians(FOV), (WIDTH/HEIGHT), 0.05f, 100.0f);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
}
inline void translateMesh(Mesh& m, const glm::vec3& offset)
{
    m.model = glm::translate(m.model, offset);
}
inline void rotateMesh(Mesh& m, float degrees, const glm::vec3& axis)
{
    m.model = glm::rotate(m.model, glm::radians(degrees), axis);
}
inline void scaleMesh(Mesh& m, const glm::vec3& factors)
{
    m.model = glm::scale(m.model, factors);
}
inline void resetMesh(Mesh& m)
{
    m.model = glm::mat4(1.0f);
}
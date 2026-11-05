// main.cpp
#include "windowTools.h"
#include "GLTools.h"
#include "default-shaders.h"
#include "loop.h"

int main()
{   
    GLFWwindow* window = initWindow("OPENGL"); 
    GLInit();
    GLuint shaderProgram = createShader(default_vert, default_frag);
    objects.push_back(createMesh(square));
    GLuint texture = assignTextures(shaderProgram);
    genMatrices(shaderProgram);

    scaleMesh(objects[0], glm::vec3(0.5f));
    translateMesh(objects[1], glm::vec3(1.0f, 0.0f, 0.0f));

    while(!glfwWindowShouldClose(window))
        runLoop(window,shaderProgram , texture);

    destroyMeshes();
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    windowCleanup(window);
}
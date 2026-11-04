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
    //objects.push_back(createMesh(triangle));

    GLuint texture = assignTextures(shaderProgram);

    while(!glfwWindowShouldClose(window))
        runLoop(window, texture);

    destroyMeshes();
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    windowCleanup(window);
}
// main.cpp
#include "windowTools.h"
#include "GLTools.h"
#include "default-shaders.h"
#include "loop.h"
#include "camera.h"

int main()
{   
    GLFWwindow* window = initWindow("OPENGL"); 
    GLInit();
    GLuint shaderProgram = createShader(default_vert, default_frag);
    objects.push_back(createMesh(cube));
    GLuint texture = assignTextures(shaderProgram);

    scaleMesh(objects[0], glm::vec3(0.5f));

    while(!glfwWindowShouldClose(window))
        runLoop(window,shaderProgram , texture);

    destroyMeshes();
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    windowCleanup(window);
}
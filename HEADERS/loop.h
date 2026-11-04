// loop.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GLTools.h"

inline void runLoop(GLFWwindow* window, GLuint texture)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    drawMeshes();


    glfwSwapBuffers(window);
    glfwPollEvents();
}
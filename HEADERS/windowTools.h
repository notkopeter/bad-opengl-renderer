// windowTools.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "settings.h"

inline GLFWwindow* initWindow(const char* TITLE)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if(window == NULL) std::cout << " Failed to create window: 'windowInit.h' " << std::endl;

    glfwMakeContextCurrent(window);

    return window;
}

inline void windowCleanup(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
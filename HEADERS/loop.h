// loop.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GLTools.h"

float dt;
float lastTime = 0; 

inline void runLoop(GLFWwindow* window, GLuint shaderProgram, GLuint texture)
{
    dt = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateCamera(window, shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    rotateMesh(objects[0], 90.0f * dt, glm::vec3(0, 1, 0));

    drawMeshes(shaderProgram);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
// camera.h
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    glm::vec3 position{0.0f};
    glm::vec3 orientation{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    int width, height;
    float speed = 3.0f;
    float sensitivity = 0.1f;

    Camera(int width, int height, glm::vec3 position);

    void Matrix(float FOV, float nearPlane, float farPlane,
                GLuint shaderProgram, const char* uniform);
    void Inputs(GLFWwindow* window);

private:
    float yaw = -90.0f;
    float pitch = 0.0f;
    bool  looking = false;
    double lastTime = 0.0;
    double lastX = 0.0, lastY = 0.0;
};
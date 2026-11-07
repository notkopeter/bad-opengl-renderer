// camera.cpp
#include "camera.h"

// this is truly awful

Camera::Camera(int width, int height, glm::vec3 position)
    : position(position), width(width), height(height) {}

void Camera::Matrix(float FOV, float nearPlane, float farPlane, GLuint shaderProgram, const char* uniform)
{
    glm::mat4 view = glm::lookAt(position, position + orientation, up);
    glm::mat4 proj = glm::perspective(glm::radians(FOV), (float)width / (float)height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window)
{
    double now = glfwGetTime();
    float dt = (lastTime == 0.0) ? 0.0f : (float)(now - lastTime);
    lastTime = now;

    float v = speed * dt;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) v *= 3.0f;

    glm::vec3 right = glm::normalize(glm::cross(orientation, up));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += v * orientation;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= v * orientation;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += v * right;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= v * right;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        position += v * up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position -= v * up;

    // hold left mouse to look around
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!looking)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwGetCursorPos(window, &lastX, &lastY);
            looking = true;
        }

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);
        yaw   += (float)(mx - lastX) * sensitivity;
        pitch -= (float)(my - lastY) * sensitivity;
        lastX = mx;
        lastY = my;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        orientation = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
    }
    else if (looking)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        looking = false;
    }
}
// default-shaders.h
#pragma once

// vertex shader
inline constexpr const char* default_vert = 
R"GLSL(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    color = aColor;
    texCoord = aTexCoord;
}
)GLSL";

// fragment shader
inline constexpr const char* default_frag = R"GLSL(
#version 330 core
in vec3 color;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, texCoord) * vec4(color, 1.0);
}
)GLSL";
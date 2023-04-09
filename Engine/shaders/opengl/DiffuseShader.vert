#version 460 core

layout (location = 0) in vec3 IPos;
layout (location = 1) in vec3 INorm;
layout (location = 2) in vec2 ITexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(model * vec4(IPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * INorm;

    gl_Position = projection * view * model * vec4(IPos, 1.0);
}
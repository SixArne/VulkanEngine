#version 460 core

in vec3 IFragPos;
in vec3 INormal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 diffuseColor;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;

    vec3 result = diffuseColor * diffuse;

    FragColor = vec4(result, 1.0);
}

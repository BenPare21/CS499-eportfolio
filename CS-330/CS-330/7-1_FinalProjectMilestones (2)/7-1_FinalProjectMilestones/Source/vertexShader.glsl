#version 460 core
layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aNormal;   // Vertex normal
layout (location = 2) in vec2 aTexCoords; // Texture coordinates

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;   // Output texture coordinates for fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Transform vertex position into world coordinates
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Transform normal into world space
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass the texture coordinates
    TexCoords = aTexCoords;

    // Final vertex position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

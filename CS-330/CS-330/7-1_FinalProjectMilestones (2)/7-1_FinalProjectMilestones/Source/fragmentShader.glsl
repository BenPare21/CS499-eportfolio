#version 460 core
out vec4 FragColor;

in vec3 FragPos;    // Fragment position from vertex shader
in vec3 Normal;     // Fragment normal from vertex shader
in vec2 TexCoords;  // Texture coordinates from vertex shader

// Lighting uniforms
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

// Texture uniforms
uniform sampler2D objectTexture; // Texture sampler
uniform bool bUseTexture;        // Flag to indicate whether to use texture

void main()
{
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (Phong model)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine lighting components (ambient + diffuse + specular)
    vec3 lighting = ambient + diffuse + specular;

    // Texture or object color handling
    vec3 color;
    if (bUseTexture) {
        color = texture(objectTexture, TexCoords).rgb; // Use texture color
    } else {
        color = objectColor; // Use fallback object color if no texture is applied
    }

    // Final color with lighting
    vec3 finalColor = lighting * color;

    // Output final color
    FragColor = vec4(finalColor, 1.0);
}

// Texture.cpp

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& path) {
    loadTexture(path); // Load the texture from the provided path
}

void Texture::loadTexture(const std::string& path) {
    // Load the texture data using stb_image
    unsigned char* data = stbi_load(path.c_str(), &width, &height, nullptr, 0);
    if (data) {
        glGenTextures(1, &id); // Generate the texture ID
        glBindTexture(GL_TEXTURE_2D, id); // Bind the texture

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload the texture data to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps for the texture

        stbi_image_free(data); // Free the image memory after loading
    }
    else {
        // Handle error (texture loading failed)
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit); // Activate the specified texture unit
    glBindTexture(GL_TEXTURE_2D, id); // Bind the texture
}

GLuint Texture::getID() const {
    return id; // Return the texture ID
}

Texture::~Texture() {
    glDeleteTextures(1, &id); // Delete the texture when the object is destroyed
}

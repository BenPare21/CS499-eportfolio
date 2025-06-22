// Texture.h
#pragma once

#include <GL/glew.h> // Include GLEW for OpenGL function pointers
#include <string>

class Texture {
public:
    // Constructor to load texture from a file
    Texture(const std::string& path);

    // Method to bind the texture to a specified texture unit
    void bind(unsigned int unit = 0) const;

    // Method to get the texture ID
    GLuint getID() const;

    // Destructor to clean up the texture
    ~Texture();

private:
    GLuint id;         // Texture ID
    int width, height; // Texture dimensions

    // Helper function to load the texture from file
    void loadTexture(const std::string& path);
};

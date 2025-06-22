#pragma once
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>  // Add this line


class ShaderManager {
public:
    // Constructor and Destructor
    ShaderManager();
    ~ShaderManager();

    // Load and compile vertex and fragment shaders
    bool LoadShaders(const char* vertexShaderPath, const char* fragmentShaderPath);

    // Use the shader program
    void UseShaderProgram();

    // Get the shader program ID
    GLuint GetShaderProgram() const { return m_shaderProgram; }

    // Utility functions for setting uniforms in the shader
    void setMat4Value(const std::string& name, const glm::mat4& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setInt(const std::string& name, int value);

private:
    GLuint m_shaderProgram;

    // Helper functions for error checking
    bool CheckShaderCompileErrors(GLuint shader, const std::string& type);
    bool CheckProgramLinkErrors(GLuint program);
};

#endif // SHADER_MANAGER_H

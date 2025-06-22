#include "ShaderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

ShaderManager::ShaderManager() : m_shaderProgram(0) { }

ShaderManager::~ShaderManager() {
    if (m_shaderProgram != 0) {
        glDeleteProgram(m_shaderProgram);
    }
}

// Load, compile, and link vertex and fragment shaders
bool ShaderManager::LoadShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    // 1. Create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 2. Read the shader code from files
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile(vertexShaderPath), fragmentFile(fragmentShaderPath);

    if (vertexFile && fragmentFile) {
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    else {
        std::cerr << "Failed to open shader files: " << vertexShaderPath << " or " << fragmentShaderPath << std::endl;
        return false;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 3. Compile vertex shader
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    if (!CheckShaderCompileErrors(vertexShader, "VERTEX")) return false;

    // 4. Compile fragment shader
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    if (!CheckShaderCompileErrors(fragmentShader, "FRAGMENT")) return false;

    // 5. Link shaders into a program (this part is already present in your code)
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    if (!CheckProgramLinkErrors(m_shaderProgram)) return false;

    // 6. Delete the shader objects now that they're linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}


// Use the shader program
void ShaderManager::UseShaderProgram() {
    glUseProgram(m_shaderProgram);
}

// Set uniforms in the shader
void ShaderManager::setMat4Value(const std::string& name, const glm::mat4& value) {
    GLuint location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderManager::setVec3(const std::string& name, const glm::vec3& value) {
    GLuint location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderManager::setInt(const std::string& name, int value) {
    GLuint location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform1i(location, value);
}

bool ShaderManager::CheckShaderCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return false;
    }
    return true;
}

bool ShaderManager::CheckProgramLinkErrors(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return false;
    }
    return true;
}


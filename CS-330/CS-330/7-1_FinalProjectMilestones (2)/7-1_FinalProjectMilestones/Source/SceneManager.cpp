// SceneManager.cpp
#include "SceneManager.h"  // Include your own header file
#include <iostream>        // For std::cerr and std::cout
#include <vector>         // For std::vector
#include <string>         // For std::string
#include <GL/glew.h>      // Include GLEW (or your OpenGL loader) for OpenGL functions
#include <GLFW/glfw3.h>   // Include GLFW for window and input management
#include <glm/glm.hpp>    // For glm::vec3, glm::mat4, etc.
#include <glm/gtx/transform.hpp> // For transformation functions
#include "stb_image.h"    // Include STB Image for image loading functions

namespace {
    const char* g_ModelName = "model";
    const char* g_ColorValueName = "objectColor";
    const char* g_TextureValueName = "objectTexture";
    const char* g_UseTextureName = "bUseTexture";
    const char* g_UseLightingName = "bUseLighting";
}

SceneManager::SceneManager(ShaderManager* pShaderManager)
    : m_pShaderManager(pShaderManager),
    m_basicMeshes(new ShapeMeshes()),
    m_loadedTextures(0) // Initialize to zero
{
    // Any additional initialization can go here
}

SceneManager::~SceneManager()
{
    DestroyGLTextures(); // Clean up textures
    delete m_basicMeshes;
    m_basicMeshes = nullptr; // Set to nullptr to avoid dangling pointer
}

bool SceneManager::LoadWoodTexture() {
    return CreateGLTexture("Source/Wood Texture.jpg", "WoodTexture");
}

bool SceneManager::Initialize() {
    if (!m_pShaderManager->LoadShaders("vertex_shader.glsl", "fragment_shader.glsl")) {
        std::cerr << "Error loading shaders!" << std::endl;
        return false;
    }

    if (!LoadWoodTexture()) {
        std::cerr << "Error loading wood texture!" << std::endl;
        return false;
    }

    // Prepare the scene, which includes loading shapes and binding textures
    PrepareScene();
    BindGLTextures(); // Bind textures after they have been loaded
    return true;
}

bool SceneManager::CreateGLTexture(const char* filename, std::string tag) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (data) {
        uint32_t textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        m_textureIDs.push_back(TEXTURE_INFO{ tag, textureID });
        return true;
    }
    else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }
}

void SceneManager::BindGLTextures() {
    for (const auto& texture : m_textureIDs) {
        glActiveTexture(GL_TEXTURE0 + texture.ID); // Activate each texture unit
        glBindTexture(GL_TEXTURE_2D, texture.ID); // Bind the texture
    }
}

void SceneManager::DestroyGLTextures() {
    for (const auto& texture : m_textureIDs) {
        glDeleteTextures(1, &texture.ID); // Delete the texture from OpenGL
    }
    m_textureIDs.clear(); // Clear the vector to release memory
}

int SceneManager::FindTextureID(std::string tag) {
    for (size_t i = 0; i < m_textureIDs.size(); ++i) {
        if (m_textureIDs[i].tag == tag) {
            return i;
        }
    }
    return -1;
}

int SceneManager::FindTextureSlot(std::string tag) {
    for (size_t i = 0; i < m_textureIDs.size(); ++i) {
        if (m_textureIDs[i].tag == tag) {
            return i; // Return the index of the texture
        }
    }
    return -1; // Return -1 if the texture is not found
}

bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material) {
    for (const auto& mat : m_objectMaterials) {
        if (mat.tag == tag) {
            material = mat;
            return true; // Material found
        }
    }
    return false; // Material not found
}

void SceneManager::SetShaderColor(float red, float green, float blue) {
    m_pShaderManager->setVec3(g_ColorValueName, glm::vec3(red, green, blue)); // Set color in shader
}


void SceneManager::SetShaderTexture(std::string textureTag) {
    int textureID = FindTextureID(textureTag);
    if (textureID != -1) {
        glActiveTexture(GL_TEXTURE0 + textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureIDs[textureID].ID);
    }
    else {
        std::cerr << "Texture not found: " << textureTag << std::endl;
    }
}

void SceneManager::SetTransformations(
    glm::vec3 scaleXYZ,
    float XrotationDegrees,
    float YrotationDegrees,
    float ZrotationDegrees,
    glm::vec3 positionXYZ)
{
    glm::mat4 modelView;
    glm::mat4 scale = glm::scale(scaleXYZ);
    glm::mat4 rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 translation = glm::translate(positionXYZ);

    modelView = translation * rotationX * rotationY * rotationZ * scale;

    if (m_pShaderManager != nullptr) {
        m_pShaderManager->setMat4Value(g_ModelName, modelView);
    }
}

void SceneManager::PrepareScene()
{
    m_basicMeshes->LoadPlaneMesh();
    m_basicMeshes->LoadSphereMesh();
    m_basicMeshes->LoadConeMesh();
    m_basicMeshes->LoadBoxMesh();
    m_basicMeshes->LoadCylinderMesh();
    m_basicMeshes->LoadTorusMesh(0.1f);

    LoadWoodTexture(); // Load texture for the scene
}

void SceneManager::RenderScene()
{
    glm::vec3 scaleXYZ;
    glm::vec3 positionXYZ;
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Lighting and camera settings
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, 3.0f);

    m_pShaderManager->setVec3("lightPos", lightPos);
    m_pShaderManager->setVec3("lightColor", lightColor);
    m_pShaderManager->setVec3("viewPos", viewPos);

    // Set color for the object and bind texture
    SetShaderColor(1.0f, 0.5f, 0.31f); // Example color
    SetShaderTexture("WoodTexture"); // Bind the wood texture before rendering

    // Render the objects in the scene using their transformations
    SetTransformations(glm::vec3(1.0f), 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    m_basicMeshes->DrawPlaneMesh(); // Correct method call


    // Continue rendering other objects similarly...
}

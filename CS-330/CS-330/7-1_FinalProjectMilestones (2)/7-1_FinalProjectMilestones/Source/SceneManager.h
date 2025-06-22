///////////////////////////////////////////////////////////////////////////////
// shadermanager.h
// ============
// manage the loading and rendering of 3D scenes
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ShaderManager.h"
#include "ShapeMeshes.h"

#include <string>
#include <vector>
#include <glm/glm.hpp> // Include GLM for glm types
#include <GL/glew.h>  // Include GLEW for OpenGL types

class SceneManager
{
public:
    // Constructor that initializes the shader manager
    SceneManager(ShaderManager* pShaderManager);

    // Destructor
    ~SceneManager();

    // Load the wood texture
    bool LoadWoodTexture();
    bool Initialize();  // Initialize method to set up the scene

    // The following methods are for the students to customize for their own 3D scene
    void PrepareScene();
    void RenderScene();

private:
    // Pointer to shader manager object
    ShaderManager* m_pShaderManager;

    // Pointer to basic shapes object
    ShapeMeshes* m_basicMeshes;

    // Total number of loaded textures
    int m_loadedTextures;

    // Loaded textures info as a vector for flexibility
    struct TEXTURE_INFO {
        std::string tag;
        uint32_t ID;
    };
    std::vector<TEXTURE_INFO> m_textureIDs; // Changed to std::vector

    // Defined object materials
    struct OBJECT_MATERIAL {
        float ambientStrength;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        float shininess;
        std::string tag;
    };
    std::vector<OBJECT_MATERIAL> m_objectMaterials;

    // Load texture images and convert to OpenGL texture data
    bool CreateGLTexture(const char* filename, std::string tag);

    // Bind loaded OpenGL textures to slots in memory
    void BindGLTextures();

    // Free the loaded OpenGL textures
    void DestroyGLTextures();

    // Find a loaded texture by tag
    int FindTextureID(std::string tag);

    // Find a texture slot by tag
    int FindTextureSlot(std::string tag);

    // Find a defined material by tag
    bool FindMaterial(std::string tag, OBJECT_MATERIAL& material);

    // Set the transformation values into the transform buffer
    void SetTransformations(glm::vec3 scaleXYZ, float XrotationDegrees, float YrotationDegrees, float ZrotationDegrees, glm::vec3 positionXYZ);

    // Set the color values into the shader
    void SetShaderColor(float redColorValue, float greenColorValue, float blueColorValue);


    // Set the texture data into the shader
    void SetShaderTexture(std::string textureTag);
};

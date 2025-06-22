///////////////////////////////////////////////////////////////////////////////
// viewmanager.h
// ============
// Manage the viewing of 3D objects within the viewport.
//
// AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
// Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ShaderManager.h"
#include "Camera.h" // Ensure your Camera class is defined in camera.h
#include "GLFW/glfw3.h"

class ViewManager
{
public:
    // Constructor
    ViewManager(ShaderManager* pShaderManager);

    // Destructor
    ~ViewManager();

    // Mouse position callback for mouse interaction with the 3D scene
    static void Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos);

    // Scroll callback for zoom adjustment and camera speed
    static void Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset);

private:
    // Pointer to shader manager object
    ShaderManager* m_pShaderManager;

    // Active OpenGL display window
    GLFWwindow* m_pWindow;

    // Pointer to the camera object
    Camera* m_pCamera;          // Non-static member for managing the camera

    // Camera movement speed
    float m_MovementSpeed;

    // Zoom speed (for the camera's zoom)
    float m_ZoomSpeed;

    // Process keyboard events for interaction with the 3D scene
    void ProcessKeyboardEvents();

public:
    // Create the initial OpenGL display window
    GLFWwindow* CreateDisplayWindow(const char* windowTitle);

    // Prepare the conversion from 3D object display to 2D scene display
    void PrepareSceneView();
};

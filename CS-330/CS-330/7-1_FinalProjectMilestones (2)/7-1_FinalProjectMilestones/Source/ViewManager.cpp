///////////////////////////////////////////////////////////////////////////////
// viewmanager.cpp
// ============
// Manage the viewing of 3D objects within the viewport.
//
// AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
// Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "ViewManager.h"     // Include the ViewManager header
#include "ShaderManager.h"   // Include the ShaderManager header
#include "Camera.h"          // Include the Camera header

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Declaration of global variables and defines
namespace
{
    // Variables for window width and height
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const char* g_ViewName = "view";
    const char* g_ProjectionName = "projection";

    // Camera object used for viewing and interacting with the 3D scene
    Camera* g_pCamera = nullptr;

    // These variables are used for mouse movement processing
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // Time between current frame and last frame
    float gDeltaTime = 0.0f;
    float gLastFrame = 0.0f;

    // If orthographic projection is on, this value will be true
    bool bOrthographicProjection = false;

    // Additional variable for mouse sensitivity
    float mouseSensitivity = 7.0f; // Default sensitivity change to make mouse faster
}

/***********************************************************
 *  ViewManager()
 *
 *  The constructor for the class
 ***********************************************************/
ViewManager::ViewManager(ShaderManager* pShaderManager)
    : m_pShaderManager(pShaderManager), // Initialize shader manager
    m_pWindow(nullptr),               // Initialize pointer to null
    m_pCamera(new Camera()),          // Allocate memory for camera object
    m_ZoomSpeed(1.0f),                // Default zoom speed
    m_MovementSpeed(5.0f)             // Default movement speed
{
    // Default camera view parameters
    m_pCamera->Position = glm::vec3(0.5f, 5.5f, 10.0f);
    m_pCamera->Front = glm::vec3(0.0f, -0.5f, -2.0f);
    m_pCamera->Up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_pCamera->Zoom = 80.0f;  // Set camera zoom level
}

/***********************************************************
 *  ~ViewManager()
 *
 *  The destructor for the class
 ***********************************************************/
ViewManager::~ViewManager()
{
    // Free up allocated memory and reset pointers to null
    m_pShaderManager = nullptr;
    m_pWindow = nullptr;

    if (m_pCamera != nullptr)
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }
}


/***********************************************************
 *  CreateDisplayWindow()
 *
 *  This method is used to create the main display window.
 ***********************************************************/
GLFWwindow* ViewManager::CreateDisplayWindow(const char* windowTitle)
{
    GLFWwindow* window = nullptr;

    // Try to create the displayed OpenGL window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // This callback is used to receive mouse moving events
    glfwSetCursorPosCallback(window, &ViewManager::Mouse_Position_Callback);
    glfwSetScrollCallback(window, &ViewManager::Mouse_Scroll_Callback); // Add scroll callback

    // Enable blending for supporting transparent rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pWindow = window;

    return window;
}

/***********************************************************
 *  Mouse_Position_Callback()
 *
 *  This method is automatically called from GLFW whenever
 *  the mouse is moved within the active GLFW display window.
 ***********************************************************/
void ViewManager::Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos)
{
    // Check if the left mouse button is currently pressed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // When the first mouse move event is received, record the last position
        if (gFirstMouse)
        {
            gLastX = xMousePos;
            gLastY = yMousePos;
            gFirstMouse = false;
        }

        // Calculate the X offset and Y offset values for moving the 3D camera accordingly
        float xOffset = (xMousePos - gLastX) * mouseSensitivity; // Apply sensitivity
        float yOffset = (gLastY - yMousePos) * mouseSensitivity; // Reversed since y-coordinates go from bottom to top

        // Set the current positions into the last position variables
        gLastX = xMousePos;
        gLastY = yMousePos;

        // Move the 3D camera according to the calculated offsets
        g_pCamera->ProcessMouseMovement(xOffset, yOffset);
    }
    else
    {
        // Reset the first mouse flag if the left button is not pressed
        gFirstMouse = true;
    }
}

/***********************************************************
 *  Mouse_Scroll_Callback()
 *
 *  This method is automatically called from GLFW whenever
 *  the mouse wheel is scrolled.
 ***********************************************************/
void ViewManager::Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
    // Adjust camera zoom based on scroll
    g_pCamera->Zoom -= (float)yOffset; // Adjust zoom
    if (g_pCamera->Zoom < 1.0f) g_pCamera->Zoom = 1.0f; // Limit zoom
    if (g_pCamera->Zoom > 45.0f) g_pCamera->Zoom = 45.0f; // Limit zoom
}

/***********************************************************
 *  ProcessKeyboardEvents()
 *
 *  This method is called to process any keyboard events
 *  that may be waiting in the event queue.
 ***********************************************************/
void ViewManager::ProcessKeyboardEvents()
{
    // Close the window if the escape key has been pressed
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, true);
    }

    // If the camera object is null, then exit this method
    if (NULL == g_pCamera)
    {
        return;
    }

    // Process camera zooming in and out
    if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(FORWARD, gDeltaTime);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(BACKWARD, gDeltaTime);
    }

    // Process camera panning left and right
    if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(LEFT, gDeltaTime);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(RIGHT, gDeltaTime);
    }

    // Process camera moving up and down
    if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS)
    {
        g_pCamera->Position += g_pCamera->Up * g_pCamera->MovementSpeed * gDeltaTime; // Move Up
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS)
    {
        g_pCamera->Position -= g_pCamera->Up * g_pCamera->MovementSpeed * gDeltaTime; // Move Down
    }
}

/***********************************************************
 *  PrepareSceneView()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes and textures in memory to support the 3D scene
 *  rendering
 ***********************************************************/
void ViewManager::PrepareSceneView()
{
    glm::mat4 view;
    glm::mat4 projection;

    // Per-frame timing
    float currentFrame = static_cast<float>(glfwGetTime()); // Cast to float to avoid warning
    gDeltaTime = currentFrame - gLastFrame;
    gLastFrame = currentFrame;


    // Process any keyboard events that may be waiting in the event queue
    ProcessKeyboardEvents();

    // Trigger the update of the Right and Up vectors based on the current Front vector
    g_pCamera->RecalculateVectors();

    // Get the current view matrix from the camera
    view = g_pCamera->GetViewMatrix();

    // Define the current projection matrix
    projection = glm::perspective(glm::radians(g_pCamera->Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

    // If the shader manager object is valid
    if (NULL != m_pShaderManager)
    {
        // Set the view matrix into the shader for proper rendering
        m_pShaderManager->setMat4Value(g_ViewName, view);
        // Set the projection matrix into the shader for proper rendering
        m_pShaderManager->setMat4Value(g_ProjectionName, projection);
        // Set the view position of the camera into the shader for proper rendering
        m_pShaderManager->setVec3("viewPosition", g_pCamera->Position);
    }
}

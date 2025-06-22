#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    // Camera attributes
    glm::vec3 Position;    // Camera position in world space
    glm::vec3 Front;       // Direction the camera is facing
    glm::vec3 Up;          // Up vector
    glm::vec3 Right;       // Right vector
    glm::vec3 WorldUp;     // World up vector
    float Yaw;             // Yaw angle
    float Pitch;           // Pitch angle
    float Zoom;            // Camera zoom level
    float MovementSpeed;   // Speed of camera movement

    // Default Constructor
    Camera();

    // Parameterized Constructor
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float zoom = 45.0f, float movementSpeed = 2.5f);

    // Destructor
    ~Camera();

    // Accessor to set orientation and update vectors
    void SetOrientation(float newYaw, float newPitch);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // Processes input received from a mouse movement event
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    // Processes input received from keyboard keys
    void ProcessKeyboard(CameraMovement direction, float deltaTime);

    // Adjust the camera speed based on mouse scroll input
    void AdjustSpeed(float offset);

    // Public method to update camera vectors
    void Update();

    // Public method to recalculate the camera's vectors
    void RecalculateVectors() {
        UpdateCameraVectors(); // Call the private method
    }

private:
    bool isDragging; // To track if the mouse is being dragged

    // Update the camera's vectors based on yaw and pitch
    void UpdateCameraVectors(); // Keep this private to encapsulate its logic
};

#endif // CAMERA_H

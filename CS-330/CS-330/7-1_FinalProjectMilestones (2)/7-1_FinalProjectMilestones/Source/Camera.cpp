#include "Camera.h"


// Default Constructor
Camera::Camera()
    : Position(glm::vec3(0.0f, 0.0f, 3.0f)), // Default position
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),  // Default front vector
    Up(glm::vec3(0.0f, 1.0f, 0.0f)),      // Default up vector
    Right(glm::vec3(1.0f, 0.0f, 0.0f)),   // Default right vector
    WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), // World up vector
    Yaw(-90.0f),                          // Default yaw
    Pitch(0.0f),                          // Default pitch
    Zoom(45.0f),                          // Default zoom level
    MovementSpeed(2.5f)                  // Default movement speed
{
    UpdateCameraVectors(); // Initialize the camera vectors
}

// Parameterized Constructor
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float zoom, float movementSpeed)
    : Position(position),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch),
    Zoom(zoom),
    MovementSpeed(movementSpeed)
{
    UpdateCameraVectors(); // Set the front vector to point forward based on Yaw and Pitch
}

// Destructor
Camera::~Camera() {
    // Clean up resources if needed (not necessary in this case)
}

// Returns the view matrix
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

// Processes mouse movement
void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= 0.1f; // Sensitivity scaling
    yOffset *= 0.1f; // Sensitivity scaling

    Yaw += xOffset;
    Pitch += yOffset;

    // Constrain pitch
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

// Processes keyboard input
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

// Adjust the camera speed based on mouse scroll input
void Camera::AdjustSpeed(float offset) {
    MovementSpeed += offset; // Increment or decrement the movement speed
    // Clamp the speed to a reasonable range (optional)
    if (MovementSpeed < 0.1f) MovementSpeed = 0.1f; // Minimum speed
    if (MovementSpeed > 10.0f) MovementSpeed = 10.0f; // Maximum speed
}

// Set the camera orientation based on yaw and pitch
void Camera::SetOrientation(float newYaw, float newPitch) {
    Yaw = newYaw;
    Pitch = newPitch;
    UpdateCameraVectors(); // Ensure the camera vectors are updated
}

// Updates the camera vectors based on yaw and pitch
void Camera::UpdateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    // Recalculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors
    Up = glm::normalize(glm::cross(Right, Front));
}

// Public method to update camera vectors
void Camera::Update() {
    UpdateCameraVectors(); // Call the private method to update vectors
}

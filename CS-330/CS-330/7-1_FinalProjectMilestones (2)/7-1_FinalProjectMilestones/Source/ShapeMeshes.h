#ifndef SHAPE_MESHES_H
#define SHAPE_MESHES_H

#include <GL/glew.h>  // Include GLEW header for GLuint type

class ShapeMeshes {
public:
    // Constructor
    ShapeMeshes();

    // Load functions to prepare the mesh data
    void LoadPlaneMesh();
    void LoadSphereMesh();
    void LoadConeMesh();
    void LoadBoxMesh();          // Renamed from LoadCubeMesh
    void LoadCylinderMesh();
    void LoadTorusMesh(float thickness); // Include the thickness parameter here
    // wasn't recongized had to include parameter checked shapeMeshes.cpp then recongized

    // Draw functions to render the mesh data
    void DrawPlaneMesh();
    void DrawSphereMesh();
    void DrawTorusMesh();
    void DrawConeMesh(bool bDrawBottom); // Include the bDrawBottom parameter here
    void DrawBoxMesh();          // Renamed from DrawCubeMesh
    void DrawCylinderMesh(bool bDrawTop, bool bDrawBottom, bool bDrawSides);

private:
    // Member variables to hold mesh IDs
    GLuint m_PlaneMesh;
    GLuint m_SphereMesh;
    GLuint m_ConeMesh;
    GLuint m_BoxMesh;
    GLuint m_CylinderMesh;
    GLuint m_TorusMesh;
};

#endif // SHAPE_MESHES_H

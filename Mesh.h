#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glad/glad.h> // Include GLAD for OpenGL functions
#include "ShaderHeader.h" // Assuming Shader class is defined elsewhere

class Mesh {
public:
    Mesh(const std::string& name);
    ~Mesh();

    void draw(Shader& shader) const;

private:
    std::string name;
    unsigned int VAO, VBO, EBO;
    unsigned int indicesCount; // Add this line to store the number of indices

    void setupMesh();
};

#endif // MESH_H

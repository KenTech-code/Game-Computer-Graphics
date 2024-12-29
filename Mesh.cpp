#include "Mesh.h"
#include <iostream>  // Include this to use std::cout and std::endl

Mesh::Mesh(const std::string& name) : name(name), indicesCount(0) { // Initialize indicesCount to 0
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh() {
    // Mock geometry data
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    std::vector<unsigned int> indices = { 0, 1, 2 };
    indicesCount = indices.size();  // Set the number of indices

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader) const {
    // Bind the vertex array
    glBindVertexArray(VAO);

    // Set up shaders and other necessary uniforms
    shader.use();

    // Draw the mesh 
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);  // Use indicesCount here

    // Unbind the vertex array
    glBindVertexArray(0);
}

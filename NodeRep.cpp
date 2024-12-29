#include "NodeRep.h"
#include <glm/gtc/matrix_transform.hpp> // For matrix transformations

NodeRep::NodeRep(const std::string& nodeName) : name(nodeName), position(0.0f), rotation(0.0f), scale(1.0f), localTransform(glm::mat4(1.0f)) {}


glm::mat4 NodeRep::getLocalTransform() const {
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translateMatrix * rotateMatrix * scaleMatrix;
}

void NodeRep::setPosition(const glm::vec3& pos) {
    position = pos; // Set the position
}

void NodeRep::setRotation(const glm::vec3& rot) {
    rotation = rot; // Set the rotation (Euler Angles)
}

void NodeRep::setScale(const glm::vec3& scl) {
    scale = scl; // Set the scale
}

void NodeRep::addChild(NodeRep* child) {
    if (child) {
        children.push_back(child); // Add child node
    }
}

const std::vector<NodeRep*>& NodeRep::getChildren() const {
    return children; // Return child nodes
}

#include "ObjectRep.h"

// Constructor initializes meshName
ObjectRep::ObjectRep(const std::string& meshName) : meshName(meshName) {}

// isObjectRep simply returns true for ObjectRep
bool ObjectRep::isObjectRep() const {
    return true;
}

// Getter for mesh name
const std::string& ObjectRep::getMeshName() const {
    return meshName;
}

// Setter for mesh name
void ObjectRep::setMeshName(const std::string& mesh) {
    meshName = mesh;
}

#ifndef NODEREP_H
#define NODEREP_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

class NodeRep {
public:
    virtual bool isObjectRep() const { return false; }
    virtual const glm::mat4& getLocalTransform() const { return localTransform; }
    virtual void addChild(NodeRep* child) { children.push_back(child); }
    const std::vector<NodeRep*>& getChildren() const { return children; }

protected:
    glm::mat4 localTransform = glm::mat4(1.0f);  // Default identity transform
    std::vector<NodeRep*> children;
};

class ObjectRep : public NodeRep {
public:
    ObjectRep(const std::string& meshName) : meshName(meshName) {}
    bool isObjectRep() const override { return true; }
    const std::string& getMeshName() const { return meshName; }

private:
    std::string meshName;
};

#endif // NODEREP_H

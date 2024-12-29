#ifndef OBJECTREP_H
#define OBJECTREP_H

#include "NodeRep.h"
#include <string>

class ObjectRep : public NodeRep {
public:
    ObjectRep(const std::string& meshName) : meshName(meshName) {}
    virtual bool isObjectRep() const override { return true; }

    void setMeshName(const std::string& mesh) { meshName = mesh; }
    const std::string& getMeshName() const { return meshName; }

private:
    std::string meshName;
};

#endif // OBJECTREP_H

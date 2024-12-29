#ifndef SCENEDESCRIPTION_H
#define SCENEDESCRIPTION_H

#include <string>
#include <map>
#include <vector>
#include "NodeRep.h"
#include "Mesh.h"

class SceneDescription {
public:
    SceneDescription(const std::string& gltfFilePath);
    ~SceneDescription();

    bool isValid() const { return valid; }
    NodeRep* getRootNode() const { return rootNode; }
    const Mesh* getMesh(const std::string& name) const;

private:
    void parseGLTFFile(const std::string& gltfFilePath);
    void clearScene();

    NodeRep* rootNode;
    std::map<std::string, Mesh*> meshes;
    bool valid = false;
};

#endif // SCENEDESCRIPTION_H

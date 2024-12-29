#include "SceneDescription.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp> // Include nlohmann JSON library

using json = nlohmann::json;

SceneDescription::SceneDescription(const std::string& gltfFilePath) {
    parseGLTFFile(gltfFilePath);
}

SceneDescription::~SceneDescription() {
    clearScene();
}

void SceneDescription::parseGLTFFile(const std::string& gltfFilePath) {
    std::ifstream file(gltfFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open glTF file: " << gltfFilePath << std::endl;
        valid = false;
        return;
    }

    json gltfJson;
    try {
        file >> gltfJson; // Parse JSON
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing glTF JSON file: " << e.what() << std::endl;
        valid = false;
        return;
    }

    // Check if the required keys exist in the JSON file
    if (gltfJson.find("nodes") == gltfJson.end()) {
        std::cerr << "Error: 'nodes' not found in glTF file" << std::endl;
        valid = false;
        return;
    }
    std::cout << "Found 'nodes' in glTF file." << std::endl;

    const auto& nodes = gltfJson["nodes"];
    if (!nodes.is_array()) {
        std::cerr << "Invalid glTF structure: 'nodes' is not an array" << std::endl;
        valid = false;
        return;
    }
    std::cout << "Parsed 'nodes' array successfully." << std::endl;

    rootNode = new NodeRep(); // Creating a root node

    // Parse nodes into the root node and create corresponding Mesh objects
    for (const auto& node : nodes) {
        if (node.contains("mesh")) {
            if (node["mesh"].is_number_integer()) { // If it's an integer, use it as an ID
                int meshIndex = node["mesh"];
                std::string meshName = "mesh_" + std::to_string(meshIndex);  // For example, "mesh_0"
                auto* objectNode = new ObjectRep(meshName);
                rootNode->addChild(objectNode);

                // Simulate mesh creation
                meshes[objectNode->getMeshName()] = new Mesh(objectNode->getMeshName());
                std::cout << "Added mesh: " << objectNode->getMeshName() << std::endl;
            }
            else if (node["mesh"].is_string()) {
                auto* objectNode = new ObjectRep(node["mesh"].get<std::string>());
                rootNode->addChild(objectNode);

                // Simulate mesh creation
                meshes[objectNode->getMeshName()] = new Mesh(objectNode->getMeshName());
                std::cout << "Added mesh: " << objectNode->getMeshName() << std::endl;
            }
            else {
                std::cerr << "Warning: Node 'mesh' is neither string nor integer" << std::endl;
            }
        }
        else {
            std::cerr << "Warning: Node missing 'mesh' key" << std::endl;
        }

        // Handle other types of nodes (e.g., LightRep, CameraRep, etc.)
        // You can add these logic checks here as needed
    }

    valid = true;
    std::cout << "Scene parsed successfully. " << meshes.size() << " meshes loaded." << std::endl;
}

void SceneDescription::clearScene() {
    delete rootNode;
    for (auto& pair : meshes) {
        delete pair.second;
    }
    meshes.clear();
    std::cout << "Scene cleared successfully." << std::endl;
}

const Mesh* SceneDescription::getMesh(const std::string& name) const {
    auto it = meshes.find(name);
    if (it != meshes.end()) {
        std::cout << "Mesh found: " << name << std::endl;
        return it->second;
    }
    else {
        std::cerr << "Error: Mesh not found: " << name << std::endl;
        return nullptr;
    }
}

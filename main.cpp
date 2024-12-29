#include "GladHeader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "ShaderHeader.h"
#include "SceneDescription.h"

// Function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void renderNode(const NodeRep* node, const glm::mat4& parentTransform, Shader& shader, SceneDescription& scene);

int main() {
    const std::string gltfFilePath = "A:/Milestone2/build/Debug/models/example1.gltf";
    std::cout << "Attempting to load glTF file: " << gltfFilePath << std::endl;

    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Project", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    std::cout << "GLFW window created successfully." << std::endl;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "GLAD loaded successfully." << std::endl;

    glEnable(GL_DEPTH_TEST);
    std::cout << "Depth testing enabled." << std::endl;

    Shader shader("A:/Milestone2/build/Debug/shaders/VertexShader.glsl", "A:/Milestone2/build/Debug/shaders/FragmentShader.glsl");
    std::cout << "Shaders loaded successfully." << std::endl;

    SceneDescription scene(gltfFilePath);
    if (!scene.isValid()) {
        std::cerr << "Failed to parse glTF file: " << gltfFilePath << std::endl;
        return -1;
    }
    std::cout << "glTF file parsed successfully." << std::endl;

    glm::vec3 cameraPos(0.0f, 5.0f, 10.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        renderNode(scene.getRootNode(), glm::mat4(1.0f), shader, scene);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "GLFW terminated successfully." << std::endl;
    return 0;
}

void renderNode(const NodeRep* node, const glm::mat4& parentTransform, Shader& shader, SceneDescription& scene) {
    glm::mat4 transform = parentTransform * node->getLocalTransform();

    if (node->isObjectRep()) {
        const ObjectRep* objectNode = dynamic_cast<const ObjectRep*>(node);
        if (objectNode) {
            const Mesh* mesh = scene.getMesh(objectNode->getMeshName());
            if (mesh) {
                shader.setMat4("model", transform);
                mesh->draw(shader);
            }
            else {
                std::cerr << "Error: Mesh not found: " << objectNode->getMeshName() << std::endl;
            }
        }
    }

    for (const NodeRep* child : node->getChildren()) {
        renderNode(child, transform, shader, scene);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

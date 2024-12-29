#ifndef SHADER_HEADER_H
#define SHADER_HEADER_H

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use();
    void setMat4(const std::string& name, const glm::mat4& value);
    bool isValid() const { return valid; }

private:
    unsigned int ID;
    bool valid = false;

    std::string loadShaderSource(const char* filePath);
    void compileShader(unsigned int shader, const char* code, const std::string& type);
};

#endif // SHADER_HEADER_H

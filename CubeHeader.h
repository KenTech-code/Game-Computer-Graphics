#ifndef CUBE_H
#define CUBE_H

#include <GladHeader.h>

class Cube {
public:
    Cube();
    ~Cube();
    void draw();

private:
    unsigned int VAO, VBO, EBO;
    void setupCube();
};

#endif

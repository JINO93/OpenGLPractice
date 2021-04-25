#ifndef GRID_H
#define GRID_H

#include "Shape.h"

class Grid : public Shape
{
  public:
    Grid():Shape("./shader/grid_vertex.glsl", "./shader/grid_fragment.glsl"){}
    Grid(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) {}
    ~Grid(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

  private:
    int texture0Id;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

#endif
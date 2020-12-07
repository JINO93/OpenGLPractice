#ifndef TRIANLE_H
#define TRIANLE_H

#include "Shape.h"

class Trianle : public Shape
{
  public:
    Trianle():Shape("./shader/triangle_vertex.glsl", "./shader/triangle_fragment.glsl"){}
    Trianle(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) {}
    ~Trianle(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

  private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

#endif
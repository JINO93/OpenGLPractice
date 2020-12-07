#ifndef RETANGLEWITHTEXTURE_H
#define RETANGLEWITHTEXTURE_H

#include "Shape.h"

class RetangleWithTexture : public Shape
{
  public:
    RetangleWithTexture():Shape("./shader/triangle_vertex.glsl","./shader/triangle_fragment.glsl") {}
    RetangleWithTexture(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) {}
    ~RetangleWithTexture(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

  private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int textureId;
    unsigned int textureId2;
};

#endif
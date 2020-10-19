#ifndef CUBEWITHTEXTURE_H
#define CUBEWITHTEXTURE_H

#include "Shape.h"

class CubeWithTexture : public Shape
{
  public:
    CubeWithTexture(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) {}
    ~CubeWithTexture(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

  private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int textureVBO;
    unsigned int textureId;
    static float vertexs[];
};

#endif
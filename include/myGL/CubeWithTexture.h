#ifndef CUBEWITHTEXTURE_H
#define CUBEWITHTEXTURE_H

#include "Shape.h"
#include "IControllable.h"

class CubeWithTexture : public Shape,virtual public IControllable
{
  public:
    CubeWithTexture():Shape("./shader/cube_vertex.glsl", "./shader/cube_fragment.glsl"){}
    CubeWithTexture(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) ,IControllable(){}
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
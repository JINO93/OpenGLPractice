#ifndef _INSTANCESCENE_H
#define _INSTANCESCENE_H
// #ifdef __cplusplus
//     extern "C"
// {
// #endif

#include "Shape.h"
// #include "IControllable.h"

    class InstanceScene : public Shape
    {
    public:
        InstanceScene() : Shape("./shader/model_vertex.glsl", "./shader/planet_fragment.glsl") {}
        InstanceScene(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath) {}
        ~InstanceScene() {}
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

// #ifdef __cplusplus
// }
// #endif
#endif // _INSTANCESCENE_H
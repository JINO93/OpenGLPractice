#ifndef _CUSTOMMODEL_H 
#define _CUSTOMMODEL_H 
// #ifdef __cplusplus
// extern "C" {
// #endif

#include <myGl/Shape.h>

class CustomModel : public Shape
{
  public:
    CustomModel():Shape(){}
    CustomModel(const char *vertexPath, const char *fragmentPath) : Shape(vertexPath, fragmentPath){}
    ~CustomModel(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

//   private:
    // Model* mModel;

};

// #ifdef __cplusplus
// }
// #endif
#endif	// _CUSTOMMODEL_H
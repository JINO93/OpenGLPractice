#ifndef SHAPE_H
#define SHAPE_H

class Shape{
public:
    Shape(){};
    Shape(const char *vertexPath,const char *fragmentPath);
    ~Shape(){}
    virtual void destroy();

    virtual void init();
    virtual void draw();

protected:
    unsigned int programId;

};

#endif
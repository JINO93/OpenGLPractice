#ifndef ICONTROLLABLE_H
#define ICONTROLLABLE_H

// #include <GLFW/glfw3.h>

class IControllable
{
public:
    IControllable(){}
    ~IControllable(){}
    virtual void onKeyInput(int keyEvent);

    virtual void onMouseMove(double xpos, double ypos);

    virtual void onScroll(double xoffset, double yoffset);
};

#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// #include <string.h>
#include <myGL/ShaderUtil.h>
#include <myGL/RetangleWithTexture.h>

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void handleInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void frameBufferSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
#endif
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置窗口大小变化回调
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
    // TODO 设置鼠标位置变化回调
    // glfwSetCursorPosCallback

    RetangleWithTexture trianle(".\\shader\\retangle_vertex.glsl",".\\shader\\retangle_fragment.glsl");
    trianle.init();

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //处理输入事件
        handleInput(window);
        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        trianle.draw();
        // glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
        // ---------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //清理数据
    trianle.destroy();

    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    // system("pause");
    return 0;
}

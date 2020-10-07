#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// #include <string.h>
using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vetc_shader = "#version 330 core\n" 
"layout(location = 0) in vec3 aPos\n;" 
"void main(){\n"  
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"  
"}\n";

const char *fragment_shader = "#version 330 core\n" 
"out vec4 gl_FragColor;\n" 
"void main(){\n" 
"gl_FragColor = vec4(1.0,0.2,0.5,1.0);\n"  
"}\n";

int createShader(const char *source, int type)
{
    int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int res;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "craete shader " << type << " failed error:" << infoLog << endl;
        return 0;
    }
    return shader;
}

int createProgram(const char *vetShaderSource,const char *fragShaderSource)
{
    int vShader = createShader(vetShaderSource, GL_VERTEX_SHADER);
    if (!vShader)
        return 0;
    int fShader = createShader(fragShaderSource, GL_FRAGMENT_SHADER);
    if (!fShader)
        return 0;
    
    int program = glCreateProgram();
    glAttachShader(program,vShader);
    glAttachShader(program,fShader);
    glLinkProgram(program);
    int res;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &res);
    if (!res)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "craete program failed error:" << infoLog << endl;
        return 0;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return program;
}

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

    //初始化gl程序
    int program = createProgram(vetc_shader,fragment_shader);
    if(!program){
        return -1;
    }

    //处理渲染数据
    float vertexs[] = {
         0.5f, 0.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,
         -0.5f, 0.0f, 0.0f, // left  
         0.0f,  -0.5f, 0.0f

    };
    unsigned int indexs[] = {
        0,1,2,
        2,0,3
    };
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    //绑定顶点数据
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexs),vertexs,GL_STATIC_DRAW);

    //绑定顶点引索数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexs),indexs,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //处理输入事件
        handleInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES,sizeof(indexs)/sizeof(indexs[0]),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
        // ---------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //清理数据
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(program);

    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    // system("pause");
    return 0;
}

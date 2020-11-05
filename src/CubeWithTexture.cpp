#include <myGL/CubeWithTexture.h>
#include <myGL/ShaderUtil.h>
// #include <myGL/Shape.h>
// #include <myGL/IControllable.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>
#include <myGL/CameraHelper.h>

float CubeWithTexture::vertexs[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

 glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

bool firstMouseMove = true;
float lastX = 0;
float lastY = 0;

float deltaTime = 0.0f;
float lastTime = 0.0f;
CameraHelper camHelper;

void CubeWithTexture::init()
{
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    textureId = ShaderUtil::createTexture("./resource/texture/container.jpg");

    glBindVertexArray(VAO);

    //绑定数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);


    //顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //注意：设置uniform前需要先启用program！！！！！！！！！
    glUseProgram(programId);
    glUniform1i(glGetUniformLocation(programId, "outTexture"), 0); 
    // glUniform1i(glGetUniformLocation(programId, "outTexture2"), 1); 
}

void CubeWithTexture::draw()
{
    float time = glfwGetTime();
    deltaTime = time - lastTime;
    lastTime = time;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);

    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1,GL_FALSE,glm::value_ptr(camHelper.getViewMatrix())); 
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1,GL_FALSE,glm::value_ptr(camHelper.getProjectionMatrix())); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glBindVertexArray(VAO);

    for(int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]);i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,0.3,1.0));
        model = glm::scale(model,glm::vec3(0.5,0.5,0.5));
        model = glm::translate(model,cubePositions[i]);
        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1,GL_FALSE,glm::value_ptr(model)); 
        glDrawArrays(GL_TRIANGLES,0,sizeof(vertexs)/sizeof(vertexs[0]));
        // glDrawElements(GL_TRIANGLES, sizeof(indexs1) / sizeof(indexs1[0]), GL_UNSIGNED_INT, 0);
    }


    glBindVertexArray(0);
}

void IControllable::onKeyInput(int keyEvent){
    std::cout << "onKey:" << keyEvent  << std::endl;
    if(GLFW_KEY_W == keyEvent){
        camHelper.handleKeyboardEvent(FORWARD,deltaTime);
    }else if(GLFW_KEY_S == keyEvent){
        camHelper.handleKeyboardEvent(BACKWARD,deltaTime);
    }else if(GLFW_KEY_A == keyEvent){
        camHelper.handleKeyboardEvent(LEFT,deltaTime);
    }else if(GLFW_KEY_D == keyEvent){
        camHelper.handleKeyboardEvent(RIGHT,deltaTime);
    }

}

void IControllable::onMouseMove(double xpos, double ypos){
    std::cout << "xP:" << xpos << "  yP:" << ypos << std::endl;
    if(firstMouseMove){
        lastX = xpos;
        lastY = ypos;
        firstMouseMove = false;
    }

    float dx = xpos - lastX;
    float dy = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camHelper.onMove(dx,dy);
}

void IControllable::onScroll(double xoffset, double yoffset){
    std::cout << "xOff:" << xoffset << "  yOff:" << yoffset << std::endl;
    camHelper.onScroll(xoffset,yoffset);
}

void CubeWithTexture::destroy()
{
    Shape::destroy();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

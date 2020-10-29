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
#include <GLFW/glfw3.h>

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

// float CubeWithTexture::tranPos[] = {0.0,0.0};

float fov;
glm::vec3 camPos = glm::vec3(0.0,0.0,-3.0);
glm::vec3 frontPos = glm::vec3(0.0,0.0,1.0);
glm::vec3 upPos = glm::vec3(0.0,1.0,0.0);
float camSpeed = 0.005f;

void CubeWithTexture::init()
{
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    fov = 45.0f;
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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,0.3,1.0));
    model = glm::scale(model,glm::vec3(0.5,0.5,0.5));
    glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1,GL_FALSE,glm::value_ptr(model)); 

    glm::mat4 view = glm::lookAt(camPos,camPos + frontPos,upPos);
    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1,GL_FALSE,glm::value_ptr(view)); 

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov),1.33f,0.2f,100.0f);
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1,GL_FALSE,glm::value_ptr(projection)); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,sizeof(vertexs)/sizeof(vertexs[0]));
    // glDrawElements(GL_TRIANGLES, sizeof(indexs1) / sizeof(indexs1[0]), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void IControllable::onKeyInput(int keyEvent){
    std::cout << "onKey:" << keyEvent  << std::endl;
    if(GLFW_KEY_W == keyEvent){
        camPos += camSpeed * frontPos;
    }else if(GLFW_KEY_S == keyEvent){
        camPos -= camSpeed * frontPos;
    }else if(GLFW_KEY_A == keyEvent){
        camPos += glm::normalize(glm::cross(frontPos,upPos)) * camSpeed;
    }else if(GLFW_KEY_D == keyEvent){
        camPos -= glm::normalize(glm::cross(frontPos,upPos)) * camSpeed;
    }

}

void IControllable::onMouseMove(double xpos, double ypos){
    std::cout << "xP:" << xpos << "  yP:" << ypos << std::endl;
}

void IControllable::onScroll(double xoffset, double yoffset){
    std::cout << "xOff:" << xoffset << "  yOff:" << yoffset << std::endl;
    fov += yoffset * 1.0f;
    if(fov > 90.0f){
        fov = 90.0f;
    }else if(fov < 12.0f){
        fov = 12.0f;
    }
}

void CubeWithTexture::destroy()
{
    Shape::destroy();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

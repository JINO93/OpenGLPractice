#include <myGL/RetangleWithTexture.h>
#include <myGL/Shape.h>
#include <myGL/ShaderUtil.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

//处理渲染数据
float vertexs1[20] = {
    -0.5f,  0.5f,   0.0f,   0.0f,1.0f,
    -0.5f, -0.5f,   0.0f,   0.0f,0.0f,
     0.5f, -0.5f,  0.0f,   1.0f,0.0f,
     0.5f,  0.5f,   0.0f,   1.0f,1.0f

};
unsigned int indexs1[6] = {
    0, 1, 2,
     2, 3,0};

void RetangleWithTexture::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    textureId = ShaderUtil::createTexture("./resource/texture/container.jpg");
    textureId2 = ShaderUtil::createTexture("./resource/texture/awesomeface.png");

    glBindVertexArray(VAO);

    //绑定数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs1), vertexs1, GL_STATIC_DRAW);

    //绑定顶点引索数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs1), indexs1, GL_STATIC_DRAW);

    //顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUniform1i(glGetUniformLocation(programId, "outTexture"), 0); 
    glUniform1i(glGetUniformLocation(programId, "outTexture2"), 1); 
}

void RetangleWithTexture::draw()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textureId2);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES, sizeof(indexs1) / sizeof(indexs1[0]), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RetangleWithTexture::destroy()
{
    Shape::destroy();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

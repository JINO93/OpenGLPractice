#include <myGL/Grid.h>
#include <glad/glad.h>
#include <myGL/ShaderUtil.h>
#include <GLFW/glfw3.h>

float rectVertexs[12] = {
    -1.0f,  1.0f,   0.0f,
    -1.0f, -1.0f,   0.0f, 
     1.0f, -1.0f,  0.0f,
     1.0f,  1.0f,   0.0f
};

unsigned int rectIndexs1[6] = {
    0, 1, 2,
     2, 3,0};

void Grid::init(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    //绑定数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertexs), rectVertexs, GL_STATIC_DRAW);

    //绑定顶点引索数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndexs1), rectIndexs1, GL_STATIC_DRAW);

    //顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(programId);
    ShaderUtil::setUniform2f(programId,"screenSize",800.0,600.0);
}

void Grid::draw()
{
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programId);
    ShaderUtil::setUniform1f(programId,"u_time",glfwGetTime());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,sizeof(rectIndexs1)/sizeof(rectIndexs1[0]),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Grid::destroy()
{
    Shape::destroy();
}
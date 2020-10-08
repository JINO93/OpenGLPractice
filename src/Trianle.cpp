#include <myGL/Trianle.h>
#include <myGL/Shape.h>
#include <glad/glad.h>

//处理渲染数据
float vertexs[12] = {
    0.5f, 0.0f, 0.0f, // right
    0.0f, 0.5f, 0.0f,
    -0.5f, 0.0f, 0.0f, // left
    0.0f, -0.5f, 0.0f

};
unsigned int indexs[6] = {
    0, 1, 2,
    2, 0, 3};

void Trianle::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //绑定顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

    //绑定顶点引索数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Trianle::draw()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programId);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(indexs[0]), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Trianle::destroy()
{
    Shape::destroy();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

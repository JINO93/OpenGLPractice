#include <myGL/CustomModel.h>
#include <model/Model.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

Model* mModel;
glm::vec3 lampPos(0.5f, 1.0f, 1.5f);


void CustomModel::init(){
    mModel = new Model("resource/model/sophia/rp_sophia_animated_003_idling.fbx");

    glEnable(GL_DEPTH_TEST);
    glUseProgram(programId);
    
    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0,0.0,3.0)
            ,glm::vec3(0.0,0.0,-1.0)
            ,glm::vec3(0.0,1.0,0.0)
        );
    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1,GL_FALSE,glm::value_ptr(view));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),1.33f,0.1f,100.0f); 
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1,GL_FALSE,glm::value_ptr(projection));
    // todo 封装对着色器变量赋值的方法

    // 设置光源属性 点光源
    GLint lightAmbientLoc = glGetUniformLocation(programId, "light.ambient");
    GLint lightDiffuseLoc = glGetUniformLocation(programId, "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(programId, "light.specular");
    GLint lightPosLoc = glGetUniformLocation(programId, "light.position");
    GLint attConstant = glGetUniformLocation(programId, "light.constant");
    GLint attLinear = glGetUniformLocation(programId, "light.linear");
    GLint attQuadratic = glGetUniformLocation(programId, "light.quadratic");
    glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(lightPosLoc, lampPos.x, lampPos.y, lampPos.z);
    // 设置衰减系数
    glUniform1f(attConstant, 1.0f);
    glUniform1f(attLinear, 0.09f);
    glUniform1f(attQuadratic, 0.032f);

    // glUniform3f(glGetUniformLocation(programId, "lightPos"), 1.2f, 1.0f, 2.0f);
    glUniform3f(glGetUniformLocation(programId, "viewPos"),0.0,10.0,30.0);
    // glUniform3f(glGetUniformLocation(programId, "lightColor"),1.0,1.0,1.0);
}

void CustomModel::draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,1.0,0.0));
    model = glm::scale(model,glm::vec3(0.015,0.015,0.015));
    model = glm::translate(model,glm::vec3(0.0,-58.0,0.0));
    glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1,GL_FALSE,glm::value_ptr(model)); 

    mModel->Draw(programId);
}

void CustomModel::destroy(){

}
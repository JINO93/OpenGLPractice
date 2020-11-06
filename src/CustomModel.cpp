#include <myGL/CustomModel.h>
#include <model/Model.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

// Model mModel("F:/CProject/OpenGLPractice/resource/model/nanosuit/nanosuit.obj");
Model* mModel;

void CustomModel::init(){
    mModel = new Model("F:/CProject/OpenGLPractice/resource/model/nanosuit/nanosuit.obj");

    glEnable(GL_DEPTH_TEST);
    glUseProgram(programId);
    
    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0,10.0,30.0)
            ,glm::vec3(0.0,10.0,-1.0)
            ,glm::vec3(0.0,1.0,0.0)
        );
    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1,GL_FALSE,glm::value_ptr(view));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),1.33f,0.1f,100.0f); 
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1,GL_FALSE,glm::value_ptr(projection));
}

void CustomModel::draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,1.0,0.0));
    glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1,GL_FALSE,glm::value_ptr(model)); 

    // mModel.Draw(programId);
    mModel->Draw(programId);
}

void CustomModel::destroy(){

}
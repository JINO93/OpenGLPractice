#include <myGL/CustomModel.h>
#include <model/Model.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>
#include <myGL/ShaderUtil.h>

Model* mModel;

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
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,1.0,0.0));
    model = glm::scale(model,glm::vec3(0.15,0.15,0.15));
    model = glm::translate(model,glm::vec3(0.0,-8.0,0.0));
    ShaderUtil::setMatrix(programId,"model",model);
    // glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1,GL_FALSE,glm::value_ptr(model)); 


    // 设置光源属性 点光源
    ShaderUtil::setUniform3f(programId, "light.ambient", 0.2f, 0.2f, 0.2f);
    ShaderUtil::setUniform3f(programId, "light.diffuse", 0.5f, 0.5f, 0.5f);
    ShaderUtil::setUniform3f(programId, "light.specular", 1.0f, 1.0f, 1.0f);
    // 设置衰减系数
    ShaderUtil::setUniform1f(programId, "light.constant", 1.0f);
    ShaderUtil::setUniform1f(programId, "light.linear", 0.09f);
    ShaderUtil::setUniform1f(programId, "light.quadratic", 0.032f);

    // glUniform3f(glGetUniformLocation(programId, "lightPos"), 1.2f, 1.0f, 2.0f);
    ShaderUtil::setUniform3f(programId, "viewPos",0.0,10.0,30.0);
    // glUniform3f(glGetUniformLocation(programId, "lightColor"),1.0,1.0,1.0);
}

void CustomModel::draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);
    glm::vec3 lampPos(0.5f * sinf(glfwGetTime()), 1.0f * sinf(glfwGetTime()), 1.5f);
    ShaderUtil::setUniform3f(programId, "light.position", lampPos.x, lampPos.y, lampPos.z);

    mModel->Draw(programId);
}

void CustomModel::destroy(){

}
#include <myGL/InstanceScene.h>
#include <model/Model.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>
#include <myGL/ShaderUtil.h>

Model* mPlanetModel;
Model* mRockModel;
const int rockCount = 10000;
float radius = 50;
float rockScaleFactor = 0.5f;
float planetScaleFactor = 8.0f;
glm::mat4 rockModel[rockCount];
unsigned int mRockProgramId;

void initRock();

void InstanceScene::init(){
    mRockProgramId = ShaderUtil::createProgram("./shader/rock_vertex.glsl", "./shader/planet_fragment.glsl");
    mPlanetModel = new Model("resource/model/planet/planet.obj");

    glEnable(GL_DEPTH_TEST);
    glUseProgram(programId);
    
    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0,0.0,100.0)
            ,glm::vec3(0.0,0.0,-1.0)
            ,glm::vec3(0.0,1.0,0.0)
        );
    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1,GL_FALSE,glm::value_ptr(view));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),1.33f,0.1f,100.0f); 
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1,GL_FALSE,glm::value_ptr(projection));
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,1.0,0.0));
    model = glm::scale(model,glm::vec3(planetScaleFactor,planetScaleFactor,planetScaleFactor));
    model = glm::translate(model,glm::vec3(0.0,0.0,0.0));
    ShaderUtil::setMatrix(programId,"model",model);

    // 设置光源属性 点光源
    ShaderUtil::setUniform3f(programId, "light.ambient", 0.2f, 0.2f, 0.2f);
    ShaderUtil::setUniform3f(programId, "light.diffuse", 0.5f, 0.5f, 0.5f);
    ShaderUtil::setUniform3f(programId, "light.specular", 1.0f, 1.0f, 1.0f);
    // 设置衰减系数
    ShaderUtil::setUniform1f(programId, "light.constant", 1.0f);
    ShaderUtil::setUniform1f(programId, "light.linear", 0.09f);
    ShaderUtil::setUniform1f(programId, "light.quadratic", 0.032f);

    ShaderUtil::setUniform3f(programId, "viewPos",0.0,0.0,100.0);
    glm::vec3 lampPos(5.0f, 1.0f , 5.0f);
    ShaderUtil::setUniform3f(programId, "light.position", lampPos.x, lampPos.y, lampPos.z);

    glUseProgram(mRockProgramId);
    glUniformMatrix4fv(glGetUniformLocation(mRockProgramId, "view"), 1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(mRockProgramId, "projection"), 1,GL_FALSE,glm::value_ptr(projection));

    initRock();
}

void initRock(){
    mRockModel = new Model("resource/model/rock/rock.obj");

    srand(glfwGetTime());
    float offset = 2.5f;
    
    float dy = 0;
    float randOffset = 0.0f;
    for (int i = 0; i < rockCount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        float angle = (float)i/(float) rockCount * 360.0f;
        randOffset = (rand() % ((int)offset * 2 * 100))/100.0f - offset;
        float x = sin(angle) * radius + randOffset;
        randOffset = (rand() % ((int)offset * 2 * 100))/100.0f - offset;
        float z = cos(angle) * radius + randOffset;
        randOffset = (rand() % ((int)offset * 2 * 100))/100.0f - offset;
        float y = 1.0f + randOffset;
        // std::cout << "rand" << rand() << std::endl;
        // std::cout << "----------------------" << std::endl;
        model = glm::translate(model,glm::vec3(x,y,z));
        float scale = (rand() % 20)/ 100.0f + rockScaleFactor;
        model = glm::scale(model,glm::vec3(scale,scale,scale));
        float rockAngle = (float)(rand() % 360);
        model = glm::rotate(model,glm::radians(rockAngle),glm::vec3(0.6f,0.2f,0.8f));
        rockModel[i] = model;
    }
    
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,rockCount * sizeof(glm::mat4),&rockModel[0],GL_STATIC_DRAW);

    for (int i = 0; i < mRockModel->meshes.size(); i++)
    {
        glBindVertexArray(mRockModel->meshes[i].VAO);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3,1);
        glVertexAttribDivisor(4,1);
        glVertexAttribDivisor(5,1);
        glVertexAttribDivisor(6,1);
        glBindVertexArray(0);
    }
    
}

void InstanceScene::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);
    // glm::mat4 model = glm::mat4(1.0f);
    // // model = glm::rotate(model,glm::radians(45.0f) * (float)glfwGetTime(),glm::vec3(0.0,1.0,0.0));
    // model = glm::scale(model,glm::vec3(planetScaleFactor,planetScaleFactor,planetScaleFactor));
    // model = glm::translate(model,glm::vec3(0.0,0.0,0.0));
    // ShaderUtil::setMatrix(programId,"model",model);
    mPlanetModel->Draw(programId);

    glUseProgram(mRockProgramId);
    for (int i = 0; i < mRockModel->meshes.size(); i++)
    {
        // ShaderUtil::setMatrix(programId,"model",rockModel[i]);
        // mRockModel->Draw(programId);
        glBindVertexArray(mRockModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES,mRockModel->meshes[i].indices.size(),GL_UNSIGNED_INT,0,rockCount);
        glBindVertexArray(0);
    }
    
    
}

void InstanceScene::destroy(){

}

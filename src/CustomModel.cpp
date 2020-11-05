#include <myGL/CustomModel.h>
#include <model/Model.h>
#include <iostream>

Model mModel("F:\\CProject\\OpenGLPractice\\resource\\model\\nanosuit\\nanosuit.obj");

void CustomModel::init(){
    // mModel = new Model("./resource/model/nanosuit/nanosuit.obj");
}

void CustomModel::draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);

    mModel.Draw(programId);
}

void CustomModel::destroy(){

}
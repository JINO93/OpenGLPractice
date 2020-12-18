#include <myGL/Shape.h>
#include <myGL/ShaderUtil.h>

using namespace std;

Shape::Shape(const char *vertexPath,const char *fragmentPath){
    // // 1. 从文件路径中获取顶点/片段着色器
    // std::string vertexCode;
    // std::string fragmentCode;
    // std::ifstream vShaderFile;
    // std::ifstream fShaderFile;
    // // 保证ifstream对象可以抛出异常：
    // vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    // fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    // try 
    // {
    //     // 打开文件
    //     std::stringstream vShaderStream, fShaderStream;
    //     vShaderFile.open(vertexPath,ios::in);
    //     fShaderFile.open(fragmentPath,ios::in);

    //     // 读取文件的缓冲内容到数据流中
    //     vShaderStream << vShaderFile.rdbuf();
    //     fShaderStream << fShaderFile.rdbuf();     

    //     // 关闭文件处理器
    //     vShaderFile.close();
    //     fShaderFile.close();

    //     // 转换数据流到string
    //     vertexCode   = vShaderStream.str();
    //     fragmentCode = fShaderStream.str();     
    //     const char* vShaderCode = vertexCode.c_str();
    //     const char* fShaderCode = fragmentCode.c_str();
    //     // std::cout << "vCode:" << vShaderCode << endl;
    //     // std::cout << "fCode:" << fShaderCode << endl;
    // }
    // catch(std::ifstream::failure e)
    // {
    //     std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :" << e.what() <<std::endl;
    // }
    programId = ShaderUtil::createProgram(vertexPath,fragmentPath);
}

void Shape::destroy(){
    ShaderUtil::deleteProgram(programId);
}

void Shape::init(){

}

void Shape::draw(){
    
}
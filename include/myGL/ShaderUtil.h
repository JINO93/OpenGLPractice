#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class ShaderUtil
{
  public:
    static int createShader(const char *path, int type)
    {
        // cout << "createShader :" << type << endl; 
        int shader = glCreateShader(type);
        string resStr = readShaderFromFile(path);
        // std::cout << "shaderSource:" << resStr << endl;
        const char* shaderSource = resStr.c_str();
        // std::cout << "shaderSource:" << shaderSource << endl;
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        int res;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
        if (!res)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            cout << "craete shader " << type << " failed, source:" << shaderSource << " error:" << infoLog << endl;
            return 0;
        }
        return shader;
    }

    static string readShaderFromFile(const char *shaderPath){
        cout << "read shader from path:" << shaderPath << endl;
        // 1. 从文件路径中获取顶点/片段着色器
        std::string shaderCode;
        std::ifstream shaderFile;
        // 保证ifstream对象可以抛出异常：
        shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // 打开文件
            std::stringstream shaderStream;
            shaderFile.open(shaderPath,ios::in);

            // 读取文件的缓冲内容到数据流中
            shaderStream << shaderFile.rdbuf();

            // 关闭文件处理器
            shaderFile.close();

            // 转换数据流到string
            shaderCode   = shaderStream.str();
            // result = shaderCode.c_str();
            // std::cout << "res:" << result << endl;
            return shaderCode;
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :" << e.what() <<std::endl;
        }
    }

    static int createProgram(const char *vetShaderPath, const char *fragShaderPath)
    {
        int vShader = createShader(vetShaderPath, GL_VERTEX_SHADER);
        if (!vShader){
            cout << "create vertex shader failed, shader source:" << vetShaderPath << endl;
            return 0;
        }
        int fShader = createShader(fragShaderPath, GL_FRAGMENT_SHADER);
        if (!fShader){
            cout << "create fragment shader failed, shader source:" << fragShaderPath << endl;
            return 0;
        }
        int program = glCreateProgram();
        glAttachShader(program, vShader);
        glAttachShader(program, fShader);
        glLinkProgram(program);
        int res;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &res);
        if (!res)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            cout << "craete program failed error:" << infoLog << endl;
            return 0;
        }
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        return program;
    }

    static void deleteProgram(int programId)
    {
        if (programId)
        {
            glDeleteProgram(programId);
            // programId = 0;
        }
    }

    static int createTexture(const char *path,bool withAlpha = false)
    {
        unsigned int textureId;
        glGenTextures(1, &textureId);
        // glActiveTexture(textureLocation);
        glBindTexture(GL_TEXTURE_2D, textureId);
        //设置纹理对象的环绕、采样方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        int width, height, channel;
        unsigned char *data = stbi_load(path, &width, &height, &channel, 0);
        if (data)
        {
            if(withAlpha){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }else{

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "load img failed" << std::endl;
            // glDeleteTextures
            textureId = 0;
        }
        stbi_image_free(data);
        return textureId;
    }

    static void setUniform1i(int programId,const char* name,int v1){
        glUniform1i(glGetUniformLocation(programId,name),v1);
    }

    static void setUniform1f(int programId,const char* name,float v1){
        glUniform1f(glGetUniformLocation(programId,name),v1);
    }

    static void setUniform2f(int programId,const char* name,glm::vec2 value){
        glUniform2fv(glGetUniformLocation(programId,name),1,&value[0]);
    }

    static void setUniform2f(int programId,const char* name,float v1,float v2){
        glUniform2f(glGetUniformLocation(programId,name),v1,v2);
    }

    static void setUniform3f(int programId,const char* name,glm::vec3 value){
        glUniform3fv(glGetUniformLocation(programId,name),1,&value[0]);
    }

    static void setUniform3f(int programId,const char* name,float v1,float v2,float v3){
        glUniform3f(glGetUniformLocation(programId,name),v1,v2,v3);
    }

    static void setUniform4f(int programId,const char* name,glm::vec4 value){
        glUniform4fv(glGetUniformLocation(programId,name),1,&value[0]);
    }

    static void setUniform4f(int programId,const char* name,float v1,float v2,float v3,float v4){
        glUniform4f(glGetUniformLocation(programId,name),v1,v2,v3,v4);
    }

    static void setMatrix(int programId,const char* name,glm::mat4 value){
        glUniformMatrix4fv(glGetUniformLocation(programId,name),1,GL_FALSE,glm::value_ptr(value));
    }
};

#endif
#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

using namespace std;

class ShaderUtil
{
  public:
    static int createShader(const char *source, int type)
    {
        int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        int res;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
        if (!res)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            cout << "craete shader " << type << " failed error:" << infoLog << endl;
            return 0;
        }
        return shader;
    }

    static int createProgram(const char *vetShaderSource, const char *fragShaderSource)
    {
        int vShader = createShader(vetShaderSource, GL_VERTEX_SHADER);
        if (!vShader)
            return 0;
        int fShader = createShader(fragShaderSource, GL_FRAGMENT_SHADER);
        if (!fShader)
            return 0;

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

    static int createTexture(const char *path)
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
        int width, height, channel;
        unsigned char *data = stbi_load(path, &width, &height, &channel, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
};

#endif
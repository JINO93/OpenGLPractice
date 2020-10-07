#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <glad/glad.h>
#include <iostream>
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

    static void deleteProgram(int programId){
        if(programId){
            glDeleteProgram(programId);
            // programId = 0;
        }
    }
};

#endif
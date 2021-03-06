#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texPos;

uniform mat4 transformM;

out vec2 outTexPos;
void main(){
    gl_Position = transformM * vec4(aPos.x,aPos.y,aPos.z,1.0);
    outTexPos = texPos;
}
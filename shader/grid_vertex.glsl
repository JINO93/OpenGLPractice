#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texPos;

uniform float u_time;

out vec2 outTexPos;

void main(){
    float maxScale = 0.7;
    float dur = 0.5;
    float time = mod(u_time,dur);
    float s = 1 + maxScale * abs(sin(time * 3.14/dur));
    s = 1.0;
    gl_Position = vec4(aPos.x * s,aPos.y * s,aPos.z,1.0);
    outTexPos = texPos;
}
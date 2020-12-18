#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normalPos;
layout(location = 2) in vec2 texPos;
layout(location = 3) in mat4 instanceModel;

uniform mat4 view;
uniform mat4 projection;

out vec2 outTexPos;
out vec3 outNormalPos;
out vec3 outFragPos;
void main(){
    gl_Position = projection * view * instanceModel * vec4(aPos.x,aPos.y,aPos.z,1.0);
    outTexPos = texPos;
    outNormalPos = normalPos;
    outFragPos = (instanceModel * vec4(aPos,1.0)).xyz;
}
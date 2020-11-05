#version 330 core

in vec2 outTexPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D outTexture2;

out vec4 gl_FragColor;
void main(){
    gl_FragColor = texture(texture_diffuse1,outTexPos);
}
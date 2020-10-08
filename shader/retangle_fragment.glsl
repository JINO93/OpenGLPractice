#version 330 core

in vec2 outTexPos;

uniform sampler2D outTexture;
uniform sampler2D outTexture2;

out vec4 gl_FragColor;
void main(){
    gl_FragColor = mix(texture(outTexture,outTexPos),texture(outTexture2,outTexPos),0.2);
}
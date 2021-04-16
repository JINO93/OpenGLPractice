#version 330 core

uniform vec2 screenSize;

out vec4 gl_FragColor;
void main(){
    float lineWidth = 0.05;
    vec2 p = gl_FragCoord.xy/screenSize;
    p *= 10;
    vec2 fP = fract(p);
    // float curX = p.x - (1.0-lineWidth)/2;
    float color = 0.0;
    color = step(1-lineWidth,fP.x) * 0.5 + step(1-lineWidth,fP.y) * 0.5;
    gl_FragColor = vec4(color,color,color,1.0);
}
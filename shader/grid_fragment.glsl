#version 330 core
precision highp float;
uniform vec2 screenSize;
uniform float u_time;

out vec4 gl_FragColor;

void drawGrid(){
    float lineWidth = 0.05;
    vec2 p = gl_FragCoord.xy/screenSize;
    p.x *= screenSize.x/screenSize.y;
    p *= 10;
    vec2 fP = fract(p);
    // float curX = p.x - (1.0-lineWidth)/2;
    float color = 0.0;
    color = step(1-lineWidth,fP.x) * 0.5 + step(1-lineWidth,fP.y) * 0.5;
    gl_FragColor = vec4(color,color,color,1.0);
}

void drawCircle(){
    float rotateAngle = 60.0;
    // 将坐标归一化
    vec2 p = gl_FragCoord.xy/screenSize;
    // 根据屏幕宽高比调整坐标
    p.x *= screenSize.x/screenSize.y;
    // p += .5;
    float radium = 0.2;
    float color = 0.0;
    // 得到从圆心到当前像素点的向量
    vec2 dr = p-vec2(0.5,0.5);
    // 根据向量计算出与圆心的夹角
    float angle = atan(dr.y,dr.x);
    int n = 6;
    int roateSpeed = 100;
    int pieceAngle = 360/n;
    // 得出当前向量的长度
    float curR = length(dr);
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    if(radium > curR){
        float curAngle = degrees(angle);
        
        // 随着时间自动旋转
        curAngle = mod(curAngle  + mod(u_time,360) * roateSpeed,360);
        // 根据像素点的半径算出偏移角度
        float offset = rotateAngle * curR/radium;
        curAngle -= offset;
        // 将负角度转换为正（因为OpenGL种的角度范围是[-180,180]）
        if(curAngle < 0){
            curAngle = curAngle + 360;
        }

        // 根据角度算出所在扇区
        float blockIdx = floor((curAngle)/pieceAngle);
        r = max(1-blockIdx*pieceAngle/180.0,0.0);
        g = sin(blockIdx*pieceAngle/2.0);
        b = max(blockIdx*pieceAngle/180.0 - 1,0);
    }
    gl_FragColor = vec4(r,g,b,1.0);
}

void main(){
    // drawGrid();
    drawCircle();
}


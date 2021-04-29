#version 330 core
precision highp float;
uniform vec2 screenSize;
uniform float u_time;
uniform sampler2D texture0;

in vec2 outTexPos;

out vec4 gl_FragColor;

void drawGrid(){
    float lineWidth = 0.05;
    vec2 p = gl_FragCoord.xy/screenSize;
    p.x *= screenSize.x/screenSize.y;
    p *= 10.0;
    vec2 fP = fract(p);
    // float curX = p.x - (1.0-lineWidth)/2;
    float color = 0.0;
    color = step(1.0-lineWidth,fP.x) * 0.5 + step(1.0-lineWidth,fP.y) * 0.5;
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
        curAngle = mod(curAngle  + mod(u_time,360.0) * float(roateSpeed),360.0);
        // 根据像素点的半径算出偏移角度
        float offset = rotateAngle * curR/radium;
        curAngle -= offset;
        // 将负角度转换为正（因为OpenGL种的角度范围是[-180,180]）
        if(curAngle < 0.0){
            curAngle = curAngle + 360.0;
        }

        // 根据角度算出所在扇区
        float blockIdx = floor(curAngle/float(pieceAngle));
        r = max(1.0-blockIdx*float(pieceAngle)/180.0,0.0);
        g = sin(blockIdx*float(pieceAngle)/2.0);
        b = max(blockIdx*float(pieceAngle)/180.0 - 1.0,0.0);
    }
    gl_FragColor = vec4(r,g,b,1.0);
}

void scaleOut(){
    float maxScale = 0.5;
    float dur = 0.5;
    float time = mod(u_time,dur);
    float scale = 1.0 + maxScale * sin(time/dur);//缩放范围[1,1.5]
    vec2 scaleTexPos = 0.5 + (outTexPos - 0.5) / scale; // 范围从[0,1]变化到[0.5 + (-0.5/1.5),0.5 + (0.5/1.5)]
    gl_FragColor = texture(texture0,scaleTexPos);
}

void soulFadeOut(){
    float maxScale = 0.5;
    float dur = 0.5;
    float maxAlpha = 0.3;

    float time = mod(u_time,dur);
    float scale = 1.0 + maxScale * sin(time/dur);
    float alpha = maxAlpha - maxAlpha * sin(time/dur);

    vec2 scaleTexPos = 0.5 + (outTexPos - 0.5) / scale; 
    // 得到淡出层的颜色
    vec4 fakeLayerColor = texture(texture0,scaleTexPos);
    vec4 resColor = texture(texture0,outTexPos);
    // 将源图层跟淡出层的颜色根据alpha比例相加得出最终颜色
    gl_FragColor = (1.0-alpha)*resColor + alpha*fakeLayerColor;
}

void mosica(){
    // 将位图分为指定份数
    float totalSize = 400.0;
    // 定义格子所占的份数
    float gridSize = 10.0;
    vec2 xy = outTexPos * totalSize;
    // 根据格子的大小，在同一个格子里返回相同的坐标（如[0,10]的区间都去同一个位置去采样）
    vec2 mosicaPos = vec2(floor(xy.x/gridSize) * gridSize, floor(xy.y/gridSize) * gridSize);
    gl_FragColor = texture(texture0,mosicaPos/totalSize);
}

void main(){
     drawGrid();
//     drawCircle();
    // scaleOut();
    // soulFadeOut();
//    mosica();
}


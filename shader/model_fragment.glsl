#version 330 core

in vec2 outTexPos;
in vec3 outNormalPos;
in vec3 outFragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

out vec4 gl_FragColor;
void main(){
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(outNormalPos);
    vec3 lightDir = normalize(lightPos - outFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 textureColor = texture(texture_diffuse1,outTexPos);
    vec3 res = (ambient + diffuse + specular) * textureColor.xyz;
    gl_FragColor = vec4(res,textureColor.w);
}
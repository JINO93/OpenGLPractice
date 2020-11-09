#version 330 core

in vec2 outTexPos;
in vec3 outNormalPos;
in vec3 outFragPos;

// 光源属性结构体
struct LightAttr
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;	// 衰减常数
	float linear;   // 衰减一次系数
	float quadratic; // 衰减二次系数
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;

uniform LightAttr light;
// uniform vec3 lightPos; 
uniform vec3 viewPos; 
// uniform vec3 lightColor;

out vec4 gl_FragColor;
void main(){
    vec3 texDiff= texture(texture_diffuse1,outTexPos).xyz;
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = light.ambient * texDiff;
  	
    // diffuse 
    vec3 norm = normalize(outNormalPos);
    vec3 lightDir = normalize(light.position - outFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texDiff;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1,outTexPos));

    // 计算衰减因子
	float distance = length(light.position - outFragPos); // 在世界坐标系中计算距离
	float attenuation = 1.0f / (light.constant 
			+ light.linear * distance
			+ light.quadratic * distance * distance);

    // vec4 textureColor = texture(texture_diffuse2,outTexPos);
    vec3 res = (ambient + diffuse + specular) * attenuation;
    gl_FragColor = vec4(res,1.0);
}
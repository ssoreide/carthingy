#version 330 core
out vec4 FragColor;
  
in vec3 FragPos;
in vec3 Normal; 

uniform vec3 lightPos;  

void main()
{
// Ambient part
    float ambientStrength = 0.1;
	vec3 lightColor = vec3(1, 1, 1);
    vec3 ambient = ambientStrength * lightColor;
//	FragColor = vec4(0.2,0.5,1,1.0);
// Diffuse part
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

// Summing it up
	vec3 objectColor = vec3(0.2,0.8,1);
	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}
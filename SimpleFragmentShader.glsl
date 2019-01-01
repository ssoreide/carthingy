#version 330 core
out vec4 FragColor;
  
in vec3 FragPos;
in vec3 Normal; 
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform int useTexture = 0;
uniform vec3 objectColor = vec3(1, 1, 1);

void main()
{
// Ambient part
    float ambientStrength = 0.5;
	vec3 lightColor = vec3(1, 1, 1);
    vec3 ambient = ambientStrength * lightColor;

// Diffuse part
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

// Summing it up
	vec4 color = useTexture * texture(ourTexture, TexCoord) + vec4((1-useTexture) * objectColor, 1.0);
	FragColor = vec4(ambient + diffuse, 1.0) * color;
}
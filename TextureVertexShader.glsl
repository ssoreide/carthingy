#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 lightColor;

uniform mat4 MVP;
uniform vec3 cameraPos;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
	vec3 carLightDir = aPos - cameraPos;
	float dist = sqrt(dot(carLightDir, carLightDir));
	lightColor = (vec3(1.0, 1.0, 1.0) * dot(carLightDir, vec3(0.0, 1.0, 0.0))) / dist;
    TexCoord = aTexCoord;
}
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;  
out vec2 TexCoord;
out vec3 Normal;

//vrir det i perspektiv, og plasserer det i det lokale skjermkortet (-1 til +1)
uniform mat4 projection;
// view = invers av camera position and rotación
uniform mat4 view;
// transformasjon til selve objektet
uniform mat4 model;

void main()
{
	// gl_postion er hardkodet output navn til vertexshaderen
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	// fragPos er verdenskoordintater
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoord = aTexCoord;
}
#version 330 core

layout(location = 0) in vec4 a_Position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragPos;  
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * a_Position;
	FragPos = vec3(u_Model * a_Position);
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;
	TexCoord = a_TexCoord;
}
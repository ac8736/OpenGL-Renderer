#version 330 core

layout(location = 0) in vec4 a_Position;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = a_Position;
}
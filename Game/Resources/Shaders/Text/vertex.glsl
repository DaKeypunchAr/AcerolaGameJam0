#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;
out vec4 color;

void main()
{
	gl_Position = vec4(aPos, 1.0, 1.0);
	texCoords = aTexCoords;
	color = aColor;
}
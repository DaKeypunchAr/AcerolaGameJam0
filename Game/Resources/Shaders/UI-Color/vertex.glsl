#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;

uniform mat4 projMatrix;

void main()
{
	gl_Position = projMatrix * vec4(aPos, 1.0, 1.0);
	color = aColor;
}
#version 450 core

in vec2 texCoords;
in vec4 color;

uniform sampler2D tex;

out vec4 fragColor;

void main()
{
	fragColor = color * vec4(1.0, 1.0, 1.0, texture(tex, texCoords).r);
}
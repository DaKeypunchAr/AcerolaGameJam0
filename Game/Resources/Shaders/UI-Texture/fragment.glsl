#version 450 core

out vec4 fragColor;

uniform sampler2D tex;

in vec2 texCoords;

void main()
{
	fragColor = texture(tex, texCoords);
}
#type vertex
#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 projectionView;
uniform mat4 transform;

void main()
{
	gl_Position = projectionView * transform * vec4(position, 1.0);
}

#type fragment
#version 460 core

out vec4 outColor;

uniform vec3 color;

void main()
{
	outColor = vec4(color, 1.0);
}

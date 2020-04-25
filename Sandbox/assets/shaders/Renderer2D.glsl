#type vertex
#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 _texCoord;

uniform mat4 projectionView;
uniform mat4 transform;

void main()
{
	gl_Position = projectionView * transform * vec4(position, 1.0);
	_texCoord = texCoord;
}

#type fragment
#version 460 core

in vec2 _texCoord;

out vec4 outColor;

uniform sampler2D tex;
uniform float tilingFactor;
uniform vec4 color;

void main()
{
	outColor = texture(tex, _texCoord * tilingFactor) * color;
}

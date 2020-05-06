#type vertex
#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texIndex;

out vec2 _texCoord;
out vec4 _color;
out float _texIndex;

uniform mat4 projectionView;
uniform mat4 transform;

void main()
{
	gl_Position = projectionView /* * transform */ * vec4(position, 1.0);
	_texCoord = texCoord;
	_color = color;
	_texIndex = texIndex;
}

#type fragment
#version 460 core

in vec2 _texCoord;
in vec4 _color;
in float _texIndex;

out vec4 outColor;

uniform sampler2D textures[32];

void main()
{
	outColor = texture(textures[int(_texIndex)], _texCoord) * _color;
}

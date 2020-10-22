#type vertex
#version 450 core

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
#version 450 core

in vec2 _texCoord;
in vec4 _color;
in float _texIndex;

out vec4 outColor;

uniform sampler2D textures[32];

void main()
{
	switch (int(_texIndex))
	{
		case  0: outColor = texture(textures[ 0], _texCoord) * _color; break;
		case  1: outColor = texture(textures[ 1], _texCoord) * _color; break;
		case  2: outColor = texture(textures[ 2], _texCoord) * _color; break;
		case  3: outColor = texture(textures[ 3], _texCoord) * _color; break;
		case  4: outColor = texture(textures[ 4], _texCoord) * _color; break;
		case  5: outColor = texture(textures[ 5], _texCoord) * _color; break;
		case  6: outColor = texture(textures[ 6], _texCoord) * _color; break;
		case  7: outColor = texture(textures[ 7], _texCoord) * _color; break;
		case  8: outColor = texture(textures[ 8], _texCoord) * _color; break;
		case  9: outColor = texture(textures[ 9], _texCoord) * _color; break;
		case 10: outColor = texture(textures[10], _texCoord) * _color; break;
		case 11: outColor = texture(textures[11], _texCoord) * _color; break;
		case 12: outColor = texture(textures[12], _texCoord) * _color; break;
		case 13: outColor = texture(textures[13], _texCoord) * _color; break;
		case 14: outColor = texture(textures[14], _texCoord) * _color; break;
		case 15: outColor = texture(textures[15], _texCoord) * _color; break;
		case 16: outColor = texture(textures[16], _texCoord) * _color; break;
		case 17: outColor = texture(textures[17], _texCoord) * _color; break;
		case 18: outColor = texture(textures[18], _texCoord) * _color; break;
		case 19: outColor = texture(textures[19], _texCoord) * _color; break;
		case 20: outColor = texture(textures[20], _texCoord) * _color; break;
		case 21: outColor = texture(textures[21], _texCoord) * _color; break;
		case 22: outColor = texture(textures[22], _texCoord) * _color; break;
		case 23: outColor = texture(textures[23], _texCoord) * _color; break;
		case 24: outColor = texture(textures[24], _texCoord) * _color; break;
		case 25: outColor = texture(textures[25], _texCoord) * _color; break;
		case 26: outColor = texture(textures[26], _texCoord) * _color; break;
		case 27: outColor = texture(textures[27], _texCoord) * _color; break;
		case 28: outColor = texture(textures[28], _texCoord) * _color; break;
		case 29: outColor = texture(textures[29], _texCoord) * _color; break;
		case 30: outColor = texture(textures[30], _texCoord) * _color; break;
		case 31: outColor = texture(textures[31], _texCoord) * _color; break;
	}
}

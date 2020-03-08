#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, TexCoord) * vec4(ourColor,1);
}
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float fillAmount;

void main()
{
    if(TexCoords.x > fillAmount)
    discard;

    vec4 tex = texture(image, TexCoords);
    color = vec4(tex.rgb, tex.a);
}
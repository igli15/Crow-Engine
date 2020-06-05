#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform sampler2D noise;

uniform vec3 filledColor;
uniform vec3 emptyColor;
uniform float time;
uniform float fillAmount;

void main()
{
    vec4 tex = texture(image, TexCoords);

    vec2 noiseUVs = TexCoords;

    noiseUVs.y /= 3;
    noiseUVs.x += time/10 * (1-tex.r);
    float noiseValue = texture(noise,noiseUVs).r;

    if(TexCoords.x < fillAmount - noiseValue/10)
    {
         color = vec4(vec3(1)- tex.rgb, tex.a) * vec4(filledColor,1);
         color += vec4(emptyColor/2 * step(0.5,noiseValue),1);
    }
    else
    {
        color = vec4(vec3(1)- tex.rgb, tex.a) * vec4(emptyColor,1);
    }

}
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const int indexMatrix4x4[16] = int[](0,  8,  2,  10,
                                     12, 4,  14, 6,
                                     3,  11, 1,  9,
                                     15, 7,  13, 5);

float indexValue() {
    int x = int(mod(gl_FragCoord.x, 4));
    int y = int(mod(gl_FragCoord.y, 4));
    //return indexMatrix4x4[(x + y * 4)] / 16.0;
    return indexMatrix4x4[(x + y * 4)] / 64.0;
}

float dither(float color) {
    float closestColor = (color < 0.5) ? 0 : 1;
    float secondClosestColor = 1 - closestColor;
    float d = indexValue();
    float distance = abs(closestColor - color);
    return (distance < d) ? closestColor : secondClosestColor;
}

const float exposure = 0.8;

void main()
{

    vec3 outColor = texture(screenTexture, TexCoords).rgb;

    // reinhard tone mapping
    vec3 mapped = vec3(1.0) - exp(-outColor * exposure);

    //FragColor = vec4(mapped, 1.0);
    FragColor = vec4(outColor, 1.0);
    //FragColor = vec4(vec3(outColor) * dither(outColor.r), 1);
}
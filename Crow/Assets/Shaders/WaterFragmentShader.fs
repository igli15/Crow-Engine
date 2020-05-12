#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform float time;
uniform vec3 mainColor;
uniform sampler2D waveNoiseTex;
uniform sampler2D depthTex;
uniform sampler2D foamGradientTex;
uniform sampler2D causticsTex;

void main()
{
    vec3 norm = normalize(Normal);

    //vec4 result = (mainColor,1);
    vec2 noiseUvs = TexCoords;
    noiseUvs.x *= 2;
    noiseUvs.y *= 4;

    vec2 foamUvs = TexCoords;



    vec2 causticsUvs = TexCoords;
    causticsUvs.x *= 2;
    causticsUvs.y *= 3;

    causticsUvs -= vec2(time * 0.03);

    vec3 caustics = texture(causticsTex, causticsUvs).rgb;

    noiseUvs -= vec2(0,time * 0.05);
    float waveNoise = texture(waveNoiseTex, noiseUvs).r;

    float depthValue = texture(depthTex, TexCoords).r;

    float waveFoamValue = texture(foamGradientTex, foamUvs).r ;
    vec3 foamColor = vec3(0.3);

    float foamDepthDifference01 = clamp(0.07/waveFoamValue, 0.0, 1.0);
    float surfaceNoiseCutoff = foamDepthDifference01 * 0.8;

    vec3 surfaceNoise = (waveNoise > surfaceNoiseCutoff ? 1 : 0) * foamColor;


    FragColor = vec4(mainColor * depthValue,1.0) + vec4(surfaceNoise,1.0) + (vec4(caustics,1) * 0.2 * depthValue);
     //FragColor = vec4(depthValue,depthValue,depthValue,1);
}

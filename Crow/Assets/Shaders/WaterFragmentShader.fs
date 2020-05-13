#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform float time;

uniform float noiseScale;
uniform float distanceScale;
uniform float causticSpeed;
uniform float noiseSpeed;

uniform vec3 mainColor;
uniform vec3 foamColor;

uniform sampler2D waveNoiseTex;
uniform sampler2D depthTex;
uniform sampler2D foamGradientTex;
uniform sampler2D causticsTex;

void main()
{
    vec3 norm = normalize(Normal);

    vec2 noiseUvs = TexCoords;
    noiseUvs.x *= 2;
    noiseUvs.y *= 4;

    vec2 foamUvs = TexCoords;

    vec2 causticsUvs = TexCoords;
    causticsUvs.x *= 2;
    causticsUvs.y *= 5;

    causticsUvs -= vec2(time * causticSpeed);

    vec3 caustics = texture(causticsTex, causticsUvs).rgb;

    noiseUvs -= vec2(0,time * noiseSpeed);
    float waveNoise = texture(waveNoiseTex, noiseUvs).r;

    float depthValue = texture(depthTex, TexCoords).r;

    float waveFoamValue = texture(foamGradientTex, foamUvs).r ;

    float foamDepthDifference01 = clamp(distanceScale/waveFoamValue, 0.0, 1.0);
    float surfaceNoiseCutoff = foamDepthDifference01 * noiseScale;

    vec3 surfaceNoise = (waveNoise > surfaceNoiseCutoff ? 1 : 0) * foamColor;

    FragColor = vec4(mainColor * depthValue,1.0) + vec4(surfaceNoise,1.0) + (vec4(caustics,1) * 0.1 * depthValue);

}
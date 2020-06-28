#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

uniform float time;
uniform vec3 mainColor;
uniform vec3 secondColor;

uniform sampler2D noiseTex;
uniform sampler2D rotationMask;
uniform sampler2D portalGlowMask;

uniform float rotationSpeed;
uniform float scaleSpeed;
uniform float swirlAmount;

vec4 pivot = vec4(0.5,0.5,1,1);

uniform float fogDensity;
uniform float fogGradient;
uniform vec3 fogColor;

vec2 rotate( float magnitude , vec2 p )
 {
   float sinTheta = sin(magnitude);
   float cosTheta = cos(magnitude);
   mat2 rotationMatrix = mat2(cosTheta, -sinTheta, sinTheta, cosTheta);
   return p* rotationMatrix;
 }

void main()
{
    vec3 norm = normalize(Normal);

    float distance = length(viewPos - FragPos);
    float visibility = exp(-pow(distance * fogDensity,fogGradient));
    clamp(visibility,0.0,1.0);

    vec3 glow = texture(portalGlowMask,TexCoords).rgb;
    float rotationMaskValue = texture(rotationMask, TexCoords).r;

    vec2 p = TexCoords - pivot.xy;

    //p = rotate((rotationMaskValue * time/10), p);
    //p = rotate(time/10 * speed, p);

    float angle = atan(p.y,p.x) * 0.5;

    float r = sqrt(dot(p,p));

    vec2 uvs;

    uvs.x = (time/10 * scaleSpeed) - 1/(r + swirlAmount);

    uvs.y = pivot.z *angle/3.1416;
    uvs.y += time/10 * rotationSpeed;

    vec3 noise = texture(noiseTex, uvs).rgb;

    vec3 finalColor = mainColor;

    finalColor += secondColor * step(0.5,noise.r);


    FragColor = vec4(finalColor + glow * 1.4,1.0) ;
    FragColor = mix(vec4(fogColor.rgb,1),FragColor,visibility);

}

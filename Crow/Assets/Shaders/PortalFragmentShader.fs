#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform float time;
uniform vec3 mainColor;
uniform vec3 secondColor;

uniform sampler2D noiseTex;
uniform sampler2D rotationMask;
uniform sampler2D portalGlowMask;

vec4 pivot = vec4(0.5,0.5,1,1);
float speed = 5;
float swirl = 0.8;
float rotation = 5;

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

    vec3 glow = texture(portalGlowMask,TexCoords).rgb;
    float rotationMaskValue = texture(rotationMask, TexCoords).r;

    vec2 p = TexCoords - pivot.xy;

    p = rotate((rotationMaskValue * time/10), p);
    p = rotate(rotation * time/10 * speed, p);

    float angle = atan(p.y,p.x) * 0.5;

    float r = sqrt(dot(p,p));

    vec2 uvs;

    uvs.x = (time/10 * speed) - 1/(r + swirl);
    uvs.y = pivot.z *angle/3.1416;

    vec3 noise = texture(noiseTex, uvs).rgb;

    vec3 finalColor = mix(mainColor,secondColor,noise.r);
    finalColor = smoothstep(0.3,1,finalColor);

    FragColor = vec4(finalColor,1.0) ;

}

#version 330

in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 resolution;
uniform vec2 mousepos;
uniform float time;

vec3 palette(float t)
{
  vec3 a = vec3(0.988, 0.500, 0.500);
  vec3 b = vec3(-0.942, 0.500, 0.500);
  vec3 c = vec3(-0.722, 1.000, 0.878); 
  vec3 d = vec3(0.000, 0.333, 0.667);
  return a + b*cos( 6.28318*(c*t+d) );
}

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                     vec2(12.9898,78.233)))*
        43758.5453123);
}

vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*43758.5453123);
}

// Gradient Noise by Inigo Quilez - iq/2013
// https://www.shadertoy.com/view/XdXGW8
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

void main()
{
  vec2 uv = fragTexCoord * 2.0 - 1.0; 
  vec2 origuv = fragTexCoord * 2.0 - 1.0; 

  uv.x *= resolution.x / resolution.y;
  vec2 uv0 = uv;
  vec3 finalcolor = vec3(0.0);
  vec2 st = fragTexCoord.xy / resolution.xy;

  for (float i = 0.0; i < 10.0; i+=5) {
    uv = fract(uv * 2.0) - 0.5;

    float d = length(uv + noise(st*time*.01)*2) + sin(time / 4) * exp(-length(uv0));
    vec3 color = palette(length(uv0)+noise(st*time*.5));
    d = sin(8.*d + time*2)/8;
    d = abs(d);
    d += noise(time*20) * .2;

    d = smoothstep(0.0, 0.004, d);
    d = pow(0.3 / d, 1.2);
    
    finalcolor += color * d; 
  }

  float grain = random(fragTexCoord);
  //finalcolor += grain * 0.25;
  fragColor = vec4(finalcolor, 1.0);

}

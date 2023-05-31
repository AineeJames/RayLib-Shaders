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

void main()
{
  vec2 uv = fragTexCoord * 2.0 - 1.0; 
  uv.x *= resolution.x / resolution.y;
  vec2 uv0 = uv;
  vec3 finalcolor = vec3(0.0);

  for (float i = 0.0; i < 4.0; i+=5) {
    uv = fract(uv * 2.0) - 0.5;

    float d = length(uv) + sin(time / 4) * exp(-length(uv0));
    vec3 color = palette(length(uv0) + time);
    d = sin(8.*d + time/2)/8.;
    d = abs(d);
    d = smoothstep(0.0, 0.1, d);
    d = pow(0.3 / d, 1.2);

    finalcolor += color * d; 
  }

  fragColor = vec4(finalcolor, 1.0);

}

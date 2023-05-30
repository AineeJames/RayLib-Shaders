#version 330

in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 resolution;
uniform vec2 mousepos;
uniform float time;

void main()
{
  vec2 uv = fragTexCoord * 2.0 - 1.0; 
  uv.x *= resolution.x / resolution.y;
  float d = length(uv);
  vec4 color = vec4(d, 0.0, 0.0, 1.0);

  fragColor = color;
}

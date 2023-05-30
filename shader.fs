#version 330

in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 resolution;
uniform vec2 mousepos;

void main()
{
  vec4 color = vec4(mousepos / resolution, 0, 1);
  fragColor = color;
}

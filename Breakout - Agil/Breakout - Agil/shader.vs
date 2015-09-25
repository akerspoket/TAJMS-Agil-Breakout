#version 330


in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
uniform float gScale;

void main()
{
    gl_Position = vec4(Position * gScale, 1.0);
}
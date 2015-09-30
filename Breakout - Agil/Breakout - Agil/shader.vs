#version 330



layout (location=0) in vec3 Position;
layout (location=1) in vec2 TexCoord;
layout (location=2) in vec3 Normal;
layout (location=3) in mat4 Translation;

out vec2 TexCoord0;
uniform mat4 gWorld;
uniform	mat4 gView;
uniform	mat4 gProj;
void main()
{
	mat4 gWVP = gProj * gView * gWorld *Translation;
    gl_Position = gWVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
}
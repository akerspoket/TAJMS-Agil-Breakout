#version 130



in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec2 TexCoord0;

uniform mat4 gWorld;
uniform	mat4 gView;
uniform	mat4 gProj;
uniform mat4 gTransMatrices;
void main()
{
	mat4 gWVP = gProj * gView * gWorld * gTransMatrices;
    gl_Position = gWVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
}
#version 130

out vec4 FragColor;
in vec2 TexCoord0;
in vec3 Normal0;
uniform sampler2D TextureSampler;

void main()
{

	vec2 texCoord = vec2(TexCoord0.x,1 - TexCoord0.y); //Dont know why this should be here but works for chests...
    FragColor = texture2D(TextureSampler, texCoord);
}

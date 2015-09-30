#version 330

out vec4 FragColor;
in vec2 TexCoord0;

uniform sampler2D TextureSampler;

void main()
{
    FragColor = texture2D(TextureSampler, TexCoord0);
}

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;

	uint texturePart : TEXTUREPART;
};

Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	return float4((float)input.texturePart / 5.0f,0,0,1);
	//return ObjTexture.Sample( ObjSamplerState, input.texCoord);
}
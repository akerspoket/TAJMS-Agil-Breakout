struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	return ObjTexture.Sample( ObjSamplerState, input.texCoord);
}
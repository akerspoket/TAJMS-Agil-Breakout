struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	uint texturePart: TEXTUREPART;
};


Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	//return float4(0,1,1,1);

	return ObjTexture.Sample(ObjSamplerState, float2(((float)input.texturePart / 2.0f) + (input.texCoord.x / 2.0f),input.texCoord.y));
	
	

}
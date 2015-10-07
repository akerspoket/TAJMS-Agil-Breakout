struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;

};


Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	//return float4(0,1,1,1);
	input.texCoord.y = 1 - input.texCoord.y;
	return ObjTexture.Sample(ObjSamplerState, input.texCoord);
	
	

}
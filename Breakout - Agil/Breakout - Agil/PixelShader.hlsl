struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	uint instanceID : SV_InstanceID;
};

cbuffer TextureSquare : register(b0)
{
	float square[12];
};

Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	return float4((float)square[2],(float)square[2],(float)square[2],1);

	/*if (input.instanceID == 2)
	{
		
	}
	else
	{
		return ObjTexture.Sample(ObjSamplerState, float2(((float)square[input.instanceID] / 2.0f) + (input.texCoord.x / 2.0f),input.texCoord.y));
	}*/
	

}
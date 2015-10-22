struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 originalPosition : ORIGINALPOS;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};


Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 PShader(PixelInputType input) : SV_TARGET
{
	//return float4(0,1,1,1);
	input.texCoord.y = 1-input.texCoord.y;
	float3 lightPos = (0, 0, 0);
	float3 dir = (0.1f,0.1f,-1.0f);
	float distance = length(dir);
	dir = normalize(dir);
	float factor = clamp(dot(input.normal, dir),0.0f,1.0f);
	return ObjTexture.Sample(ObjSamplerState, input.texCoord)*factor*1.5f;
	
	

}
struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float blend : BLEND;
	float2 texCoord: TEXCOORD;
	float textureID : TEXID;
};

Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

float4 main(PixelInputType input) : SV_TARGET
{
	//Text shader
	
	//return float4(input.color,input.blend);
	float2 texCoord = float2((input.texCoord.x + input.textureID.x) / 4.0f, input.texCoord.y);
	float4 temp = ObjTexture.Sample(ObjSamplerState, texCoord);
	float4 colorBlend = float4(input.color, temp.w - (1 - input.blend));
	return temp * colorBlend;
	
	

}
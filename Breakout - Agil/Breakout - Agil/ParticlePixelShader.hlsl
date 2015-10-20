struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float blend : BLEND;
};


float4 main(PixelInputType input) : SV_TARGET
{
	//Text shader
	
	return float4(input.color,input.blend);
	
	

}
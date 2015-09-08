struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader( float4 pos : POSITION , float4 color : COLOR)
{
	VOut output;
	output.position = pos;
	output.color = color;
	return output;
}
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

//cbuffer MovementBuffer
//{
//	float time;
//};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader( VertexInputType input)
{
	VOut output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.color = input.color;
	return output;
}
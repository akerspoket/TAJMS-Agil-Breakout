cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer MovementBuffer : register(b1)
{
	float time;
	float3 filler;
};

cbuffer InstanceMatrices : register(b2)
{
	matrix translationMatrices[5];
};

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

VOut VShader( VertexInputType input,uint instanceID : SV_InstanceID)
{
	VOut output;

	
	//input.position.y += input.position.y * sin(time);
	input.position = mul(input.position, translationMatrices[instanceID]);
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.color = input.color;
	return output;
}
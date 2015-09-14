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

struct InstanceLayout
{
	matrix translationMatrix;
	float4 colorInstance;
};

cbuffer InstanceMatrices : register(b2)
{
	InstanceLayout instances[5];
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};



struct VOut
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

VOut VShader( VertexInputType input,uint instanceID : SV_InstanceID)
{
	VOut output;

	output.texCoord = input.texCoord;
	//input.position.y += input.position.y * sin(time);
	input.position = mul(input.position, instances[instanceID].translationMatrix);
	//output.color = input.color * instances[instanceID].colorInstance;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	return output;
}
cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
	matrix matris : INSTANCEMATRIX;
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
	input.position = mul(float4(input.position,1.0f), input.matris).xyz;
	//output.color = input.color * instances[instanceID].colorInstance;
	output.position = mul(float4(input.position, 1.0f), worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	return output;
}
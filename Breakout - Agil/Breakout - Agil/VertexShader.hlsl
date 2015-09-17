cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct InstanceLayout
{
	matrix matris;
	float4 texturePart;
};

cbuffer InstanceMatrices : register(b2)
{
	InstanceLayout instances[5];
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;

	matrix matris : INSTANCEMATRIX;
	uint texturePart : TEXTUREPART;
};



struct VOut
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;

	uint texturePart : TEXTUREPART;
};

VOut VShader( VertexInputType input,uint instanceID : SV_InstanceID)
{
	VOut output;

	output.texCoord = input.texCoord;
	//input.position.y += input.position.y * sin(time);
	output.position = mul(input.position, input.matris);
	//output.color = input.color * instances[instanceID].colorInstance;
	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.texturePart = input.texturePart;
	return output;
}
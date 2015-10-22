struct VertexInputType
{
	uint vertexID : SV_VertexID;
};

struct VOut
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float size : SIZE;
	float blend : BLEND;
	float LifeTime : LIFETIME;
	float LifeLength : LIFELENGTH;
};

struct Particle
{
	float3 Position;
	float3 Direction;
	float3 Color;
	float Speed;
	float LifeTime;
	float LifeLength;
	float Size;
	float Blend;
	float StartSize;
};

StructuredBuffer<Particle> particleBuffer: register(u0);

VOut main( VertexInputType input,uint instanceID : SV_InstanceID)
{
	VOut output;
	output.color = particleBuffer[input.vertexID].Color;
	output.position = float4(particleBuffer[input.vertexID].Position, 1.0f);
	output.LifeTime = particleBuffer[input.vertexID].LifeTime;
	output.LifeLength = particleBuffer[input.vertexID].LifeLength;
	output.blend = particleBuffer[input.vertexID].Blend;
	output.size = particleBuffer[input.vertexID].Size;
	return output;
}
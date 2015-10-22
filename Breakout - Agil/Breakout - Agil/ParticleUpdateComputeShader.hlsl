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



RWStructuredBuffer<Particle> inoutput : register (u0);

[numthreads(500, 1, 1)]
void main( uint3 threadID : SV_DispatchThreadID )
{
	inoutput[threadID.x].LifeTime += 0.01;
	if (inoutput[threadID.x].LifeTime >= inoutput[threadID.x].LifeLength)
	{
		return;
	}
	inoutput[threadID.x].Size = inoutput[threadID.x].LifeTime / inoutput[threadID.x].LifeLength * 0.2f + inoutput[threadID.x].StartSize; // va snyggt för svansen
	inoutput[threadID.x].Blend = 1 - inoutput[threadID.x].LifeTime / inoutput[threadID.x].LifeLength;
	inoutput[threadID.x].Position += inoutput[threadID.x].Direction * inoutput[threadID.x].Speed;

}


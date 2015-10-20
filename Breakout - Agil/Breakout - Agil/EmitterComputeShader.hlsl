struct Emitter
{
	float3 Position;
	float LifeTime;
	float3 Color;
	float Density;
	float3 filler;
	float ParticleLifeTime;
	
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
};

cbuffer Emitters : register(b1)
{
	Emitter EmitterInfo[30];
};

cbuffer NumberOfEmitters : register(b2)
{
	int totalEmitters;
	float3 fillers;
};

cbuffer RandomDirections : register(b3)
{
	float4 randomDirection[20]; //needs to be float4 to align in memory, w is ignored
};


RWStructuredBuffer<Particle> output : register (u0);

[numthreads(1, 1, 1)]
void main( uint3 threadID : SV_DispatchThreadID )
{
	Particle NewParticle;
	int dirIndex = 0;
	uint MaxParticles;
	uint tStride;
	output.GetDimensions(MaxParticles, tStride);
	for (int i = 0; i < totalEmitters; i++)
	{
		for (int j = 0; j < EmitterInfo[i].Density; j++)
		{
			output[0].Speed++;

			NewParticle.Position = EmitterInfo[i].Position;
			NewParticle.Direction = normalize(randomDirection[dirIndex].xyz);
			NewParticle.Color = EmitterInfo[i].Color;
			NewParticle.Speed = abs(dot(randomDirection[dirIndex].xyz, randomDirection[dirIndex].xyz)) / length(randomDirection[dirIndex].xyz)/10;
			NewParticle.LifeTime = 0;
			NewParticle.LifeLength = EmitterInfo[i].ParticleLifeTime;
			NewParticle.Blend = 1.0f;
			NewParticle.Size = 0.0f; //Should probably be inserted in emitter info...
			output[output[0].Speed] = NewParticle;
			
			if (output[0].Speed == MaxParticles-1)
			{
				output[0].Speed = 1;
			}
			dirIndex++;
			if (dirIndex > 19)
			{
				dirIndex = 0;
			}
		}
	}

}


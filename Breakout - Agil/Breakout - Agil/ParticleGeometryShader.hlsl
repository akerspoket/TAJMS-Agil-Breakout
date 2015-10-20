struct GeoInputType
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float size : SIZE;
	float blend : BLEND;
	float LifeTime : LIFETIME;
	float LifeLength : LIFELENGTH;
};

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct GOut
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float blend : BLEND;
};

[maxvertexcount(4)]
void main(point GeoInputType gin[1], uint primID : SV_PrimitiveID, inout TriangleStream<GOut> triStream)
{
	if (gin[0].LifeTime >= gin[0].LifeLength)
	{
		return;
	}
	float4 v[4];
	v[0] = float4(gin[0].position.x - gin[0].size, gin[0].position.y + gin[0].size, gin[0].position.z, 1.0f);
	v[1] = float4(gin[0].position.x - gin[0].size, gin[0].position.y - gin[0].size, gin[0].position.z, 1.0f);
	v[2] = float4(gin[0].position.x + gin[0].size, gin[0].position.y + gin[0].size, gin[0].position.z, 1.0f);
	v[3] = float4(gin[0].position.x + gin[0].size, gin[0].position.y - gin[0].size, gin[0].position.z, 1.0f);

	GOut gout;
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		v[i] = mul(v[i], worldMatrix);
		v[i] = mul(v[i], viewMatrix);
		v[i] = mul(v[i], projectionMatrix);
		gout.position = v[i];
		gout.color = gin[0].color;
		gout.blend = gin[0].blend;
		triStream.Append(gout);
	}
	


}
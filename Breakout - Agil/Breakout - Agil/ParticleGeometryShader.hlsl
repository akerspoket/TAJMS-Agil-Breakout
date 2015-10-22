struct GeoInputType
{
	float4 position : SV_POSITION;
	float3 color : COLOR0;
	float size : SIZE;
	float blend : BLEND;
	float LifeTime : LIFETIME;
	float LifeLength : LIFELENGTH;
	float TextureID : TEXID;
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
	float2 texCoord : TEXCOORD;
	float TextureID : TEXID;
};

[maxvertexcount(4)]
void main(point GeoInputType gin[1], uint primID : SV_PrimitiveID, inout TriangleStream<GOut> triStream)
{
	if (gin[0].LifeTime >= gin[0].LifeLength)
	{
		return;
	}
	float4 v[4];
	float2 t[4];
	v[0] = float4(gin[0].position.x - gin[0].size, gin[0].position.y + gin[0].size, gin[0].position.z, 1.0f);
	t[0] = float2(0, 0);
	v[1] = float4(gin[0].position.x - gin[0].size, gin[0].position.y - gin[0].size, gin[0].position.z, 1.0f);
	t[1] = float2(0, 1);
	v[2] = float4(gin[0].position.x + gin[0].size, gin[0].position.y + gin[0].size, gin[0].position.z, 1.0f);
	t[2] = float2(1, 0);
	v[3] = float4(gin[0].position.x + gin[0].size, gin[0].position.y - gin[0].size, gin[0].position.z, 1.0f);
	t[3] = float2(1, 1);

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
		gout.texCoord = t[i];
		gout.TextureID = gin[0].TextureID;
		triStream.Append(gout);
	}
	


}
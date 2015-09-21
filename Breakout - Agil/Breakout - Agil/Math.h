#pragma once



struct vec2
{
	//Member Variables
	float x;
	float y;

	//Constructors
	vec2()
	{
		x = y = 0;
	}

	vec2(float X, float Y)
	{
		x = X;
		y = Y;
	}

	//Operators
	vec2 operator+(vec2 v)
	{
		return vec2(x + v.x, y + v.y);
	}
	vec2 operator-(vec2 v)
	{
		return vec2(x - v.x, y - v.y);
	}
	vec2 operator*(float f)
	{
		return vec2(x *f, y*f);
	}
	void operator*=(float f)
	{
		x *= f;
		y *= f;
	}
	float operator*(vec2 v)
	{
		return x*v.x + y*v.y;
	}
	float Abs()
	{
		return sqrt(x*x + y*y);
	}
	vec2 Normalize()
	{
		float length = Abs();
		return vec2(x / length, y / length);
	}
};


struct vec3
{
	//Member Variables
	float x;
	float y;
	float z;

	//Constructors
	vec3()
	{
		x = y = z = 0;
	}

	vec3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	//Operators
	vec3 operator+(vec3 v)
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 operator-(vec3 v)
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	float operator*(vec3 v)
	{
		return x*v.x + y*v.y + z*v.x;
	}
	void operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
	}
	vec3 operator*(float f)
	{
		return vec3(x *f, y*f, z*f);
	}
	float Abs()
	{
		return sqrt(x*x + y*y + z*z);
	}
	vec3 Normalize()
	{
		float length = Abs();
		return vec3(x / length, y / length, z / length);
	}
};

struct vec4
{
	//Member variables
	float x;
	float y;
	float z;
	float w;

	//Constructors
	vec4()
	{
		x = y = z = w = 0;
	}
	vec4(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	//Operators
	vec4 operator+(vec4 v)
	{
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	vec4 operator-(vec4 v)
	{
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	float operator*(vec4 v)
	{
		return x*v.x + y*v.y + z*v.x + w*v.w;
	}
	void operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
	}
	vec4 operator*(float f)
	{
		return vec4(x *f, y*f, z*f, w*f);
	}
	float Abs()
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	vec4 Normalize()
	{
		float length = Abs();
		return vec4(x / length, y / length, z / length, w / length);
	}
};


static vec3 vec2toVec3(vec2 pVec2)
{
	return vec3(pVec2.x, pVec2.y, 0);
}

static vec4 vec2toVec4(vec2 pVec2)
{
	return vec4(pVec2.x, pVec2.y, 0, 0);
}

static vec2 vec3toVec2(vec3 pVec3)
{
	return vec2(pVec3.x, pVec3.y);
}

static vec4 vec3toVec4(vec3 pVec3)
{
	return vec4(pVec3.x, pVec3.y, pVec3.z, 0);
}

static vec2 vec4toVec2(vec4 pVec4)
{
	return vec2(pVec4.x, pVec4.y);
}
static vec3 vec4toVec3(vec4 pVec4)
{
	return vec3(pVec4.x, pVec4.y, pVec4.z);
}


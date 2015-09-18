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
	float operator*(vec2 v)
	{
		return x*v.x + y*v.y;
	}

	//Methods
	vec3 toVec3()
	{
		return vec3(x, y, 0);
	}
	vec4 toVec4()
	{
		return vec4(x, y, 0, 0);
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

	//Methods
	vec2 toVec2()
	{
		return vec2(x, y);
	}
	vec4 tovec4()
	{
		return vec4(x, y, z, 0);
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

	//Methods
	vec2 toVec2()
	{
		return vec2(x, y);
	}
	vec3 toVec3()
	{
		return vec3(x, y, z);
	}
};
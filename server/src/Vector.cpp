//
//  Vector.cpp
//  Catalyst Game Engine
//
//  Created by Travis True on 1/5/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#include "Vector.h"


namespace CatalystEngine
{
	Vector2::Vector2()
	{
		x = y = 0.0f;
	}


	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}


	Vector2::~Vector2()
	{
		x = y = 0.0f;
	}


	Vector2 Vector2::operator=(Vector2 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		return *this;
	}


	Vector2 Vector2::operator=(Vector3 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		return *this;
	}


	Vector2 Vector2::operator=(Vector4 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		return *this;
	}


	Vector2 Vector2::operator+(Vector2 opt2)
	{
		Vector2 temp;
		temp.x = x + opt2.x;
		temp.y = y + opt2.y;
		return temp;
	}


	Vector2 Vector2::operator-(Vector2 opt2)
	{
		Vector2 temp;
		temp.x = x - opt2.x;
		temp.y = y - opt2.y;
		return temp;
	}


	float Vector2::operator*(Vector2 opt2)
	{
		return (x * opt2.x) + (y * opt2.y);
	}


	Vector2 Vector2::operator*(float opt2)
	{
		Vector2 temp;
		temp.x = x * opt2;
		temp.y = y * opt2;
		return temp;
	}


	Vector2 Vector2::operator/(Vector2 opt2)
	{
		Vector2 temp;
		temp.x = x / opt2.x;
		temp.y = y / opt2.y;
		return temp;
	}


	Vector2 Vector2::operator/(float opt2)
	{
		Vector2 temp;
		temp.x = x / opt2;
		temp.y = y / opt2;
		return temp;
	}


	Vector2 Vector2::operator+=(Vector2 opt2)
	{
		x += opt2.x;
		y += opt2.y;
		return *this;
	}


	Vector2 Vector2::operator*=(float opt2)
	{
		x *= opt2;
		y *= opt2;
		return *this;
	}


	Vector2 Vector2::operator/=(float opt2)
	{
		x /= opt2;
		y /= opt2;
		return *this;
	}


	Vector2 Vector2::operator-=(Vector2 opt2)
	{
		x -= opt2.x;
		y -= opt2.y;
		return *this;
	}


	Vector2 Vector2::operator++()
	{
		x++;
		y++;
		return *this;
	}


	Vector2 Vector2::operator--()
	{
		x--;
		y--;
		return *this;
	}


	Vector2 Vector2::operator++(int notused)
	{
		Vector2 temp = *this;
		x++;
		y++;
		return temp;
	}


	Vector2 Vector2::operator--(int notused)
	{
		Vector2 temp = *this;
		x--;
		y--;
		return temp;
	}


	bool Vector2::operator<(Vector2 opt2)
	{
		if((x < opt2.x) && (y < opt2.y))
			return true;
		else
			return false;
	}


	bool Vector2::operator<=(Vector2 opt2)
	{
		if((x <= opt2.x) && (y <= opt2.y))
			return true;
		else
			return false;
	}


	bool Vector2::operator>(Vector2 opt2)
	{
		if((x > opt2.x) && (y > opt2.y))
			return true;
		else
			return false;
	}


	bool Vector2::operator>=(Vector2 opt2)
	{
		if((x >= opt2.x) && (y >= opt2.y))
			return true;
		else
			return false;
	}


	bool Vector2::operator==(Vector2 opt2)
	{
		if((x == opt2.x) && (y == opt2.y))
			return true;
		else
			return false;
	}


	bool Vector2::operator!=(Vector2 opt2)
	{
		if((x != opt2.x) && (y != opt2.y))
			return true;
		else
			return false;
	}


	void Vector2::SetVector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}


	void Vector2::Print(const char *caption)
	{
		printf("%s<%.3f  %.3f>\n", caption, x, y);
	}


	float Vector2::MagnitudeSq()
	{
		return (x * x) + (y * y);
	}


	float Vector2::Magnitude()
	{
		return sqrtf(MagnitudeSq());
	}


	float Vector2::Normalize()
	{
		float magnitude = Magnitude();
		if(!magnitude) return magnitude;
		*this /= magnitude;
		return magnitude;
	}


	Vector3::Vector3()
	{
		x = y = z = 0.0f;
	}


	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	Vector3::~Vector3()
	{
		x = y = z = 0.0f;
	}


	Vector3 Vector3::operator=(Vector2 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = 0.0f;
		return *this;
	}


	Vector3 Vector3::operator=(Vector3 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = opt2.z;
		return *this;
	}


	Vector3 Vector3::operator=(Vector4 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = opt2.z;
		return *this;
	}


	Vector3 Vector3::operator+(Vector3 opt2)
	{
		Vector3 temp;
		temp.x = x + opt2.x;
		temp.y = y + opt2.y;
		temp.z = z + opt2.z;
		return temp;
	}


	Vector3 Vector3::operator-(Vector3 opt2)
	{
		Vector3 temp;
		temp.x = x - opt2.x;
		temp.y = y - opt2.y;
		temp.z = z - opt2.z;
		return temp;
	}


	float Vector3::operator*(Vector3 opt2)
	{
		return (x * opt2.x) + (y * opt2.y) + (z * opt2.z);
	}


	Vector3 Vector3::operator*(float opt2)
	{
		return Vector3(x * opt2, y * opt2, z * opt2);
	}


	Vector3 Vector3::operator/(Vector3 opt2)
	{
		Vector3 temp;
		temp.x = x / opt2.x;
		temp.y = y / opt2.y;
		temp.z = z / opt2.z;
		return temp;
	}


	Vector3 Vector3::operator/(float opt2)
	{
		Vector3 temp;
		temp.x = x / opt2;
		temp.y = y / opt2;
		temp.z = z / opt2;
		return temp;
	}


	Vector3 Vector3::operator+=(Vector3 opt2)
	{
		x += opt2.x;
		y += opt2.y;
		z += opt2.z;
		return *this;
	}


	Vector3 Vector3::operator*=(float opt2)
	{
		x *= opt2;
		y *= opt2;
		z *= opt2;
		return *this;
	}


	Vector3 Vector3::operator/=(float opt2)
	{
		x /= opt2;
		y /= opt2;
		z /= opt2;
		return *this;
	}


	Vector3 Vector3::operator-=(Vector3 opt2)
	{
		x -= opt2.x;
		y -= opt2.y;
		z -= opt2.z;
		return *this;
	}


	Vector3 Vector3::operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}


	Vector3 Vector3::operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}


	Vector3 Vector3::operator++(int notused)
	{
		Vector3 temp = *this;
		x++;
		y++;
		z++;
		return temp;
	}


	Vector3 Vector3::operator--(int notused)
	{
		Vector3 temp = *this;
		x--;
		y--;
		z--;
		return temp;
	}


	bool Vector3::operator<(Vector3 opt2)
	{
		if((x < opt2.x) && (y < opt2.y) && (z < opt2.z))
			return true;
		else
			return false;
	}


	bool Vector3::operator<=(Vector3 opt2)
	{
		if((x <= opt2.x) && (y <= opt2.y) && (z <= opt2.z))
			return true;
		else
			return false;
	}


	bool Vector3::operator>(Vector3 opt2)
	{
		if((x > opt2.x) && (y > opt2.y) && (z > opt2.z))
			return true;
		else
			return false;
	}


	bool Vector3::operator>=(Vector3 opt2)
	{
		if((x >= opt2.x) && (y >= opt2.y) && (z >= opt2.z))
			return true;
		else
			return false;
	}


	bool Vector3::operator==(Vector3 opt2)
	{
		if((x == opt2.x) && (y == opt2.y) && (z == opt2.z))
			return true;
		else
			return false;
	}


	bool Vector3::operator!=(Vector3 opt2)
	{
		if((x != opt2.x) && (y != opt2.y) && (z != opt2.z))
			return true;
		else
			return false;
	}


	void Vector3::Print(const char *caption)
	{
		printf("%s<%.3f  %.3f  %.3f>\n", caption, x, y, z);
	}


	void Vector3::SetVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	float Vector3::MagnitudeSq()
	{
		return (x * x) + (y * y) + (z * z);
	}


	float Vector3::Magnitude()
	{
		return sqrtf(MagnitudeSq());
	}

	float Vector3::Normalize()
	{
		float magnitude = Magnitude();
		if(!magnitude) return magnitude;
		*this /= magnitude;
		return magnitude;
	}


	Vector3 GetUpVector()
	{ return Vector3(0.0f, 1.0f, 0.0f); }


	Vector3 GetGravityVector()
	{ return Vector3(0.0f, -9.8f, 0.0f); }


	Vector3 CrossProduct(Vector3 a, Vector3 b)
	{
		Vector3 temp;
		temp.x = (a.y * b.z) - (a.z * b.y);
		temp.y = (a.z * b.x) - (a.x * b.z);
		temp.z = (a.x * b.y) - (a.y * b.x);
		return temp;
	}


	Vector4::Vector4()
	{
		x = y = z = w = 0.0f;
	}


	Vector4::Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}


	Vector4::~Vector4()
	{
		x = y = z = w = 0.0f;
	}


	Vector4 Vector4::operator=(Vector2 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = 0.0f;
		w = 1.0f;
		return *this;
	}


	Vector4 Vector4::operator=(Vector3 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = opt2.z;
		w = 1.0f;
		return *this;
	}


	Vector4 Vector4::operator=(Vector4 opt2)
	{
		x = opt2.x;
		y = opt2.y;
		z = opt2.z;
		w = opt2.w;
		return *this;
	}


	Vector4 Vector4::operator+(Vector4 opt2)
	{
		Vector4 temp;
		temp.x = x + opt2.x;
		temp.y = y + opt2.y;
		temp.z = z + opt2.z;
		temp.w = w + opt2.w;
		return temp;
	}


	Vector4 Vector4::operator-(Vector4 opt2)
	{
		Vector4 temp;
		temp.x = x - opt2.x;
		temp.y = y - opt2.y;
		temp.z = z - opt2.z;
		temp.w = w - opt2.w;
		return temp;
	}


	float Vector4::operator*(Vector4 opt2)
	{
		return (x * opt2.x) + (y * opt2.y) + (z * opt2.z) + (w * opt2.w);
	}


	Vector4 Vector4::operator*(float opt2)
	{
		Vector4 temp;
		temp.x = x * opt2;
		temp.y = y * opt2;
		temp.z = z * opt2;
		temp.w = w * opt2;
		return temp;
	}


	Vector4 Vector4::operator/(Vector4 opt2)
	{
		Vector4 temp;
		temp.x = x / opt2.x;
		temp.y = y / opt2.y;
		temp.z = z / opt2.z;
		temp.w = w / opt2.w;
		return temp;
	}


	Vector4 Vector4::operator/(float opt2)
	{
		Vector4 temp;
		temp.x = x / opt2;
		temp.y = y / opt2;
		temp.z = z / opt2;
		temp.w = w / opt2;
		return temp;
	}


	Vector4 Vector4::operator+=(Vector4 opt2)
	{
		x += opt2.x;
		y += opt2.y;
		z += opt2.z;
		w += opt2.w;
		return *this;
	}


	Vector4 Vector4::operator*=(float opt2)
	{
		x *= opt2;
		y *= opt2;
		z *= opt2;
		w *= opt2;
		return *this;
	}


	Vector4 Vector4::operator/=(float opt2)
	{
		x /= opt2;
		y /= opt2;
		z /= opt2;
		w /= opt2;
		return *this;
	}


	Vector4 Vector4::operator-=(Vector4 opt2)
	{
		x -= opt2.x;
		y -= opt2.y;
		z -= opt2.z;
		z -= opt2.w;
		return *this;
	}


	Vector4 Vector4::operator++()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}


	Vector4 Vector4::operator--()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}


	Vector4 Vector4::operator++(int notused)
	{
		Vector4 temp = *this;
		
		x++;
		y++;
		z++;
		w++;
		return temp;
	}


	Vector4 Vector4::operator--(int notused)
	{
		Vector4 temp = *this;
		
		x--;
		y--;
		z--;
		w--;
		return temp;
	}


	bool Vector4::operator<(Vector4 opt2)
	{
		if((x < opt2.x) && (y < opt2.y) && (z < opt2.z) && (w < opt2.w))
			return true;
		else
			return false;
	}


	bool Vector4::operator<=(Vector4 opt2)
	{
		if((x <= opt2.x) && (y <= opt2.y) && (z <= opt2.z) && (w <= opt2.w))
			return true;
		else
			return false;
	}


	bool Vector4::operator>(Vector4 opt2)
	{
		if((x > opt2.x) && (y > opt2.y) && (z > opt2.z) && (w > opt2.w))
			return true;
		else
			return false;
	}


	bool Vector4::operator>=(Vector4 opt2)
	{
		if((x >= opt2.x) && (y >= opt2.y) && (z >= opt2.z) && (w >= opt2.w))
			return true;
		else
			return false;
	}


	bool Vector4::operator==(Vector4 opt2)
	{
		if((x == opt2.x) && (y == opt2.y) && (z == opt2.z) && (w == opt2.w))
			return true;
		else
			return false;
	}


	bool Vector4::operator!=(Vector4 opt2)
	{
		if((x != opt2.x) && (y != opt2.y) && (z != opt2.z) && (w != opt2.w))
			return true;
		else
			return false;
	}


	void Vector4::SetVector(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}


	void Vector4::Print(char *caption)
	{
		printf("%s<%.2f  %.2f  %.2f  %.2f>\n", caption, x, y, z, w);
	}


	float Vector4::MagnitudeSq()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}


	float Vector4::Magnitude()
	{
		return sqrtf(MagnitudeSq());
	}


	float Vector4::Normalize()
	{
		float magnitude = Magnitude();
		if(!magnitude) return magnitude;
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
		return magnitude;
	}
}

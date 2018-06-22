//
//  Vector.h
//  Catalyst Game Engine
//
//  Created by Travis True on 1/5/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H

#include "CatalystEnumeration.h"


namespace CatalystEngine
{
	class Vector3;
	class Vector4;


	class Vector2
	{
	public:
		float x, y;
		
		// constructors/destructor
		Vector2();
		Vector2(float x, float y);
		~Vector2();
		
		// operator overloads
		Vector2 operator=(Vector2 opt2);
		Vector2 operator=(Vector3 opt2);
		Vector2 operator=(Vector4 opt2);
		Vector2 operator+(Vector2 opt2);
		Vector2 operator-(Vector2 opt2);
		float   operator*(Vector2 opt2);
		Vector2 operator*(float opt2);
		Vector2 operator/(Vector2 opt2);
		Vector2 operator/(float opt2);
		Vector2 operator+=(Vector2 opt2);
		Vector2 operator-=(Vector2 opt2);
		Vector2 operator*=(float opt2);
		Vector2 operator/=(float opt2);
		Vector2 operator++();
		Vector2 operator--();
		Vector2 operator++(int notused);
		Vector2 operator--(int notused);
		bool    operator<(Vector2 opt2);
		bool    operator<=(Vector2 opt2);
		bool    operator>(Vector2 opt2);
		bool    operator>=(Vector2 opt2);
		bool    operator==(Vector2 opt2);
		bool    operator!=(Vector2 opt2);
		
		void SetVector(float x, float y);
		void Print(const char *caption);
		float MagnitudeSq();
		float Magnitude();
		float Normalize();
	};


	class Vector3
	{
	public:
		float x, y, z;
		
		// constructors/destructor
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();
		
		// operator overloads
		Vector3 operator=(Vector2 opt2);
		Vector3 operator=(Vector3 opt2);
		Vector3 operator=(Vector4 opt2);
		Vector3 operator+(Vector3 opt2);
		Vector3 operator-(Vector3 opt2);
		float   operator*(Vector3 opt2);
		Vector3 operator*(float opt2);
		Vector3 operator/(Vector3 opt2);
		Vector3 operator/(float opt2);
		Vector3 operator+=(Vector3 opt2);
		Vector3 operator-=(Vector3 opt2);
		Vector3 operator*=(float opt2);
		Vector3 operator/=(float opt2);
		Vector3 operator++();
		Vector3 operator--();
		Vector3 operator++(int notused);
		Vector3 operator--(int notused);
		bool    operator<(Vector3 opt2);
		bool    operator<=(Vector3 opt2);
		bool    operator>(Vector3 opt2);
		bool    operator>=(Vector3 opt2);
		bool    operator==(Vector3 opt2);
		bool    operator!=(Vector3 opt2);
		
		void SetVector(float x, float y, float z);
		void Print(const char *caption);
		float MagnitudeSq();
		float Magnitude();
		float Normalize();
	};


	Vector3 GetUpVector();
	Vector3 GetGravityVector();
	Vector3 CrossProduct(Vector3 a, Vector3 b);


	class Vector4
	{
	public:
		float x, y, z, w;
		
		// constructors/destructor
		Vector4();
		Vector4(float x, float y, float z, float w);
		~Vector4();
		
		Vector4 operator=(Vector2 opt2);
		Vector4 operator=(Vector3 opt2);
		Vector4 operator=(Vector4 opt2);
		Vector4 operator+(Vector4 opt2);
		Vector4 operator-(Vector4 opt2);
		float   operator*(Vector4 opt2);
		Vector4 operator*(float opt2);
		Vector4 operator/(Vector4 opt2);
		Vector4 operator/(float opt2);
		Vector4 operator+=(Vector4 opt2);
		Vector4 operator-=(Vector4 opt2);
		Vector4 operator*=(float opt2);
		Vector4 operator/=(float opt2);
		Vector4 operator++();
		Vector4 operator--();
		Vector4 operator++(int notused);
		Vector4 operator--(int notused);
		bool    operator<(Vector4 opt2);
		bool    operator<=(Vector4 opt2);
		bool    operator>(Vector4 opt2);
		bool    operator>=(Vector4 opt2);
		bool    operator==(Vector4 opt2);
		bool    operator!=(Vector4 opt2);
		
		void SetVector(float x, float y, float z, float w);
		void Print(char *caption);
		float MagnitudeSq();
		float Magnitude();
		float Normalize();
	};
}

#endif // VECTOR_H

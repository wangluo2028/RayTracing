
#ifndef VECTOR3
#define VECTOR3


#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class vec3
{
public:
	vec3(){}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r()const { return e[0]; }
	inline float g()const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator + ()const { return *this; }
	inline vec3& operator - () const { return  vec3(-e[0], -e[1], -e[2]); }
	inline float operator[] (int i) const { return e[i]; }
	inline float& operator [](int i) { return e[i]; }

	inline vec3& operator+=(const vec3 & v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
	inline vec3& operator *=(const float t);
	inline vec3& operator /=(const float t);

	inline void make_unit_vector();
	inline float squared_length() const
	{
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline float length()const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}


	float e[3];
};


inline void vec3::make_unit_vector() 
{
	float k = (float)1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline vec3& vec3:: operator +=(const vec3& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline vec3& vec3::operator -=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline vec3& vec3::operator  *= (const vec3& v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline vec3& vec3::operator /=(const vec3 &v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline vec3& vec3::operator *=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator /=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}



inline std::istream& operator >> (istream &is, vec3& t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator <<(ostream& os, const vec3& t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline vec3 operator+(const vec3& v1, const vec3&  v2)
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator* (const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator / (const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator* (float t, const vec3& v)
{
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator /(vec3 v, float t)
{
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator *(const vec3&v, float t)
{
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}


inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n)*n;
}

inline bool refract(const vec3& v, const vec3& normal, float ni_over_nt, vec3& refracted)
{
	// Normalize ray 
	vec3 uv = unit_vector(v);

	// Calculate the projection of 'uv' onto 'n'
	float dt = dot(uv, normal);

	// according to n1 * sin¦Ä == n2 * sin¦Ã
	// Calculate the projection of refracted ray onto 'normal'
	float discriminant = 1.f - ni_over_nt*ni_over_nt*(1.f - dt*dt);

	// judge whether or not the ray will refract
	if (discriminant > 0)
	{
		refracted = ni_over_nt*(uv - normal*dt) - normal*sqrt(discriminant);
		return true;
	}
	else
		return false; // end if
}

#endif

#ifndef VECTOR3
#define VECTOR3

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
	inline vec3& operator -() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[] (int i) const { return e[i]; }
	inline float& operator [](int i) { return e[i]; }

	inline vec3& operator+=(const vec3 & v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
	inline vec3& operator *=(const float t);
	inline vec3& operator /=(const float t);

	inline void vec3::make_unit_vector();
	inline float vec3::squared_length() const;
	

	inline float length()const;



	float e[3];
};

inline vec3 unit_vector(vec3 v);

inline vec3 operator* (float t, const vec3& v);

inline vec3 operator* (const vec3 &v1, const vec3 &v2);

#endif
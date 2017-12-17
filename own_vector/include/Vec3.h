#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>

class Vec3 {
public:
	float e[3];
	unsigned char rgb[3];
	static const unsigned char MAX_RGB = 255;

	Vec3() : e{0, 0, 0}, rgb{0, 0, 0} {}
	Vec3(float _e0, float _e1, float _e2);
	Vec3(const Vec3 &_v2);
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline int r() const { return rgb[0]; }
	inline int g() const { return rgb[1]; }
	inline int b() const { return rgb[2]; }

	inline float squared_length() const 
	{ return (e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
	inline float length() const 
	{ return sqrt( this->squared_length()); }
	inline Vec3 unit_vector()
	{ return *this / this->length(); }
	void make_RGB(int _maxRGB = MAX_RGB);

	inline float operator[](int _i) const { return e[_i]; }
	inline float& operator[](int _i) { return e[_i]; }

	// vector/scalar operations
	Vec3 operator*(float _scalar) const;
	inline friend Vec3 operator*(float _scalar, const Vec3& _v)
	{ return _v*_scalar; }
	Vec3 operator/(float _scalar) const;
	Vec3 operator+(float _scalar) const;
	Vec3 operator-(float _scalar) const;
	Vec3& operator+=(float _scalar);

	// vector/vector operations
	inline friend float dot(const Vec3& _v1, const Vec3& _v2)
	{ return _v1.e[0]*_v2.e[0] + _v1.e[1]*_v2.e[1] + _v1.e[2]*_v2.e[2]; }
	Vec3 operator+(const Vec3& _v2) const;
	Vec3 operator-(const Vec3& _v2) const;
};

#endif		
#include "Vec3.h"

Vec3::Vec3(float _e0, float _e1, float _e2) :
e{_e0, _e1, _e2}, rgb{0, 0, 0}
{}

Vec3::Vec3(const Vec3 &_v2) :
e{_v2.e[0], _v2.e[1], _v2.e[2]}, rgb{0, 0, 0}
{}

Vec3 Vec3::operator*(float _scalar) const
{
	Vec3 v = *this;
	v.e[0] *= _scalar; v.e[1] *= _scalar; v[2] *= _scalar;
	return v;
}

Vec3 Vec3::operator/(float _scalar) const
{
	Vec3 v = *this;
	v.e[0] /= _scalar; v.e[1] /= _scalar; v[2] /= _scalar;
	return v;
}

Vec3 Vec3::operator+(float _scalar) const
{
	Vec3 v = *this;
	v.e[0] += _scalar; v.e[1] += _scalar; v[2] += _scalar;
	return v;
}

Vec3 Vec3::operator-(float _scalar) const
{
	Vec3 v = *this;
	v.e[0] -= _scalar; v.e[1] -= _scalar; v[2] -= _scalar;
	return v;
}

Vec3& Vec3::operator+=(float _scalar)
{
	e[0] += _scalar;
	e[1] += _scalar;
	e[2] += _scalar;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& _v2) const
{
	Vec3 v = *this;
	v.e[0] += _v2.e[0]; v.e[1] += _v2.e[1]; v.e[2] += _v2.e[2];
	return v;
}

Vec3 Vec3::operator-(const Vec3& _v2) const
{
	Vec3 v = *this;
	v.e[0] -= _v2.e[0]; v.e[1] -= _v2.e[1]; v.e[2] -= _v2.e[2];
	return v;
}


void Vec3::make_RGB(int _maxRGB)
{
	float top = _maxRGB + 0.99;
	rgb[0] = int(top * sqrt(e[0]));
	rgb[1] = int(top * sqrt(e[1]));
	rgb[2] = int(top * sqrt(e[2]));
}
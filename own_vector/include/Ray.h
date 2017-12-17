#ifndef __RAY_H__
#define __RAY_H__

#include "Vec3.h"

class Ray {
public:
	Vec3 A, B;

	Ray() {}
	Ray(const Vec3& _a, const Vec3& _b) : A(_a), B(_b) {}
	Vec3 origin() const { return A; }
	Vec3 direction() const { return B; }
	Vec3 point_at(float _t) const { return A + (_t*B); }
};

#endif
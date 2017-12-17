#ifndef __HITABLE_H__
#define __HITABLE_H__

#include "Vec3.h"
#include "Ray.h"

struct HitRecord {
	float t;
	Vec3 point;
	Vec3 normal;
};

class Hitable {
public:
	virtual bool hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const = 0;
};

#endif
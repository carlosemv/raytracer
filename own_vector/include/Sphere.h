#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Hitable.h"

class Sphere : public Hitable {
public:
	Vec3 center;
	float radius;

	Sphere() {}
	Sphere(Vec3 _c, float _r) : center(_c), radius(_r) {}
	virtual bool hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const;
	void make_record(const Ray& _r, float _t, HitRecord& _rec) const;
};

#endif
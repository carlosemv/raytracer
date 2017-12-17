#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Hitable.h"
#include "Material.h"

class Sphere : public Hitable {
public:
	glm::vec3 center;
	float radius;
	std::shared_ptr<Material> material;

	Sphere() {}
	Sphere(glm::vec3 _c, float _r, std::shared_ptr<Material> _m) :
		center(_c), radius(_r), material(_m) {}
	virtual bool hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const;
	void make_record(const Ray& _r, float _t, HitRecord& _rec) const;
};

#endif
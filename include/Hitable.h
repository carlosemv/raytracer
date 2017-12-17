#ifndef __HITABLE_H__
#define __HITABLE_H__

#include <memory>
#include "Ray.h"

class Material;

struct HitRecord {
	float t;
	glm::vec3 point;
	glm::vec3 normal;
	std::shared_ptr<Material> material;
};

class Hitable {
public:
	virtual bool hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const = 0;
};

#endif
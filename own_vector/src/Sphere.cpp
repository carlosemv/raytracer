#include "Sphere.h"

bool Sphere::hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const 
{
	/* 
	 * Ray : A + t*B	
	 * dot(ray(t) - center, ray(t) - center) = r2
	 * dot(A + t*B - C, A + t*B - C) = r2
	 * t*t*dot(B, B) + 2*t*dot(A-C, B) + dot(A-C, A-C) - r2 = 0
	 */

	Vec3 ac = _r.origin() - center; // A - C
	float a = dot(_r.direction(), _r.direction()); // dot(B, B)
	float b = 2.0 * dot(ac, _r.direction()); // 2*dot(A-C, B)
	float c = dot(ac, ac) - radius*radius;

	float discriminant = b*b - 4*a*c;
	if (discriminant <= 0)
		return false;

	// discriminant > 0
	float t = (-b - sqrt(discriminant)) / (2.0*a);
	if (t > _t_min && t < _t_max) {
		make_record(_r, t, _rec);
		return true;
	}
	
	t = (-b + sqrt(discriminant)) / (2.0*a);
	if (t > _t_min && t < _t_max) {
		make_record(_r, t, _rec);
		return true;
	}

	return false;
}

void Sphere::make_record(const Ray& _r, float _t, HitRecord& _rec) const 
{
	_rec.t = _t;
	_rec.point = _r.point_at(_t);
	_rec.normal = (_rec.point - center) / radius;
}
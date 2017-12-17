#include "HitableList.h"

bool HitableList::hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const 
{
	HitRecord record;
	bool any_hit = false;
	float closest = _t_max;

	for (auto&& obj : list) {
		if (obj->hit(_r, _t_min, closest, record)) {
			any_hit = true;
			closest = record.t;
			_rec = record;
		}
	}

	return any_hit;
}
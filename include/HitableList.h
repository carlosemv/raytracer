#ifndef __HITABLE_LIST_H__
#define __HITABLE_LIST_H__

#include <vector>
#include "Hitable.h"

class HitableList : public Hitable {
public:
	std::vector<std::unique_ptr<Hitable>> list;

	HitableList() {}
	HitableList(std::vector<std::unique_ptr<Hitable>> _l) : list(std::move(_l)) {}
	virtual bool hit(const Ray& _r, float _t_min, float _t_max, HitRecord& _rec) const;
	void add(std::unique_ptr<Hitable> _n) { list.push_back(std::move(_n)); }
};

#endif
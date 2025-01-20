//
// Created by Patrick Li on 12/27/24.
//

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"

#include <vector>

class HittableList : public Hittable{
public:
	std::vector<std::shared_ptr<Hittable>> objs;
	HittableList();
	HittableList(std::shared_ptr<Hittable> obj);

	void add(std::shared_ptr<Hittable> obj);
	void clear();
	bool hit(const Ray& r, Interval rayIntv, hit_record& hr) const;
};



#endif //HITTABLELIST_H

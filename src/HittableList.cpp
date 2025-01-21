//
// Created by Patrick Li on 12/27/24.
//

#include "HittableList.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> obj) {
	add(obj);
}

void HittableList::clear() {
	objs.clear();
}
void HittableList::add(std::shared_ptr<Hittable> obj) {
	objs.push_back(obj);
	bb = Bbox(bb, obj->boundingBox());
}/*
void HittableList::add(Hittable&& obj) {
	Hittable* temp = new Hittable(std::move(obj));
	objs.push_back(temp);
}
*/
bool HittableList::hit(const Ray& r, Interval rayIntv, hit_record& hr) const {
	hit_record temp;
	bool hit = false;
	double closest = rayIntv.max;
	for(const auto& o : objs) {
		if(o->hit(r, Interval(rayIntv.min, closest), temp)) {
			hit = true;
			closest = temp.t;
			hr = temp;
		}
	}
	return hit;
}

Bbox HittableList::boundingBox() const {
	return bb;
}
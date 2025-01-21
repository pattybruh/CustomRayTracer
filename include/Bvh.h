//
// Created by Patrick Li on 1/21/25.
//

#ifndef BVH_H
#define BVH_H
#include "Bbox.h"
#include "Hittable.h"
#include "HittableList.h"


class BvhNode : public Hittable {
	std::shared_ptr<Hittable> m_left;
	std::shared_ptr<Hittable> m_right;
	Bbox m_bb;

	static bool boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axisIdx);
	static bool xboxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
		return boxCompare(a,b,0);
	}
	static bool yboxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
		return boxCompare(a,b,1);
	}
	static bool zboxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
		return boxCompare(a,b,2);
	}
public:
	BvhNode(HittableList& list);
	BvhNode(std::vector<std::shared_ptr<Hittable>>& objs, size_t start, size_t end);
	bool hit(const Ray& r, Interval rayIntv, hit_record& rec) const override;
	Bbox boundingBox() const override;
};



#endif //BVH_H

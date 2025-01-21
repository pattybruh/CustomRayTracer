//
// Created by Patrick Li on 1/21/25.
//

#include "Bvh.h"
#include <algorithm>

bool BvhNode::boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axisIdx) {
	Interval aIntv = a->boundingBox().axisInterval(axisIdx);
	Interval bIntv = b->boundingBox().axisInterval(axisIdx);
	return aIntv.min < bIntv.min;
}

BvhNode::BvhNode(HittableList& list) : BvhNode(list.objs, 0, list.objs.size()) {
}

BvhNode::BvhNode(std::vector<std::shared_ptr<Hittable>>& objs, size_t start, size_t end) {
	m_bb = Bbox::Bbox_Empty;
	for(size_t idx=start; idx<end; idx++) {
		m_bb = Bbox(m_bb, objs[idx]->boundingBox());
	}
	int axis = m_bb.longestAxis();

	auto comparator = (axis == 0) ? xboxCompare
					: (axis == 1) ? yboxCompare
					: zboxCompare;
	size_t len = end-start;
	if(len == 1) {
		m_left = m_right = objs[start];
	}
	else if(len == 2) {
		m_left = objs[start];
		m_right = objs[start+1];
	}
	else {
		std::sort(objs.begin()+start, objs.begin()+end, comparator);
		size_t mid = start+len/2;
		m_left = std::make_shared<BvhNode>(objs, start, mid);
		m_right = std::make_shared<BvhNode>(objs, mid, end);
	}
}

bool BvhNode::hit(const Ray& r, Interval rayIntv, hit_record& rec) const {
	if(!m_bb.hit(r,rayIntv)) return false;
	bool hitLeft = m_left->hit(r, rayIntv, rec);
	bool hitRight = m_right->hit(r, Interval(rayIntv.min, hitLeft? rec.t : rayIntv.max), rec);
	return hitLeft || hitRight;
}

Bbox BvhNode::boundingBox() const {
	return m_bb;
}

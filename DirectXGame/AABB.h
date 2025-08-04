#pragma once
#include "KamataEngine.h"

struct AABB {
	KamataEngine::Vector3 min;
	KamataEngine::Vector3 max;
	//ここに入れる
};

class AABBUtil {
public:
	static KamataEngine::Vector3 GetWorldPosition(const KamataEngine::WorldTransform& transform) { return transform.translation_; }

	static AABB GetAABB(const KamataEngine::WorldTransform& transform, float width, float height);
	
	static bool CheckAABBCollision(const AABB& a, const AABB& b) {
		return (a.min.x <= b.max.x && a.max.x >= b.min.x && a.min.y <= b.max.y 
			&& a.max.y >= b.min.y && a.min.z <= b.max.z && a.max.z >= b.min.z);
	}
};

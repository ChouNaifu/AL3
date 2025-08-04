#include "AABB.h"
#include "math/MathUtility.h"

using namespace KamataEngine;
using namespace MathUtility;

AABB AABBUtil::GetAABB(const KamataEngine::WorldTransform& transform, float width, float height) { 
	KamataEngine::Vector3 pos = GetWorldPosition(transform);
	AABB aabb;
	aabb.min = pos + KamataEngine::Vector3{-width / 2.0f, -height / 2.0f, -width / 2.0f};
	aabb.max = pos + KamataEngine::Vector3{width / 2.0f, height / 2.0f, width / 2.0f};
	return aabb;
}

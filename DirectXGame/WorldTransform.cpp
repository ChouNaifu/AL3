#include "3d/WorldTransform.h"
#include "math/MathUtility.h"

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::MakeAffineMatrix() {
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale_);
	Matrix4x4 rotationXMatrix = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 rotationYMatrix = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 rotationZMatrix = MakeRotateZMatrix(rotation_.z);
	Matrix4x4 translationMatrix = MakeTranslateMatrix(translation_);
	matWorld_ = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
}

void WorldTransform::UpdateMatrix() { 
	MakeAffineMatrix();
	TransferMatrix();
}	
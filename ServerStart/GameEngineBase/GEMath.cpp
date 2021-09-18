#include "GEMath.h"

const float GEVector::GPI = 3.14159265359f;
const float GEVector::GR2D = 180.0f / GPI;
const float GEVector::GD2R = GPI / 180.0f;
const GEVector GEVector::LEFT = {-1.0f, 0.0f, 0.0f };
const GEVector GEVector::RIGHT = { 1, 0.0f, 0.0f };
const GEVector GEVector::UP = { 0.0f, -1.0f, 0.0f };
const GEVector GEVector::DOWN = { 0.0f, 1.0f, 0.0f };
const GEVector GEVector::ZERO = { 0.0f, 0.0f, 0.0f };

float GEVector::Angle(GEVector _Left, GEVector _Right)
{
	_Left.Normalize();
	_Right.Normalize();

	DirectX::XMVECTOR Vec = DirectX::XMVector3AngleBetweenNormals(_Left.DxVector, _Right.DxVector);

	//m_OBB.Center.z = Pos.x;
	//m_OBB.Center.x = Pos.y;
	//m_OBB.Center.y = Pos.z;

	return GR2D * Vec.m128_f32[0];
}
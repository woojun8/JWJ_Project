#pragma once
#include <memory.h>
#include <DirectXCollision.h>

class GEMath
{
};

// c++에서 구조체와 class의 차이는
// 오로지 디폴트 접근제한 지정자의 차이밖에 없다.
// 디폴트 접근제한지정자가 public: struct
// 디폴트 접근제한지정자가 private: class

class GEVector
{
public:
	static const float GPI;
	static const float GR2D;
	static const float GD2R;
	static const GEVector LEFT;
	static const GEVector RIGHT;
	static const GEVector UP;
	static const GEVector DOWN;
	static const GEVector ZERO;

public:

	union 
	{
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};

		DirectX::XMFLOAT3 Dxfloat3;
		DirectX::XMFLOAT4 Dxfloat4;
		DirectX::XMVECTOR DxVector;
		float Arr[4];
	};

	//union 
	//{
		//struct 
		//{
		//};
		//float Arr[4];
	//};

public:
	inline int ix() const
	{
		// return (int)(x);
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int hix() const
	{
		// return (int)(x);
		return ix() / 2;
	}

	inline int hiy() const
	{
		return iy() / 2;
	}

	inline float hx() const
	{
		// return (int)(x);
		return x * 0.5f;
	}

	inline float hy() const
	{
		return y * 0.5f;
	}

	inline float operator[](int _Index) const
	{
		return Arr[_Index];
	}

	inline float Len()
	{
		DirectX::XMVECTOR Vec = DirectX::XMVector3Length(DxVector);

		return Vec.m128_f32[0];
	}

	inline void Normalize()
	{
		DxVector = DirectX::XMVector3Normalize(DxVector);
	}

	inline void Copy3D(float* _Data)
	{
		memcpy_s(&x, sizeof(float) * 3, _Data, sizeof(float) * 3);
	}

	inline void Copy(float* _Data) 
	{
		memcpy_s(&x, sizeof(float) *4, _Data, sizeof(float) * 4);
	}


	static float Angle(GEVector _Left, GEVector _Right);


	inline GEVector& operator=(const GEVector& _Other)
	{
		// 복사연산으로 
		x = _Other.x;
		y = _Other.y;
		z = _Other.z;
		w = _Other.w;

		// memcpy_s(this, sizeof(GEVector), &_Other, sizeof(GEVector));
		return *this;
	}

	inline GEVector operator-()
	{
		return GEVector(-x, -y, -z);
	}


	inline GEVector operator-(const GEVector& _Other)
	{
		GEVector Result;

		Result.x = x - _Other.x;
		Result.y = y - _Other.y;
		Result.z = z - _Other.z;
		return Result;
	}


	inline GEVector operator+(const GEVector& _Other)
	{
		GEVector Result;

		Result.x = x + _Other.x;
		Result.y = y + _Other.y;
		Result.z = z + _Other.z;
		return Result;
	}

	inline GEVector operator*(const float _Other)
	{
		GEVector Result;

		Result.x = x * _Other;
		Result.y = y * _Other;
		Result.z = z * _Other;
		return Result;
	}

	inline GEVector operator*(const GEVector& _Other)
	{
		GEVector Result;

		Result.x = x * _Other.x;
		Result.y = y * _Other.y;
		Result.z = z * _Other.z;
		return Result;
	}

	inline GEVector& operator+=(const GEVector& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	inline GEVector& operator*=(const GEVector& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	inline GEVector& operator*=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;
		return *this;
	}


	inline bool operator==(const GEVector& _Other)
	{
		return _Other.x == x && _Other.y == y && _Other.z == z;
	}

	inline bool operator!=(const GEVector& _Other)
	{
		return _Other.x != x || _Other.y != y || _Other.z != z;
	}

	//GEVector& operator=(const GEVector& _Other) 
	//{
	//	x = _Other.x;
	//	y = _Other.y;
	//	z = _Other.z;
	//	w = _Other.w;
	//	return *this;
	//}

public:
	GEVector() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	GEVector(const float* _Other) : x(_Other[0]), y(_Other[1]), z(_Other[2]), w(1.0f)
	{

	}

	GEVector(const GEVector& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
	{

	}
	// 복사 생성자
	/*GEVector(const GEVector& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
	{

	}*/

	GEVector(int _X, int _Y) : x(static_cast<float>(_X)), y(static_cast<float>(_Y)), z(0.0f), w(1.0f)
	{

	}

	GEVector(float _X, float _Y) : x(_X), y(_Y), z(0.0f), w(1.0f)
	{

	}

	GEVector(float _X, float _Y, float _Z) : x(_X), y(_Y), z(_Z), w(1.0f)
	{

	}


};

typedef GEVector float4;
typedef GEVector Rotfloat4; // {40, 20, 90}
typedef GEVector Sizefloat4; // {100, 100, 100}
typedef GEVector Posfloat4;
typedef GEVector Dirfloat4;
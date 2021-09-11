/*===========================================================================
  @file   VectorClass.h
  @brief 2次、3次、4次元クラス
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "main.h"
/*===========================================================================
	2Dベクトル
===========================================================================*/
struct Vector2f :public XMFLOAT2
{
	Vector2f() = default;
	Vector2f(float x, float y)
	{
		this->x = x;  this->y = y;
	}
	Vector2f(const XMVECTOR& other) :XMFLOAT2() {
		XMVECTOR temp = other;
		XMStoreFloat2(this, temp);
	}
	//const Vector2f operator +(const Vector2f& other) const{ return Vector2f(x + other.x, y + other.y); }

	//const Vector2f operator -(const Vector2f& other) const { return Vector2f(x - other.x, y - other.y); }

	Vector2f& operator +=(const Vector2f& other) { return *this = *this + other; }
	Vector2f& operator -=(const Vector2f& other) { return *this = *this - other; }
	inline BOOL operator == (const Vector2f&r) const { return x == r.x && y == r.y; }
	inline BOOL operator != (const Vector2f&r) const { return x != r.x || y != r.y; }
	inline XMVECTOR operator *(const float r) const { return Vector2f(x * r, y * r); }
	inline XMVECTOR operator /(const float r) const { return Vector2f(x / r, y / r); }

	// ベクトルの内積
	constexpr float Dot(Vector2f In)const { return x * In.x + y * In.y ; }
	//// ベクトルの外積
	//constexpr Vector3f Cross(Vector2f In)const {
	//	return Vector3f(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x);
	//}
	//角度を求める
	float Angle(Vector2f In) {
		float cosine_sita = Dot(In) / (Length()*In.Length());
		float sita = acosf(cosine_sita);
		return sita;
	}
	//代入
	Vector2f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat2(this, temp);
		return *this;
	}
	//キャスト
	operator XMVECTOR() const {
		return XMLoadFloat2(this);
	}
	//長さ
	float Length() const {
		return (static_cast<Vector2f>(XMVector2Length(XMVECTOR(*this)))).x;
	}
	//正規化
	void Normalize() {
		*this = XMVector2Normalize(XMVECTOR(*this));
	} 
	
};
/*===========================================================================
	3Dベクトル
===========================================================================*/
struct Vector3f : public XMFLOAT3
{
	Vector3f() = default;
	constexpr Vector3f(float x, float y, float z):XMFLOAT3()
	{
		this->x = x; this->y = y; this->z = z;
	}
	//コンストラクタ
	Vector3f(const XMVECTOR& other) :XMFLOAT3() {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
	}
	Vector3f& operator +=(const Vector3f& other) { return *this = *this + other; }
	Vector3f& operator -=(const Vector3f& other) { return *this = *this - other; }
	Vector3f& operator *=(const Vector3f& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	Vector3f& operator /=(const Vector3f& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	inline BOOL operator == (const Vector3f&r) const { return x == r.x && y == r.y && z == r.z; }
	inline BOOL operator != (const Vector3f&r) const { return x != r.x || y != r.y || z != r.z; }
	Vector3f& operator *=(const float r) { x *= r; y *= r; z *= r; return *this; }
	inline Vector3f& operator /=(const float r) { return *this *= (1.0f / r); }

	// ベクトルの内積
	constexpr float Dot(Vector3f In)const { return x * In.x + y * In.y + z * In.z; }
	// ベクトルの外積
	constexpr Vector3f Cross(Vector3f In)const {
		return Vector3f(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x); }
	// ベクトルのスケーリング
	Vector3f Scale(float Scale) { *this *= Scale;  return *this; }
	//角度を求める
	float Angle(Vector3f In) {
		float cosine_sita = Dot(In) / (Length()*In.Length());
		float sita = acosf(cosine_sita);
		return sita;
	}
	//代入
	Vector3f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
		return *this;
	}
	Vector3f& operator=(const XMFLOAT3& other) {
		this->x = other.x; this->y = other.y; this->z = other.z;
		return *this;
	}
	
	//キャスト
	operator XMVECTOR() const {
		return XMLoadFloat3(this);
	}
	//長さ
	float Length() const {
		return (static_cast<Vector3f>(XMVector3Length(XMVECTOR(*this)))).x;
	}
	//正規化
	void Normalize() {
		*this = XMVector3Normalize(XMVECTOR(*this));
	}
};
/*===========================================================================
	4Dベクトル
===========================================================================*/
struct Vector4f : public XMFLOAT4
{
	Vector4f() = default;
	Vector4f(float x, float y, float z,float w)
	{
		this->x = x; this->y = y; this->z = z; this->w = w;
	}
	//コンストラクタ
	Vector4f(const XMVECTOR& other) :XMFLOAT4() {
		XMVECTOR temp = other;
		XMStoreFloat4(this, temp);
	}

	Vector4f& operator +=(const Vector4f& other) { return *this = *this + other; }
	Vector4f& operator -=(const Vector4f& other) { return *this = *this - other; }
	inline BOOL operator == (const Vector4f&r) const { return x == r.x && y == r.y && z == r.z; }
	inline BOOL operator != (const Vector4f&r) const { return x != r.x || y != r.y || z != r.z; }
	inline XMVECTOR operator *(const float r) const { return Vector4f(x * r, y * r, z * r, w); }
	inline XMVECTOR operator /(const float r) const { return Vector4f(x / r, y / r, z / r, w); }

	//// ベクトルの内積
	//float Dot(Vector4f In) { return x * In.x + y * In.y + z * In.z; }
	//// ベクトルの外積
	//Vector4f Cross(Vector4f In) { return Vector4f(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x); }
	//// ベクトルのスケーリング
	//Vector4f Scale(float Scale) { Vector4f Result = { x * Scale, y * Scale, z * Scale }; return Result; }

	//代入
	Vector4f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat4(this, temp);
		return *this;
	}
	Vector4f& operator=(const XMFLOAT4& other) {
		this->x = other.x; this->y = other.y; this->z = other.z; this->w = other.w;
		return *this;
	}
	//キャスト
	operator XMVECTOR() const {
		return XMLoadFloat4(this);
	}
	//長さ
	float Length() const {
		return (static_cast<Vector4f>(XMVector4Length(XMVECTOR(*this)))).x;
	}
	//正規化
	void Normalize() {
		*this = XMVector4Normalize(XMVECTOR(*this));
	}
};
#endif // !_VECTOR_H_

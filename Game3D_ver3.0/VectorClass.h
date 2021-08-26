/*===========================================================================
  [VectorClass.h]
	�x�N�g���N���X�Q
===========================================================================*/
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "main.h"
/*===========================================================================
	2D�x�N�g��
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

	//���
	Vector2f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat2(this, temp);
		return *this;
	}
	//�L���X�g
	operator XMVECTOR() const {
		return XMLoadFloat2(this);
	}
	//����
	float Length() const {
		return (static_cast<Vector2f>(XMVector2Length(XMVECTOR(*this)))).x;
	}
	//���K��
	void Normalize() {
		*this = XMVector2Normalize(XMVECTOR(*this));
	}
};
/*===========================================================================
	3D�x�N�g��
===========================================================================*/
struct Vector3f : public XMFLOAT3
{
	Vector3f() = default;
	Vector3f(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	//�R���X�g���N�^
	Vector3f(const XMVECTOR& other) :XMFLOAT3() {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
	}

	Vector3f& operator +=(const Vector3f& other) { return *this = *this + other; }
	Vector3f& operator -=(const Vector3f& other) { return *this = *this - other; }
	inline BOOL operator == (const Vector3f&r) const { return x == r.x && y == r.y && z == r.z; }
	inline BOOL operator != (const Vector3f&r) const { return x != r.x || y != r.y || z != r.z; }
	inline XMVECTOR operator *(const float r) const { return Vector3f(x * r, y * r, z * r); }
	inline XMVECTOR operator /(const float r) const { return Vector3f(x / r, y / r, z / r); }

	// �x�N�g���̓���
	float Dot(Vector3f In) { return x * In.x + y * In.y + z * In.z; }
	// �x�N�g���̊O��
	Vector3f Cross(Vector3f In) { return Vector3f(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x); }
	// �x�N�g���̃X�P�[�����O
	Vector3f Scale(float Scale) { Vector3f Result = { x * Scale, y * Scale, z * Scale }; return Result; }

	//���
	Vector3f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
		return *this;
	}
	Vector3f& operator=(const XMFLOAT3& other) {
		this->x = other.x; this->y = other.y; this->z = other.z;
		return *this;
	}
	XMFLOAT3& operator=(const Vector3f& other) {
		XMFLOAT3 f3 = XMFLOAT3(other.x, other.y, other.z);
		return f3;
	}
	//�L���X�g
	operator XMVECTOR() const {
		return XMLoadFloat3(this);
	}
	//����
	float Length() const {
		return (static_cast<Vector3f>(XMVector3Length(XMVECTOR(*this)))).x;
	}
	//���K��
	void Normalize() {
		*this = XMVector3Normalize(XMVECTOR(*this));
	}
};
/*===========================================================================
	4D�x�N�g��
===========================================================================*/
struct Vector4f : public XMFLOAT4
{
	Vector4f() = default;
	Vector4f(float x, float y, float z,float w)
	{
		this->x = x; this->y = y; this->z = z; this->w = w;
	}
	//�R���X�g���N�^
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

	//// �x�N�g���̓���
	//float Dot(Vector4f In) { return x * In.x + y * In.y + z * In.z; }
	//// �x�N�g���̊O��
	//Vector4f Cross(Vector4f In) { return Vector4f(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x); }
	//// �x�N�g���̃X�P�[�����O
	//Vector4f Scale(float Scale) { Vector4f Result = { x * Scale, y * Scale, z * Scale }; return Result; }

	//���
	Vector4f& operator=(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat4(this, temp);
		return *this;
	}
	Vector4f& operator=(const XMFLOAT4& other) {
		this->x = other.x; this->y = other.y; this->z = other.z; this->w = other.w;
		return *this;
	}
	//�L���X�g
	operator XMVECTOR() const {
		return XMLoadFloat4(this);
	}
	//����
	float Length() const {
		return (static_cast<Vector4f>(XMVector4Length(XMVECTOR(*this)))).x;
	}
	//���K��
	void Normalize() {
		*this = XMVector4Normalize(XMVECTOR(*this));
	}
};
#endif // !_VECTOR_H_

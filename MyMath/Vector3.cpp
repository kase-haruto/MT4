#include "Vector3.h"

/* c++ */
#include <algorithm>
#include <cmath>

float Vector3::Length()const{
	return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::Normalize()const{
	float length = Length();
	return Vector3(x / length, y / length, z / length);
}

Vector3 Vector3::Normalized() const{
	float length = std::sqrt(x * x + y * y + z * z);
	// ゼロ除算を防ぐためのチェック
	if (length == 0.0f) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(x / length, y / length, z / length);
}


Vector3 Vector3::Cross(const Vector3& v0, const Vector3& v1){
	return {
	  v0.y * v1.z - v0.z * v1.y,
	  v0.z * v1.x - v0.x * v1.z,
	  v0.x * v1.y - v0.y * v1.x
	};
}

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

Vector3 Vector3::Lerp(const Vector3& v1, const Vector3& v2, float t){

	return Vector3(
		v1.x + t * (v2.x - v1.x),
		v1.y + t * (v2.y - v1.y),
		v1.z + t * (v2.z - v1.z)
	);
}

//乗算
Vector3 Vector3::operator*(const float& scalar) const{
	float newX = x * scalar;
	float newY = y * scalar;
	float newZ = z * scalar;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator*=(const float& scalar){
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return Vector3(x, y, z);
}

Vector3 Vector3::operator*(const Vector3& other) const{
	float newX = x * other.x;
	float newY = y * other.y;
	float newZ = z * other.z;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator*=(const Vector3& other){
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return Vector3(x, y, z);
}

Vector3 operator*(float scalar, const Vector3& vec){
	return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}



//除算
Vector3 Vector3::operator/(const float& scalar) const{
	float newX = x / scalar;
	float newY = y / scalar;
	float newZ = z / scalar;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator/=(const float& scalar){
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return Vector3(x, y, z);
}

Vector3 Vector3::operator/(const Vector3& other) const{
	float newX = x / other.x;
	float newY = y / other.y;
	float newZ = z / other.z;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator/=(const Vector3& other){
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return Vector3(x, y, z);
}

Vector3 operator/(float scalar, const Vector3& vec){
	return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}


// ベクトルの加算
Vector3 Vector3::operator+(const float& scalar) const{
	float newX = x + scalar;
	float newY = y + scalar;
	float newZ = z + scalar;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator+=(const float& scalar){
	x += scalar;
	y += scalar;
	z += scalar;
	return Vector3(x, y, z);
}

Vector3 Vector3::operator+(const Vector3& other) const{
	float newX = x + other.x;
	float newY = y + other.y;
	float newZ = z + other.z;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator+=(const Vector3& other){
	x += other.x;
	y += other.y;
	z += other.z;
	return Vector3(x, y, z);
}

Vector3 operator+(float scalar, const Vector3& vec){
	return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

// ベクトルの減算
Vector3 Vector3::operator-(const float& scalar) const{
	float newX = x - scalar;
	float newY = y - scalar;
	float newZ = z - scalar;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator-=(const float& scalar){
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return Vector3(x, y, z);
}

Vector3 Vector3::operator-(const Vector3& other) const{
	float newX = x - other.x;
	float newY = y - other.y;
	float newZ = z - other.z;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator-=(const Vector3& other){
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return Vector3(x, y, z);
}


Vector3 operator-(float scalar, const Vector3& vec){
	return Vector3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}
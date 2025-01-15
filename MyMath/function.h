#pragma once



#include <cmath>

struct Vector3;
struct  Matrix4x4;
// ベクトルの長さを測る
float Length(const Vector3& v);

// ベクトルを正規化する
Vector3 Normalize(const Vector3& v);

// ベクトルの外積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// ベクトルの内積
float Dot(const Vector3& v1, const Vector3& v2);
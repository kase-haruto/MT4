#include "function.h"

#include "Vector3.h"
#include "Matrix4x4.h"

float Length(const Vector3& v){
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// ベクトルを正規化する
Vector3 Normalize(const Vector3& v){
    float length = Length(v);
    return Vector3(v.x / length, v.y / length, v.z / length);
}

// ベクトルの外積
Vector3 Cross(const Vector3& v1, const Vector3& v2){
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

// ベクトルの内積
float Dot(const Vector3& v1, const Vector3& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
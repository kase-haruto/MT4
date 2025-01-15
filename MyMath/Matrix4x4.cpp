#include "Matrix4x4.h"

#include "Vector3.h"

/* lib */
#include<cmath>
#include <numbers>


float cot(float angle){
	return 1 / std::tan(angle);
}

Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& m1, const Matrix4x4& m2){
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k){
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

Matrix4x4 Matrix4x4::MakeIdentity(){
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			if (i == j){
				result.m[i][j] = 1.0f; // 対角成分は1
			} else{
				result.m[i][j] = 0.0f; // 対角以外の成分は0
			}
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& mat){
	Matrix4x4 result;

	//行列式を求める
#pragma region 行列式
	float bottom =
		mat.m[0][0] * mat.m[1][1] * mat.m[2][2] * mat.m[3][3] +
		mat.m[0][0] * mat.m[1][2] * mat.m[2][3] * mat.m[3][1] +
		mat.m[0][0] * mat.m[1][3] * mat.m[2][1] * mat.m[3][2] -

		mat.m[0][0] * mat.m[1][3] * mat.m[2][2] * mat.m[3][1] -
		mat.m[0][0] * mat.m[1][2] * mat.m[2][1] * mat.m[3][3] -
		mat.m[0][0] * mat.m[1][1] * mat.m[2][3] * mat.m[3][2] -

		mat.m[0][1] * mat.m[1][0] * mat.m[2][2] * mat.m[3][3] -
		mat.m[0][2] * mat.m[1][0] * mat.m[2][3] * mat.m[3][1] -
		mat.m[0][3] * mat.m[1][0] * mat.m[2][1] * mat.m[3][2] +

		mat.m[0][3] * mat.m[1][0] * mat.m[2][2] * mat.m[3][1] +
		mat.m[0][2] * mat.m[1][0] * mat.m[2][1] * mat.m[3][3] +
		mat.m[0][1] * mat.m[1][0] * mat.m[2][3] * mat.m[3][2] +

		mat.m[0][1] * mat.m[1][2] * mat.m[2][0] * mat.m[3][3] +
		mat.m[0][2] * mat.m[1][3] * mat.m[2][0] * mat.m[3][1] +
		mat.m[0][3] * mat.m[1][1] * mat.m[2][0] * mat.m[3][2] -

		mat.m[0][3] * mat.m[1][2] * mat.m[2][0] * mat.m[3][1] -
		mat.m[0][2] * mat.m[1][1] * mat.m[2][0] * mat.m[3][3] -
		mat.m[0][1] * mat.m[1][3] * mat.m[2][0] * mat.m[3][2] -

		mat.m[0][1] * mat.m[1][2] * mat.m[2][3] * mat.m[3][0] -
		mat.m[0][2] * mat.m[1][3] * mat.m[2][1] * mat.m[3][0] -
		mat.m[0][3] * mat.m[1][1] * mat.m[2][2] * mat.m[3][0] +

		mat.m[0][3] * mat.m[1][2] * mat.m[2][1] * mat.m[3][0] +
		mat.m[0][2] * mat.m[1][1] * mat.m[2][3] * mat.m[3][0] +
		mat.m[0][1] * mat.m[1][3] * mat.m[2][2] * mat.m[3][0];
#pragma endregion

	float determinant = 1 / bottom;

	//逆行列を求める
#pragma region 1行目
	//======================================================
	result.m[0][0] =
		(mat.m[1][1] * mat.m[2][2] * mat.m[3][3] +
		 mat.m[1][2] * mat.m[2][3] * mat.m[3][1] +
		 mat.m[1][3] * mat.m[2][1] * mat.m[3][2] -
		 mat.m[1][3] * mat.m[2][2] * mat.m[3][1] -
		 mat.m[1][2] * mat.m[2][1] * mat.m[3][3] -
		 mat.m[1][1] * mat.m[2][3] * mat.m[3][2]) * determinant;

	result.m[0][1] =
		(-mat.m[0][1] * mat.m[2][2] * mat.m[3][3] -
		 mat.m[0][2] * mat.m[2][3] * mat.m[3][1] -
		 mat.m[0][3] * mat.m[2][1] * mat.m[3][2] +
		 mat.m[0][3] * mat.m[2][2] * mat.m[3][1] +
		 mat.m[0][2] * mat.m[2][1] * mat.m[3][3] +
		 mat.m[0][1] * mat.m[2][3] * mat.m[3][2]) * determinant;

	result.m[0][2] =
		(mat.m[0][1] * mat.m[1][2] * mat.m[3][3] +
		 mat.m[0][2] * mat.m[1][3] * mat.m[3][1] +
		 mat.m[0][3] * mat.m[1][1] * mat.m[3][2] -
		 mat.m[0][3] * mat.m[1][2] * mat.m[3][1] -
		 mat.m[0][2] * mat.m[1][1] * mat.m[3][3] -
		 mat.m[0][1] * mat.m[1][3] * mat.m[3][2]) * determinant;

	result.m[0][3] =
		(-mat.m[0][1] * mat.m[1][2] * mat.m[2][3] -
		 mat.m[0][2] * mat.m[1][3] * mat.m[2][1] -
		 mat.m[0][3] * mat.m[1][1] * mat.m[2][2] +
		 mat.m[0][3] * mat.m[1][2] * mat.m[2][1] +
		 mat.m[0][2] * mat.m[1][1] * mat.m[2][3] +
		 mat.m[0][1] * mat.m[1][3] * mat.m[2][2]) * determinant;
#pragma endregion

#pragma region 2行目
	//======================================================
	result.m[1][0] =
		(-mat.m[1][0] * mat.m[2][2] * mat.m[3][3] -
		 mat.m[1][2] * mat.m[2][3] * mat.m[3][0] -
		 mat.m[1][3] * mat.m[2][0] * mat.m[3][2] +
		 mat.m[1][3] * mat.m[2][2] * mat.m[3][0] +
		 mat.m[1][2] * mat.m[2][0] * mat.m[3][3] +
		 mat.m[1][0] * mat.m[2][3] * mat.m[3][2]) * determinant;

	result.m[1][1] =
		(mat.m[0][0] * mat.m[2][2] * mat.m[3][3] +
		 mat.m[0][2] * mat.m[2][3] * mat.m[3][0] +
		 mat.m[0][3] * mat.m[2][0] * mat.m[3][2] -
		 mat.m[0][3] * mat.m[2][2] * mat.m[3][0] -
		 mat.m[0][2] * mat.m[2][0] * mat.m[3][3] -
		 mat.m[0][0] * mat.m[2][3] * mat.m[3][2]) * determinant;

	result.m[1][2] =
		(-mat.m[0][0] * mat.m[1][2] * mat.m[3][3] -
		 mat.m[0][2] * mat.m[1][3] * mat.m[3][0] -
		 mat.m[0][3] * mat.m[1][0] * mat.m[3][2] +
		 mat.m[0][3] * mat.m[1][2] * mat.m[3][0] +
		 mat.m[0][2] * mat.m[1][0] * mat.m[3][3] +
		 mat.m[0][0] * mat.m[1][3] * mat.m[3][2]) * determinant;

	result.m[1][3] =
		(mat.m[0][0] * mat.m[1][2] * mat.m[2][3] +
		 mat.m[0][2] * mat.m[1][3] * mat.m[2][0] +
		 mat.m[0][3] * mat.m[1][0] * mat.m[2][2] -
		 mat.m[0][3] * mat.m[1][2] * mat.m[2][0] -
		 mat.m[0][2] * mat.m[1][0] * mat.m[2][3] -
		 mat.m[0][0] * mat.m[1][3] * mat.m[2][2]) * determinant;
#pragma endregion

#pragma region 3行目
	//======================================================
	result.m[2][0] =
		(mat.m[1][0] * mat.m[2][1] * mat.m[3][3] +
		 mat.m[1][1] * mat.m[2][3] * mat.m[3][0] +
		 mat.m[1][3] * mat.m[2][0] * mat.m[3][1] -
		 mat.m[1][3] * mat.m[2][1] * mat.m[3][0] -
		 mat.m[1][1] * mat.m[2][0] * mat.m[3][3] -
		 mat.m[1][0] * mat.m[2][3] * mat.m[3][1]) * determinant;

	result.m[2][1] =
		(-mat.m[0][0] * mat.m[2][1] * mat.m[3][3] -
		 mat.m[0][1] * mat.m[2][3] * mat.m[3][0] -
		 mat.m[0][3] * mat.m[2][0] * mat.m[3][1] +
		 mat.m[0][3] * mat.m[2][1] * mat.m[3][0] +
		 mat.m[0][1] * mat.m[2][0] * mat.m[3][3] +
		 mat.m[0][0] * mat.m[2][3] * mat.m[3][1]) * determinant;

	result.m[2][2] =
		(mat.m[0][0] * mat.m[1][1] * mat.m[3][3] +
		 mat.m[0][1] * mat.m[1][3] * mat.m[3][0] +
		 mat.m[0][3] * mat.m[1][0] * mat.m[3][1] -
		 mat.m[0][3] * mat.m[1][1] * mat.m[3][0] -
		 mat.m[0][1] * mat.m[1][0] * mat.m[3][3] -
		 mat.m[0][0] * mat.m[1][3] * mat.m[3][1]) * determinant;

	result.m[2][3] =
		(-mat.m[0][0] * mat.m[1][1] * mat.m[2][3] -
		 mat.m[0][1] * mat.m[1][3] * mat.m[2][0] -
		 mat.m[0][3] * mat.m[1][0] * mat.m[2][1] +
		 mat.m[0][3] * mat.m[1][1] * mat.m[2][0] +
		 mat.m[0][1] * mat.m[1][0] * mat.m[2][3] +
		 mat.m[0][0] * mat.m[1][3] * mat.m[2][1]) * determinant;
#pragma endregion

#pragma region 4行目
	//======================================================
	result.m[3][0] =
		(-mat.m[1][0] * mat.m[2][1] * mat.m[3][2] -
		 mat.m[1][1] * mat.m[2][2] * mat.m[3][0] -
		 mat.m[1][2] * mat.m[2][0] * mat.m[3][1] +
		 mat.m[1][2] * mat.m[2][1] * mat.m[3][0] +
		 mat.m[1][1] * mat.m[2][0] * mat.m[3][2] +
		 mat.m[1][0] * mat.m[2][2] * mat.m[3][1]) * determinant;

	result.m[3][1] =
		(mat.m[0][0] * mat.m[2][1] * mat.m[3][2] +
		 mat.m[0][1] * mat.m[2][2] * mat.m[3][0] +
		 mat.m[0][2] * mat.m[2][0] * mat.m[3][1] -
		 mat.m[0][2] * mat.m[2][1] * mat.m[3][0] -
		 mat.m[0][1] * mat.m[2][0] * mat.m[3][2] -
		 mat.m[0][0] * mat.m[2][2] * mat.m[3][1]) * determinant;

	result.m[3][2] =
		(-mat.m[0][0] * mat.m[1][1] * mat.m[3][2] -
		 mat.m[0][1] * mat.m[1][2] * mat.m[3][0] -
		 mat.m[0][2] * mat.m[1][0] * mat.m[3][1] +
		 mat.m[0][2] * mat.m[1][1] * mat.m[3][0] +
		 mat.m[0][1] * mat.m[1][0] * mat.m[3][2] +
		 mat.m[0][0] * mat.m[1][2] * mat.m[3][1]) * determinant;

	result.m[3][3] =
		(mat.m[0][0] * mat.m[1][1] * mat.m[2][2] +
		 mat.m[0][1] * mat.m[1][2] * mat.m[2][0] +
		 mat.m[0][2] * mat.m[1][0] * mat.m[2][1] -
		 mat.m[0][2] * mat.m[1][1] * mat.m[2][0] -
		 mat.m[0][1] * mat.m[1][0] * mat.m[2][2] -
		 mat.m[0][0] * mat.m[1][2] * mat.m[2][1]) * determinant;
#pragma endregion

	return result;
}

Matrix4x4 Matrix4x4::MakeRotateAxisAngle(const Vector3& axis, float angle){
	// 軸ベクトルを正規化
	Vector3 nAxis = axis.Normalized();
	float x = nAxis.x;
	float y = nAxis.y;
	float z = nAxis.z;

	// コサインとサイン、そして補助値の計算
	float c = std::cos(angle);
	float s = std::sin(angle);
	float t = 1.0f - c;

	// 回転行列の要素を計算 (列優先で設定)
	Matrix4x4 result;

	result.m[0][0] = t * x * x + c;
	result.m[1][0] = t * x * y - s * z;
	result.m[2][0] = t * x * z + s * y;
	result.m[3][0] = 0.0f;

	result.m[0][1] = t * x * y + s * z;
	result.m[1][1] = t * y * y + c;
	result.m[2][1] = t * y * z - s * x;
	result.m[3][1] = 0.0f;

	result.m[0][2] = t * x * z - s * y;
	result.m[1][2] = t * y * z + s * x;
	result.m[2][2] = t * z * z + c;
	result.m[3][2] = 0.0f;

	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

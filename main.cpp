#include <Novice.h>

#include "MyMath/Vector3.h"
#include "MyMath/Matrix4x4.h"

#include <string>

const char kWindowTitle[] = "LE2A_08_カセ_ハルト";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& mat, const std::string& label){
	Novice::ScreenPrintf(x - 20, y - 20, "%s", label.c_str());

	for (int row = 0; row < 4; ++row){
		for (int col = 0; col < 4; ++col){
			Novice::ScreenPrintf(x + col * kColumnWidth, y + row * kRowHeight, "%.3f", mat.m[row][col]);
		}
	}
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0){
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);


		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0){
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

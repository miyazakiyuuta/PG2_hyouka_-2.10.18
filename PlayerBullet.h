#pragma once
#include "Vector2.h"

class PlayerBullet
{
public:

	//コンストラクタ
	PlayerBullet();

	/*メンバ関数*/
	//更新
	void Update();
	//描画
	void Draw();
	//当たり判定
	int IsHit(Vector2 pos, float radius);

	/*アクセッサ*/

	//Get
	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	int GetIsShot() { return isShot_; }

	//Set
	void SetPos(Vector2 pos) { pos_ = pos; }
	void SetIsShot(int isShot) { isShot_ = isShot; }

private:
	/*メンバ変数*/
	Vector2 pos_; //中心座標
	float radius_; //半径
	float speed_; //速さ
	int isShot_; //発射されているかのフラグ

};


#pragma once
#include "Vector2.h"
class EnemyBullet
{
public:
	//コンストラクタ
	EnemyBullet();
	/*メンバ関数*/
	//更新
	void Update();
	//描画
	void Draw();

	/*アクセッサ*/

	//Get
	Vector2 GetPos() { return pos_; }
	Vector2 GetStart() { return start_; }
	Vector2 GetEnd() { return end_; }
	float GetRadius_() { return radius_; }
	int GetIsAlive() { return isAlive_; }
	int GetIsShot() { return isShot_; }

	//Set
	void SetPos(Vector2 pos) { pos_ = pos; }
	void SetStart(Vector2 start) { start_ = start; }
	void SetAuxiliary(Vector2 auxiliary) { auxiliary_ = auxiliary; }
	void SetEnd(Vector2 end) { end_ = end; }
	void SetIsAlive(int isAlive) { isAlive_ = isAlive; }
	void SetIsShot(int isShot) { isShot_ = isShot; }

private:
	Vector2 pos_;
	Vector2 start_;
	Vector2 auxiliary_;
	Vector2 end_;
	float radius_;
	int isAlive_;
	int isShot_;
	float t_;
	float easedT_;
};


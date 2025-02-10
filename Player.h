#pragma once
#include "Vector2.h"

class PlayerBullet; //前方宣言

class Player
{
public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	/*メンバ関数*/
	//更新
	void Update(char keys[]);
	//描画
	void Draw();
	//当たり判定
	int IsHit(Vector2 pos, float radius);

	/*アクセッサ*/
	//Get
	Vector2 GetPos() { return pos_; }
	int GetLife() { return life_; }
	int GetIsAlive() { return isAlive_; }
	int GetKMaxBullet() { return kMaxBullet_; }
	PlayerBullet* GetBullet(int i) { return bullet_[i]; }

private:

	/*メンバ変数*/

	Vector2 pos_; //中心座標
	Vector2 move_; //動く方向 
	float speed_; //速さ(moveに乗算する値)
	float radius_; //半径
	const int kMaxLife_ = 5;
	int life_; //体力
	int isAlive_; //生きているかのフラグ
	const int kInvincibleTime_ = 60; //無敵時間の最大(初期値)
	int invincibleTimer_; //無敵時間のタイマー
	
	const int kBulletCoolTime_ = 5; //弾のクールタイム(初期値)
	int bulletCoolTimer_; //弾のクールタイマー
	static const int kMaxBullet_ = 20; //弾の最大数
	PlayerBullet* bullet_[kMaxBullet_];
};


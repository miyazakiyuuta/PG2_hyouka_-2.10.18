#pragma once
#include "Vector2.h"

class EnemyBullet; //前方宣言

class Enemy
{
public:

	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();

	/*メンバ関数*/
	//更新
	void Update();
	//描画
	void Draw();

	/*アクセッサ*/

	//Get
	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	int GetHp() { return hp_; }
	int GetIsAlive() { return isAlive_; }
	int GetKMaxBullet() { return kMaxBullet_; }
	int GetIsAttack() { return isAttack_; }
	EnemyBullet* GetBullet(int i) { return bullet_[i]; }

	//Set
	void SetHp(int hp) { hp_ = hp; }
	void SetBulletEnd(int i, Vector2 end);
	void SetBulletIsShot(int i, int isShot);
	void SetBulletIsAlive(int i, int isAlive);

private:

	/*メンバ変数*/
	Vector2 pos_; //中心座標
	float radius_; //半径
	const int kMaxHp_ = 500;
	int hp_; //体力
	int isAlive_; //生きているかのフラグ

	int bulletFalseCount_; //bulletのfalseカウント
	int isAttack_; //攻撃フラグ
	float bulletT_; //スタート位置にいくまでのイージングに使うt
	float bulletEasedT_;
	static const int kMaxBullet_ = 4; //弾の最大数
	EnemyBullet* bullet_[kMaxBullet_];
};


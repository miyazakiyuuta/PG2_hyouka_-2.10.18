#pragma once

//前方宣言
class Player;
class Enemy;

class Scene
{
public:

	//コンストラクタ
	Scene();
	//デストラクタ
	~Scene();

	/*メンバ関数*/
	//更新
	void Update(char keys[],char preKeys[]);
	//描画
	void Draw();

private:

	/*メンバ変数*/

	enum SceneChange
	{
		GAMETITLE,
		GAMEPLAY,
		GAMEOVER,
		GAMECLEAR
	};

	int scene_;
	int isSceneChange_;
	int darkenAlpha_;

	Player* player_;

	Enemy* enemy_;


};


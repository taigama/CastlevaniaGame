#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"

#define REDBAT 1
#define BLUEBAT 2
#define GHOUL 3
#define FISH 4
#define PANTHER 5
#define ENEMYFIRE 6
#define VAMBAT 7
#define MEDUSA 8
#define SNAKE 9

class Enemy :
	public GameObject

{
public:
	////
	int healthMax;
	int health;
	int enemyType;

	bool isFreezed;
	float timerFreeze;


	Sprite *spriteLeft;
	Sprite *spriteRight;
	Sprite *spriteVamBat;
	Sprite *spriteMedusa;
	Enemy();
	Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager);
	virtual ~Enemy();

	//ham ao ke thua tu game object
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool _IsRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void TakeDamage(int damage);
	//ham ao moi tao
	virtual void CheckActive();
	void TakeDamage(GameObject* actor, int damage);
	static Enemy* CreateEnemy(int type, int X, int Y, LPD3DXSPRITE _SpriteHandler,
		World *_manager);
	bool CheckGroundCollision(World *manager, const float _DeltaTime);

	// trả về tỉ lệ máu / 16
	virtual int HealthDot() { return 0; };
	
	void Freeze(float _Time);
};
#endif // !_ENEMY_H_


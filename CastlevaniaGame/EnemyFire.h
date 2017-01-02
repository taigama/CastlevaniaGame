#ifndef _ENEMYFIRE_H_
#define _ENEMYFIRE_H_

#include "Enemy.h"

class EnemyFire :
	public Enemy

{
public:
	bool isRight;
	EnemyFire();
	EnemyFire(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~EnemyFire();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	void Init(int _X, int _Y, bool _isRight);

	virtual void CheckActive();
};
#endif // !_ENEMYFIRE_H_


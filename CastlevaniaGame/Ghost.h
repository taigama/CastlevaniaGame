#ifndef _GHOST_H_
#define _GHOST_H_

#include "Enemy.h"

class Ghost :
	public Enemy

{
public:
	Ghost() {};
	Ghost(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Ghost() {};
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void TakeDamage(int damage);
};
#endif // !_ENEMYFIRE_H_


#ifndef _GHOUL_H_
#define _GHOUL_H_

#include "Enemy.h"

class Ghoul :
	public Enemy

{
public:
	Ghoul();
	Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Ghoul();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_GHOUL_H_


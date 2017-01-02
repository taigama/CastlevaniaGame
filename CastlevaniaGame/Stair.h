
#ifndef _STAIR_H_
#define _STAIR_H_

#include "GameObject.h"

class Stair :
	public GameObject

{
public:

	bool isBreakable;
	int stairType;
	Stair(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type);
	Stair(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Stair();
	virtual void Init(int _X, int _Y);
	virtual void Update(const int &_deltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};
#endif // !_STAIR_H_



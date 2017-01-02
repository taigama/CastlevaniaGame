#pragma once
#ifndef _BIGHEART_
#define _BIGHEART_

#include "Item.h"

class BigHeart :
	public Item

{
public:
	BigHeart();
	BigHeart(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BigHeart();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_BIGHEART_


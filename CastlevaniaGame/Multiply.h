#pragma once
#ifndef _MULTIPLY_
#define _MULTIPLY_

#include "Item.h"

class Multiply :
	public Item

{
public:
	Multiply();
	Multiply(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Multiply();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_MULTIPLY_


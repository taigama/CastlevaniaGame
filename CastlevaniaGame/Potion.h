#pragma once
#ifndef _POTION_
#define _POTION_

#include "Item.h"

class Potion :
	public Item

{
public:
	Potion();
	Potion(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Potion();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_POTION_


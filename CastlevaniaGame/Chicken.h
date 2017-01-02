#pragma once
#ifndef _CHICKEN_
#define _CHICKEN_

#include "Item.h"

class Chicken :
	public Item

{
public:
	Chicken();
	Chicken(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Chicken();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);

};
#endif // !_CHICKEN_


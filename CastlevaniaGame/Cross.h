#pragma once
#ifndef _CROSS_
#define _CROSS_

#include "Item.h"

class Cross :
	public Item

{
public:
	Sprite* flash;
	Cross();
	Cross(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Cross();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_CROSS_


#pragma once
#ifndef _MONEYBAG_
#define _MONEYBAG_

#include "Item.h"

class MoneyBag :
	public Item

{
public:
	MoneyBag();
	MoneyBag(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~MoneyBag();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);

	virtual void Init(int _X, int _Y, int _level);
};
#endif // !_MONEYBAG_


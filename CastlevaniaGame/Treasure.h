#pragma once
#ifndef _TREASURE_
#define _TREASURE_

#include "Item.h"

class Treasure :
	public Item

{
public:
	
	Treasure();
	Treasure(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Treasure();

	
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);

	virtual void Init(int _X, int _Y, int _type);
};
#endif // !_MONEYBAG_


#pragma once
#ifndef _CRYSTAL_
#define _CRYSTAL_

#include "Item.h"

class Crystal :
	public Item

{
public:
	Crystal();
	Crystal(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Crystal();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);

};
#endif // !_CRYSTAL_


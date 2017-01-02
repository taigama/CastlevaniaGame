#pragma once
#ifndef _WHIPUPGRADE_
#define _WHIPUPGRADE_

#include "Item.h"

class WhipUpgrade :
	public Item

{
public:
	WhipUpgrade();
	WhipUpgrade(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~WhipUpgrade();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_WHIPUPGRADE_


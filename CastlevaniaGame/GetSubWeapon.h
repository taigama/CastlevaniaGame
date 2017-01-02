#pragma once
#ifndef _GETSUBWEAPON_
#define _GETSUBWEAPON_

#include "Item.h"

class GetSubWeapon :
	public Item

{
public:
	Sprite* weaponSprite;
	GetSubWeapon();
	GetSubWeapon(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~GetSubWeapon();

	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y,int type);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
};
#endif // !_GetSubWeapon_


#pragma once
#ifndef _HEART_
#define _HEART_

#include "Item.h"
#include "GroupObject.h"
#include "Ground.h"
#include "GameObject.h"
class Heart :
	public Item

{
public:
	float a;
	Heart();
	Heart(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Heart();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);

};
#endif // !_HEART_


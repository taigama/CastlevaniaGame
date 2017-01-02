#ifndef _STANDITEM_H_
#define _STANDITEM_H_

#include "Zone.h"

class StandItem :
	public Zone
{
	// will spawn at this coordinate
	int triggerX;
	int triggerY;

	// điều kiện?
	bool needCrouch;

	// để cho việc tạo item
	int itemType;
	float timeRequired;
	float timePending;
	// dùng cấp sprite cho item
	LPD3DXSPRITE spriteHandler;

public:
	virtual void Render();

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int _triggerX, int _triggerY,	// show item chỗ này
		int _itemType, int _time, int _needCrouch);	// item rớt & điều kiện
	virtual void Collision(Player *actor, const float &_DeltaTime);


	StandItem(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~StandItem();
};

#endif
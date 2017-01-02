#ifndef _DEADZONE_H_
#define _DEADZONE_H_

#include "Zone.h"

class DeadZone :
	public Zone
{
	// will spawn at this coordinate
	int triggerX;
	int triggerY;

	// Zone hay grinder
	bool isGrinder;

	// nếu là grinder -> lên xuống bao nhiêu
	int iStack;
	// trạng thái grinder
	int status;

public:
	virtual void Update(const float &_DeltaTime);
	virtual void Render();

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int _Stack, int rubbish1,	
		int rubbish2, int rubbish3, int rubbish4);
	virtual void Collision(Player *actor, const float &_DeltaTime);


	DeadZone(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type);
	~DeadZone();
};

#endif
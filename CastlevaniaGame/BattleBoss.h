#ifndef _BATTLEBOSS_H_
#define _BATTLEBOSS_H_

#include "Zone.h"

class BattleBoss :
	public Zone
{

public:

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int rubbish1, int rubbish2,
		int rubbish3, int rubbish4, int rubbish5);
	virtual void Collision(Player *actor, const float &_DeltaTime);


	BattleBoss(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BattleBoss();
};

#endif
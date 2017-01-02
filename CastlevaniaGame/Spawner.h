#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "Zone.h"
// spawner = 6

class Spawner :
	public Zone
{
	// will spawn at this coordinate
	int triggerX;
	int triggerY;

	// dùng trong việc tạo enemy
	LPD3DXSPRITE spriteHandler;
	int typeEnemy;
	int numberEnemy;

	// các enemy
	Enemy** objects;
	// các thời gian kiểm soát
	float* timers;
	float timerRespawn;

public:
	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
	int _TypeEnemy, int _Count,
	int rubbish1, int rubbish2, int rubbish3);
	virtual void Collision(Player *actor, const float &_DeltaTime);


	Spawner(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Spawner();
};

#endif
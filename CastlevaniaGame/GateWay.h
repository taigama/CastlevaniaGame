#ifndef _GATEWAY_H_
#define _GATEWAY_H_

#include "Zone.h"
class GateWay :
	public Zone
{
	// will mo to this coordinate
	int triggerX;
	int triggerY;

	//	change camera to this, no need to change camX because it follows the player
	int camXLeft;
	int camXRight;
	int camY;

public:
	virtual void Render();

	virtual void Init(int _top, int _bottom, int _left, int _right,
		int _triggerX, int _triggerY, int _camXLeft, int _camXRight, int _camY);
	virtual void Collision(Player *actor, const float &_DeltaTime);


	GateWay(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~GateWay();
};

#endif
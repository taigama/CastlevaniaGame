#ifndef _ZONE_H_
#define _ZONE_H_

#include "GameObject.h"
#define ZONE_GATEWAY 1

class Zone :
	public GameObject

{
public:
	int typeZone;

	//Zone();
	Zone(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Zone();
	// ----- K_1.9
	void Init(int _X, int _Y, int _Width, int _Height);
	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int _triggerX, int _triggerY,	// trigger tại vị trí này
		int param7, int param8, int param9);


	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *actor, const float &_DeltaTime);
};
#endif // !_ZONE_H_




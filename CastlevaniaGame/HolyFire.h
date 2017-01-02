#ifndef _HOLYFIRE_H_
#define _HOLYFIRE_H_


#include "Projectile.h"
#define LIFE_TIME 2.0f
class HolyFire :
	public Projectile
{
public:

	Sprite *spriteLeft;
	Sprite *spriteRight;

	float timeActive;
	// constructor & destructor
	HolyFire(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~HolyFire();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void CollisionObject(float _DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif


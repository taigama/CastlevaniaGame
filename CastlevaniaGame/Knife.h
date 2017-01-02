#ifndef _KNIFE_H_
#define _KNIFE_H_


#include "Projectile.h"

class Knife :
	public Projectile
{
public:

	Sprite *spriteLeft;
	Sprite *spriteRight;

	// constructor & destructor
	Knife(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Knife();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void CollisionObject(float _DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif


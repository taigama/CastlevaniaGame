#ifndef _Boomerang_H_
#define _Boomerang_H_


#include "Projectile.h"
#define BOOM_ANIM_TIME 0.13f
class Boomerang :
	public Projectile
{
public:

	Sprite *spriteLeft;
	Sprite *spriteRight;
	bool isRight;
	bool isReverted;

	
	// constructor & destructor
	Boomerang(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Boomerang();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif

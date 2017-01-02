
#ifndef _HOLYWATER_H_
#define _HOLYWATER_H_


#include "Projectile.h"
#define BOOM_ANIM_TIME 0.13f
class HolyWater :
	public Projectile
{
public:

	Sprite *spriteLeft;
	Sprite *spriteRight;
	bool isRight;
	bool isReverted;
	// constructor & destructor
	HolyWater(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~HolyWater();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	void CollisionObject(float _DeltaTime);
};

#endif

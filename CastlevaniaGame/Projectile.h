#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_


#include "GameObject.h"

class Projectile :
	public GameObject
{
public:

	Sprite *spriteLeft;
	Sprite *spriteRight;
	int projectileType;
	int Damage;

	// constructor & destructor
	Projectile();
	Projectile(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Projectile();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	void CollisionObject(float _DeltaTime);
};

#endif


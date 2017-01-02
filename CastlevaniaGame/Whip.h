#ifndef _WHIP_H_
#define _WHIP_H_

#include "Projectile.h"

class Whip :
	public Projectile
{
public:

	Whip(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Whip();
	int whipLevel;
	int lvl3indexsprite;
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void CollisionObject(float _DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

};

#endif // !_WHIP_H_



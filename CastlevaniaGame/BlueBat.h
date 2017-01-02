#ifndef _BLUEBAT_H_
#define _BLUEBAT_H_

#include "Enemy.h"

class BlueBat :
	public Enemy

{
public:
	BlueBat();
	BlueBat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BlueBat();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
	bool isSleeping;
};
#endif // !_BLUEBAT_H_

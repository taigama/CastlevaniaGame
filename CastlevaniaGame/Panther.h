#ifndef _PANTHER_H_
#define _PANTHER_H_

#include "Enemy.h"

class Panther :
	public Enemy

{
public:
	bool isSleeping;
	bool hasJumped;
	bool isRight;
	Panther();
	Panther(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Panther();
	virtual void Init(int _X, int _Y);
	void Init(int _X, int _Y, bool _isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
	bool CheckGroundCollision(World * manager, const float _DeltaTime);
};
#endif // !_PANTHER_H_
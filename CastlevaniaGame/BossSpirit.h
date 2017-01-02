#ifndef _BOSSSPIRIT_
#define _BOSSSPIRIT_

#include "Effect.h"

class BossSpirit :
	public Effect

{
public:
	BossSpirit();
	BossSpirit(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BossSpirit();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();
};
#endif // !_BOSSSPIRIT_



#ifndef _HIT_
#define _HIT_

#include "Effect.h"

class Hit :
	public Effect

{
public:
	Hit();
	Hit(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Hit();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();
};
#endif // !_HIT_



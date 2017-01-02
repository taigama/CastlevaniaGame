#ifndef _SPIRIT_
#define _SPIRIT_

#include "Effect.h"

class Spirit :
	public Effect

{
public:
	Spirit();
	Spirit(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Spirit();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();
};
#endif // !_SPIRIT_



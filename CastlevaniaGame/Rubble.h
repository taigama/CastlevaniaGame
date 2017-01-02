#ifndef _RUBBLE_
#define _RUBBLE_

#include "Effect.h"

class Rubble :
	public Effect

{
public:
	Rubble();
	Rubble(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Rubble();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, int heso);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();

};
#endif // !_RUBBLE_



#ifndef _BUBBLE_
#define _BUBBLE_

#include "Effect.h"

class Bubble :
	public Effect

{
public:
	Bubble();
	Bubble(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Bubble();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, int heso);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();

};
#endif // !_BUBBLE_



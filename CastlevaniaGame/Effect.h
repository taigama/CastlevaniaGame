#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "GameObject.h"

class Effect :
	public GameObject

{
public:
	int effectType;
	float timeSurvive;
	int heso;
	Effect();
	Effect(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Effect();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, int heso);
	virtual void Update(const float &_deltaTime);
	virtual void Render();
	virtual void Destroy();
	static Effect* CreateEffect(int effectType, int X, int Y, int heso, LPD3DXSPRITE _SpriteHandler, World *_manager);
};
#endif // !_EFFECT_H_



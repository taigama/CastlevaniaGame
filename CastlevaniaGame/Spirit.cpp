#include "Spirit.h"

Spirit::Spirit() {}

Spirit::Spirit(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Effect(_SpriteHandler, _manager)
{
	effectType = EFFECT_SPIRIT;
}

Spirit :: ~Spirit()
{

}

void Spirit::Init(int _X, int _Y)
{
	Effect::Init(_X, _Y);
	sprite->Next(1, 2);
}

void Spirit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 0.5f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(1, 3);
			timerSprite = 0;
		}
	}
}

void Spirit::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Spirit::Destroy()
{
	isActive = false;
}


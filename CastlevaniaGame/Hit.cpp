#include "Hit.h"

Hit::Hit() {}

Hit::Hit(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Effect(_SpriteHandler, _manager)
{
	effectType = EFFECT_HIT;
}

Hit :: ~Hit()
{

}

void Hit::Init(int _X, int _Y)
{
	Effect::Init(_X, _Y);
	sprite->Next(0, 0);
}

void Hit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 0.5f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(0, 0);
			timerSprite = 0;
		}
	}
}

void Hit::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Hit::Destroy()
{
	isActive = false;
}


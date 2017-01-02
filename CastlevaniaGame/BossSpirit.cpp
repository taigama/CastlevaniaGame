#include "BossSpirit.h"

BossSpirit::BossSpirit() {}

BossSpirit::BossSpirit(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Effect(_SpriteHandler, _manager)
{
	effectType = EFFECT_BOSSSPIRIT;
}

BossSpirit :: ~BossSpirit()
{

}

void BossSpirit::Init(int _X, int _Y)
{
	Effect::Init(_X, _Y);
	sprite->Next(3, 4);
}

void BossSpirit::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 1.2f)
		isActive = false;
	if (isActive)
	{
		timerSprite += _deltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(1, 4);
			timerSprite = 0;
		}
	}
}

void BossSpirit::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void BossSpirit::Destroy()
{
	isActive = false;
}


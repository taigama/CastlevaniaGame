#include "Rubble.h"

Rubble::Rubble() {}

Rubble::Rubble(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Effect(_SpriteHandler, _manager)
{
	effectType = EFFECT_RUBBLE;
	velocityX = 30;
	velocityY = -200;
}

Rubble :: ~Rubble()
{

}

void Rubble::Init(int _X, int _Y)
{

}
void Rubble::Init(int _X, int _Y, int _heso)
{
	Effect::Init(_X, _Y);
	sprite->Next(5, 5);
	heso = _heso;
}

void Rubble::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	postX += velocityX * _deltaTime*heso*4;
	postY -= velocityY * _deltaTime;

	timerSprite += _deltaTime;

	if (timerSprite >= 0.2f)
	{
		velocityY += velocityX*velocityX / 5 ;
		sprite->Next(5, 5);
		timerSprite = 0;
	}
}

void Rubble::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Rubble::Destroy()
{
	isActive = false;
}


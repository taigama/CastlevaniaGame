#include "Bubble.h"

Bubble::Bubble() {}

Bubble::Bubble(LPD3DXSPRITE _SpriteHandler, World *_manager)
	:Effect(_SpriteHandler,_manager)
{
	effectType = EFFECT_BUBBLE;
	velocityX = 25;
	velocityY = -200;
}

Bubble :: ~Bubble()
{

}

void Bubble::Init(int _X, int _Y)
{
	
}
void Bubble::Init(int _X, int _Y, int _heso)
{
	Effect::Init(_X, _Y);
	sprite->Next(6, 6);
	heso = _heso;
}

void Bubble::Update(const float &_deltaTime)
{
	timeSurvive += _deltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	postX += velocityX * _deltaTime*heso;
	postY -= velocityY * _deltaTime;

	timerSprite += _deltaTime;

	if (timerSprite >= 0.2f)
	{
		velocityY += velocityX*velocityX/5 ;
		sprite->Next(6, 6);
		timerSprite = 0;
	}
}

void Bubble::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Bubble::Destroy()
{
	isActive = false;
}


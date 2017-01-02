#include "Effect.h"
#include "World.h"
Effect::Effect() {}

Effect::Effect(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = EFFECT_TYPE;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", 64, 64, 7, 6);
	timeSurvive = 0;
	timerSprite = 0;
	isActive = false;
}

Effect :: ~Effect()
{

}

void Effect::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;
}

void Effect::Init(int _X, int _Y, int heso)
{
	
}

void Effect::Update(const float &_deltaTime)
{
}

void Effect::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Effect::Destroy()
{
	
}

Effect * Effect::CreateEffect(int effectType, int X, int Y, int heso, LPD3DXSPRITE _SpriteHandler,
	World *_manager)
{
	Effect* effect = new Effect();
	switch (effectType)
	{
	case EFFECT_HIT:
		effect = new Hit(_SpriteHandler, _manager);
		effect->Init(X, Y);
		break;
	case EFFECT_SPIRIT:
		effect = new Spirit(_SpriteHandler, _manager);
		effect->Init(X, Y);
		break;
	case EFFECT_BOSSSPIRIT:
		effect= new BossSpirit(_SpriteHandler, _manager);
		effect->Init(X, Y);
		break;
	case EFFECT_BUBBLE:
		effect = new Bubble(_SpriteHandler, _manager);
		effect->Init(X, Y, heso);
		break;
	case EFFECT_RUBBLE:
		effect = new Rubble(_SpriteHandler, _manager);
		effect->Init(X, Y, heso);
		break;
	}
	return effect;
}


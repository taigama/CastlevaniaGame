#include "Head.h"
#include "Sprite.h"
#include "World.h"


Head::Head() {}

Head::Head(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(10, -10, -10, 10);
	enemyType = HEAD;
	spriteLeft->_Index = 23;
	spriteRight->_Index = 23;
}

Head :: ~Head()
{

}

void Head::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	postY = _Y;
	postX = _X;
	a = 0;
	if (manager->Simon->isRight)
		velocityX = -150;
	else
		velocityX = 150;

	lineY = manager->Simon->postY;
}

void Head::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isActive = true;

	//postY = _Y;
	//postY = manager->Simon->postY;
	lineY = manager->Simon->postY;

	postX = _X;
	a = 0.8f;

	if (manager->Simon->isRight)
	{
		velocityX = -120;
		sprite = spriteLeft;
	}
	else
	{
		velocityX = 120;
		sprite = spriteRight;
	}
	sprite->_Index = 7;
}

void Head::Update(const float &_DeltaTime)
{
	postX += velocityX * _DeltaTime;
	a += 0.03;

	postY = 100 * sin(a) + lineY;

	timerSprite += _DeltaTime;
	if (timerSprite >= 0.1f)
	{
		
		sprite->Next(23, 24);
		timerSprite = 0;
	}

	if (!IsInCamera())
		this->isActive = false;
}



void Head::Render()
{
	sprite->Render(postX, postY);
}

void Head::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Head::Collision()
{
	Enemy::Collision();
}

void Head::CheckActive()
{
	if ((postX < Sprite::cameraX) || (postX > Sprite::cameraX + 512))
		isActive = false;
}

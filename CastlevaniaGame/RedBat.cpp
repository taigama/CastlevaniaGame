#include "RedBat.h"
#include "Sprite.h"
#include "World.h"


RedBat::RedBat() {}

RedBat::RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = REDBAT;
	spriteLeft->_Index = 7;
	spriteRight->_Index = 7;
}

RedBat :: ~RedBat()
{

}

void RedBat::Init(int _X, int _Y)
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

void RedBat::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isActive = true;

	//postY = _Y;
	//postY = manager->Simon->postY;
	lineY = manager->Simon->postY;

	postX = _X;
	a = 0;

	if (manager->Simon->isRight)
	{
		velocityX = -130;
		sprite = spriteLeft;
	}
	else
	{
		velocityX = 130;
		sprite = spriteRight;
	}
	sprite->_Index = 7;
}

void RedBat::Update(const float &_DeltaTime)
{
	postX += velocityX * _DeltaTime;
	a += 0.03;
	timerSprite += _DeltaTime;

	postY = 20 * sin(a) + lineY;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(7, 10);
		timerSprite = 0;
	}

	if ((postX < Sprite::cameraX - 16) || (postX > Sprite::cameraX + 528))
		this->isActive = false;
	// hàm này xét nhỏ quá
	//if (!IsInCamera())
		//this->isActive = false;
}



void RedBat::Render()
{
	sprite->Render(postX, postY);
}

void RedBat::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void RedBat::Collision()
{
	Enemy::Collision();
}

void RedBat::CheckActive()
{
	if ((postX < Sprite::cameraX) || (postX > Sprite::cameraX + 512))
		isActive = false;
}

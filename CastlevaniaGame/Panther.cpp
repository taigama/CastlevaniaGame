#include "Panther.h"
#include "Sprite.h"
#include "World.h"
#include <math.h>

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(6, -32, -14, 14);
	enemyType = PANTHER;
	spriteLeft->_Index = 2;
	spriteRight->_Index = 2;
}

Panther :: ~Panther()
{

}


void Panther::Init(int _X, int _Y)
{
	if (manager->Simon->postX < _X)
		Init(_X, _Y, false);
	else
		Init(_X, _Y, true);

	health = 1;
}

void Panther::Init(int _X, int _Y, bool _isRight)
{
	isActive = true;
	isSleeping = true;
	hasJumped = false;
	postY = _Y;
	postX = _X;
	isRight = _isRight;
	if (isRight)
	{
		sprite = spriteRight;
		velocityX = 200;

	}
	else
	{
		sprite = spriteLeft;
		velocityX = -200;
	}
	velocityY = 0;

	health = 1;
}

void Panther::Update(const float &_DeltaTime)
{

	velocityY += -(2000 * _DeltaTime);
	Enemy::CheckGroundCollision(manager, _DeltaTime);

	// kiem tra kich simon co nam gan con bao khong? khoang cach toi thieu 150px
	//if (manager->Simon->postX <= postX + 100 && manager->Simon->postX >= postX - 100)
		//isSleeping = false;

	if (sqrt(
			pow(manager->Simon->postX - this->postX, 2) + 
			pow(manager->Simon->postY - this->postY, 2)) 
		< 200)
		isSleeping = false;

	if (isSleeping)
	{
		postY += velocityY*_DeltaTime;
		return;
	}
	// đang chạy chuyển sang nhảy 
	if (!hasJumped && velocityY < 0)
	{
		hasJumped = true;
		sprite->_Index = 4;

		//lực nhảy của con báo
		if (isRight)
			velocityX += 150;
		else
			velocityX -= 150;
		velocityY += 300;
	}
	//truong hop dang nhay cham dat
	if (hasJumped && velocityY == 0)
	{
		hasJumped = false;
		if (isRight)
		{
			sprite = spriteLeft;
			velocityX = -200;
		}
		else
		{
			sprite = spriteRight;
			velocityX = 200;
		}
	}

	postX += velocityX * _DeltaTime;
	postY += velocityY* _DeltaTime;

	if (!hasJumped)
	{
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			sprite->Next(3, 5);
			timerSprite = 0;
		}
	}

	//kiem tra nam ngoai camera
	if (!IsInCamera())
		isActive = false;

}



void Panther::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Panther::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Panther::Collision()
{

}

void Panther::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;

}
#include "EnemyFire.h"
#include "Sprite.h"
#include "World.h"

EnemyFire::EnemyFire() {}

EnemyFire::EnemyFire(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(2, -2, -3, 3);
	enemyType = ENEMYFIRE;
	spriteLeft->_Index = 28;
	spriteRight->_Index = 28;

}

EnemyFire :: ~EnemyFire()
{

}

void EnemyFire::Init(int _X, int _Y)
{
}

void EnemyFire::Init(int _X, int _Y, bool _isRight)
{
	// -----------
	health = 1;
	isRight = _isRight;
	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
	{
		velocityX = 150;
		sprite = spriteRight;

	}
	else
	{
		velocityX = -150;
		sprite = spriteLeft;
	}

	sprite->_Index = 28;
}

void EnemyFire::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;
	postX += velocityX * _DeltaTime;

	// điều kiện để lửa un-active
	if (!IsInCamera())
		this->isActive = false;
}



void EnemyFire::Render()
{
	if (!isActive)
		return;
	sprite->Render(postX, postY);
}

void EnemyFire::Destroy()
{
	manager->Simon->score += 100;
	isActive = false;
}

void EnemyFire::Collision()
{
	Enemy::Collision();
}

void EnemyFire::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}
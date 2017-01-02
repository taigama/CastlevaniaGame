#include "Boomerang.h"
#include "World.h"
#include "GroupObject.h"
#include "Game.h"
#include <math.h>

Boomerang::Boomerang(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = BOOMERANG;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 5;
	spriteRight->_Index = 5;
	spriteLeft->_Index = 5;
	Damage = 4;
	collider->setCollider(10, -10, -10, 10);
	isReverted = false;


}
Boomerang::~Boomerang()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}
void Boomerang::Init(int _X, int _Y)
{
	Game::gameSound->playSoundLoop(BOOMERANG);
	isReverted = false;
	isActive = true;
	postX = _X;
	isRight = manager->Simon->isRight;
	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	if (isRight)
	{
		velocityX = 200;
		sprite = spriteRight;
	}
	else
	{
		velocityX = -200;
		sprite = spriteLeft;
	}

}

void Boomerang::Update(const float &_DeltaTime)
{

	timerSprite += _DeltaTime;

	postX += velocityX*_DeltaTime;
	if (postX >= Sprite::cameraX + 512 || postX <= Sprite::cameraX)
	{
		postX -= velocityX*_DeltaTime;
		if (isRight)
		{
			if (isReverted)
			{
				isActive = false;
				Game::gameSound->stopSound(BOOMERANG);
				return;
			}
			velocityX = -200;
			sprite = spriteLeft;
			isRight = false;
			isReverted = true;
		}
		else
		{

			if (isReverted)
			{
				isActive = false;
				Game::gameSound->stopSound(BOOMERANG);
				return;
			}
			velocityX = 200;
			sprite = spriteRight;
			isRight = true;
			isReverted = true;
		}
		postX += velocityX*_DeltaTime;

	}
	if (timerSprite >= BOOM_ANIM_TIME)
	{
		sprite->Next(5, 7);
		timerSprite -= BOOM_ANIM_TIME;
	}
	
	if (SweptAABB(manager->Simon, _DeltaTime) < 1 && isReverted)
	{
		Game::gameSound->stopSound(BOOMERANG);
		isActive = false;
	}
	if (!IsInCamera())
		isActive = false;

	CollisionObject(_DeltaTime);
}
void Boomerang::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Boomerang::Destroy()
{
	isActive = false;
}
void Boomerang::Collision()
{
	isActive = false;
}
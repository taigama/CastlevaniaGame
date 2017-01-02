#include "Axe.h"
#include "World.h"
#include "GroupObject.h"
#include "Game.h"

Axe::Axe(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = AXE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 1;
	spriteRight->_Index = 1;
	spriteLeft->_Index = 1;
	Damage = 4;
	isReverted = false;

	// update by k
	collider->setCollider(18, -18, -18, 18);
}
Axe::~Axe()
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
void Axe::Init(int _X, int _Y)
{
	///////
	Game::gameSound->playSoundLoop(WHIPATTACK_AXE);

	isActive = true;
	postX = _X;
	postY = _Y;
	isRight = manager->Simon->isRight;

	velocityY = 600;

	// update by k
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

void Axe::Update(const float &_DeltaTime)
{
	
	if (!isActive)
		return;
	timerSprite += _DeltaTime;

	postX += velocityX*_DeltaTime;
	//xac dinh toòa do Y
	velocityY += -(1000 * _DeltaTime);
	postY += (velocityY * _DeltaTime);
	if (timerSprite >= ANIM_TIME/1.5f)
	{
		sprite->Next(1,4);
		timerSprite -= ANIM_TIME/1.5f;
	}
	

	if (!IsInCamera())
	{
		isActive = false;
		Game::gameSound->stopSound(WHIPATTACK_AXE);
		return;
	}
	CollisionObject(_DeltaTime);
}
void Axe::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Axe::Destroy()
{
	isActive = false;
}
void Axe::Collision()
{
	isActive = false;
}
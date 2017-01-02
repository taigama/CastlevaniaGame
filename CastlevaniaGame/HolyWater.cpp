#include "HolyWater.h"
#include "World.h"
#include "GroupObject.h"
#include "Game.h"

HolyWater::HolyWater(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = HOLYWATER;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 8;
	spriteRight->_Index = 8;
	spriteLeft->_Index = 8;

	collider->setCollider(4, -4, -4, 4);
	Damage = 2;
	isReverted = false;

}
HolyWater::~HolyWater()
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
void HolyWater::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;
	isRight = manager->Simon->isRight;

	velocityY = 400;

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

}

void HolyWater::Update(const float &_DeltaTime)
{
	CollisionObject(_DeltaTime);
	if (!isActive)
		return;
	timerSprite += _DeltaTime;

	postX += velocityX*_DeltaTime;
	//xac dinh tọa do Y
	velocityY += -(1000 * _DeltaTime);
	postY += (velocityY * _DeltaTime);

	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	CollisionObject(_DeltaTime);
}
void HolyWater::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void HolyWater::Destroy()
{

	isActive = false;
}
void HolyWater::Collision()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		if (manager->holyFire[i]->isActive)
			count++;
	}

	if (count <= manager->Simon->weaponNumber)
	{
		manager->holyFire[count]->Init(postX, postY);
		Game::gameSound->playSound(HOLYWATERBREAK);
	}
	isActive = false;
}

void HolyWater::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{

		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f&& collisionScale > 0.0f)
			{
				((Enemy*)tempObject)->Freeze(ANIM_TIME);
				((Enemy*)tempObject)->TakeDamage(Damage);
			}
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				Collision();
			}
			break;
		case DESTRUCTIBLE_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				tempObject->Destroy();
			}
			break;
		}
	}
}
#include "Knife.h"
#include "World.h"
#include "GroupObject.h"
#include "Game.h"

Knife::Knife(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = KNIFE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 0;
	spriteRight->_Index = 0;
	spriteLeft->_Index = 0;
	Damage = 3;

}
Knife::~Knife()
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
void Knife::Init(int _X, int _Y)
{
	Game::gameSound->playSound(SOUNDKNIFE);
	isActive = true;
	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	if (manager->Simon->isRight)
	{
		postX = _X + 10;
		velocityX = 250;
		sprite = spriteRight;
		collider->setCollider(10, -10, -18, 18);
	}
	else
	{
		postX = _X -10;
		velocityX = -250;
		sprite = spriteLeft;
		collider->setCollider(10, -10, -18, 18);
	}

}

void Knife::Update(const float &_DeltaTime)
{
	postX += velocityX*_DeltaTime;
	if (!IsInCamera())
		isActive = false;

	CollisionObject(_DeltaTime);
}

void Knife::CollisionObject(float _DeltaTime)
{
	float collisionScale = 1;

	GameObject* tempObject;


	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{

		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				((Enemy*)tempObject)->TakeDamage(Damage);
				this->isActive = false;
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
		case DESTRUCTIBLE_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				this->isActive = false;
				tempObject->Destroy();
			}
			break;
		default:
			break;
		}
	}
}

void Knife::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Knife::Destroy()
{
	isActive = false;
}
void Knife::Collision()
{
	isActive = false;
}

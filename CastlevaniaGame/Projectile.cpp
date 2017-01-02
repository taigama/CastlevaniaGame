#include "Projectile.h"
#include "World.h"
#include "GroupObject.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Projectile::Projectile() {}

Projectile::Projectile(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PROJECTILE_TYPE;
	manager = _manager;
	collider = new Collider();
	postX = 0;
	postY = 0;
}


Projectile::~Projectile()
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

// ===== VIRTUAL =====
void Projectile::Init(int _X, int _Y)
{
	isActive = false;
	postX = _X;
	postY = _Y;
}

// ---=== THE MAIN PROCESSING ===---
void Projectile::Update(const float &_DeltaTime)
{

}

void Projectile::Render()
{
}

void Projectile::CollisionObject(float _DeltaTime)
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
				// // -----------------
			if (collisionScale < 1.0f&& collisionScale > 0.0f)
			{
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
		{/*
		case GROUND_TYPE:
			if ((this->projectileType == WHIP) && ((Ground*)tempObject)->isBreakable)
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f)
				{
					((Ground*)tempObject)->Destroy();
				}
			}
			break;*/// chỗ này đã được chuyển vào Whip::CollisionObject()
		case DESTRUCTIBLE_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				tempObject->Destroy();
			}
			break;
		default:
			break;
		}
	}
}

void Projectile::Destroy() {}

void Projectile::Collision() {}
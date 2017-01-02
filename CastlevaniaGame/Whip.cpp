#include "Whip.h"
#include "World.h"
#include "GroupObject.h"

Whip::Whip(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = WHIP;
	sizeWidth = 256;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_left.bmp", sizeWidth, sizeHeight, 18, 3);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_right.bmp", sizeWidth, sizeHeight, 18, 3);
	sprite = spriteRight;
	whipLevel = 0;
	Damage = 3;
	isActive = false;

}
Whip::~Whip()
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
void Whip::Init(int _X, int _Y)
{
	isActive = true;

	postX = _X;

	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	if (manager->Simon->isRight)
	{
		sprite = spriteRight;
		// --------- update by k
		if (whipLevel < 2)
			collider->setCollider(16, -5, 27, 74);
		else

			collider->setCollider(18, -20, 27, 110);
			
	}
	else
	{
		sprite = spriteLeft;
		// --------- update by k
		if (whipLevel < 2)
			collider->setCollider(16, -5, -74, -27);
		else
			collider->setCollider(18, -20, -110, -27);
	}

	sprite->_Index = 3 * whipLevel;
	// ---------- update by k
	if (whipLevel < 1)
		Damage = 3;
	else
	{
		Damage = 4;
		if (whipLevel > 1)
		{
			sprite->_Index = 6;
			lvl3indexsprite = 6;
		}
	}

	firstShow = true;
}

void Whip::Update(const float &_DeltaTime)
{
	if (!manager->Simon->isAttack)
		isActive = false;
	if (!isActive)
		return;
	postX = manager->Simon->postX;

	if (manager->Simon->isCrouch)
		postY = manager->Simon->postY - 14;
	else
		postY = manager->Simon->postY;

	// update by khang -------------
	if (manager->Simon->isChangeFrame)
	{
		switch (whipLevel)
		{
		case 0:
			sprite->Next(0, 2);
			break;
		case 1:
			sprite->Next(3, 5);
			break;
			//
		case 2:
			lvl3indexsprite += 4;
			break;
		}
	}

	if (whipLevel == 2)
	{
		sprite->Next(lvl3indexsprite, lvl3indexsprite + 3);
	}

	//-----------------------

	if (manager->Simon->isAttack && manager->Simon->killingMoment)
		CollisionObject(_DeltaTime);
}

void Whip::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;

	GameObject* tempObject;

	// xét với nhóm special
	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{

		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			// frame đầu tiên khi whip xuất hiện => chơi vầy
			if (firstShow)
			{
				if (IsCollide(tempObject))
				{
					((Enemy*)tempObject)->TakeDamage(Damage);
				}
			}
			else
			// mấy frame sau nếu chưa va chạm intersect thì sẽ cho va chạm theo sweptAABB
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f&& collisionScale > 0.0f)
				{
					((Enemy*)tempObject)->TakeDamage(Damage);
				}
			}
			
			break;
		default:
			break;
		}
	}

	// xét với nhóm quadtree (cố định)
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{

		tempObject = manager->groupQuadtreeCollision->objects[i];

		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			if (((Ground*)tempObject)->isBreakable)
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f)
				{
					((Ground*)tempObject)->Destroy();
				}
			}
			break;
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
	firstShow = false;
}


void Whip::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Whip::Destroy()
{
	isActive = false;
}
void Whip::Collision()
{}

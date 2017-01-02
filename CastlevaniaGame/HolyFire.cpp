#include "HolyFire.h"
#include "World.h"
#include "GroupObject.h"

HolyFire::HolyFire(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = HOLYFIRE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->Next(1, 1);

	collider->setCollider(10, -2, -12, 12);

	Damage = 2;
}
HolyFire::~HolyFire()
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
void HolyFire::Init(int _X, int _Y)
{
	timeActive = 0;
	isActive = true;
	postX = _X;
	postY = _Y;
	sprite->Next(1, 1);
}

void HolyFire::Update(const float &_DeltaTime)
{
	if (timeActive >= 1.8f)// 1.8f là thời gian của holy fire
	{
		isActive = false;
		return;
	}
	timeActive += _DeltaTime;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME*1.5f)
	{
		sprite->Next(1, 4);
		timerSprite -= ANIM_TIME*1.5f;
		CollisionObject(_DeltaTime);
	}
	if (!IsInCamera())
		isActive = false;
}

void HolyFire::CollisionObject(float _DeltaTime)
{
	GameObject* tempObject;

	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{

		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			if (IsCollide(tempObject))
			{
				((Enemy*)tempObject)->Freeze(ANIM_TIME*2.0f);
				((Enemy*)tempObject)->TakeDamage(Damage);
			}
			break;
		default:
			break;
		}
	}
}


void HolyFire::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void HolyFire::Destroy()
{
	isActive = false;
}
void HolyFire::Collision()
{

}
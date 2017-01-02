#include "Fish.h"
#include "Sprite.h"
#include "World.h"
#include <time.h>

Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	enemyType = FISH;

	isFiring = false;
	timer = 5;
	sprite->_Index = 12;
	spriteRight->_Index = 12;

}

Fish :: ~Fish()
{

}

void Fish::Init(int _X, int _Y)
{
	health = 1;

	isFiring = false;
	TimeToAttack = 0;
	isActive = true;
	postY = 0;
	velocityY = 650;


	// random vị trí spawn fish nhưng không quá sát player
	do
	{
		postX = Sprite::cameraX + 31 + (rand() % 450);
	} while (
		(postX > (manager->Simon->postX - 80)) &&
		(postX < (manager->Simon->postX + 80))
		);

	if (postX > manager->Simon->postX)
	{
		isRight = false;
		velocityX = -70;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		velocityX = 70;
		sprite = spriteRight;
	}

	jumping = true;
}

void Fish::Init(int _X, int _Y, bool isRight)
{

	health = 1;

	isFiring = false;
	TimeToAttack = 0;
	isActive = true;
	postY = 0;
	velocityY = 650;

	// random vị trí spawn fish nhưng không quá sát player
	do
	{
		postX = Sprite::cameraX + 31 + (rand() % 450);
	} while (
		(postX > (manager->Simon->postX - 80)) &&
		(postX < (manager->Simon->postX + 80))
		);

	if (postX > manager->Simon->postX)
	{
		isRight = false;
		velocityX = -70;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		velocityX = 70;
		sprite = spriteRight;
	}

	jumping = true;
	Effect* bubble1 = Effect::CreateEffect(EFFECT_BUBBLE, postX, postY+20, -4,spriteHandler, manager);
	manager->groupEffect->AddObject(bubble1);
	Effect* bubble2 = Effect::CreateEffect(EFFECT_BUBBLE, postX, postY + 40, -2, spriteHandler, manager);
	manager->groupEffect->AddObject(bubble2);
	Effect* bubble3 = Effect::CreateEffect(EFFECT_BUBBLE, postX, postY + 20, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(bubble3);
}

void Fish::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	//random thoi gian doi chieu
	srand(time(NULL));
	timer = (rand() % 400 + 100) / 100.0;

	//timer = 1.5f;

	// xac dinh sprite can ve

	//xac dinh toòa do Y
	velocityY += -(600 * _DeltaTime);


	//kiem tra neu Y huong xuong va vi?tri doi tuong thap hon mãòt ðâìt
	if (Enemy::CheckGroundCollision(manager, _DeltaTime))
		jumping = false;
	if (!jumping)
	{
		postX += velocityX * _DeltaTime;

		//tinh thoi gian tan cong
		TimeToAttack += _DeltaTime;

		//luu thoi gian chuyen frame cua con ca
		timerSprite += _DeltaTime;

		//thoi gian de chuyen frame 
		if (timerSprite >= 2 * ANIM_TIME)
		{
			// kiem tra con ca co dang tan cong hay không?
			if (isFiring)
			{

				if (postX < manager->Simon->postX)
					velocityX = 70;
				else
					velocityX = -70;

				isFiring = false;
				if (velocityX > 0)
				{
					sprite = spriteRight;
					isRight = true;
				}
				else
				{
					sprite = spriteLeft;
					isRight = false;
				}


			}
			else // con ca dang khong tan cong
			{
				sprite->Next(12, 13);
				//kiem tra va cho con ca tan cong
				if (TimeToAttack >= timer)
				{
					ActivateEnemyFire();
					sprite->_Index = 11;

					TimeToAttack = 0;
					isFiring = true;
				}
				timerSprite = 0;
			}
		}
	}
	postY += (velocityY * _DeltaTime);

	if (!IsInCamera())
		this->isActive = false;
}


void Fish::Render()
{
	if (!isActive)
		return;
	sprite->Render(postX, postY);
}

void Fish::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 300;
	isActive = false;
}

void Fish::Collision()
{
	Enemy::Collision();
}

void Fish::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}

void Fish::ActivateEnemyFire()
{
	EnemyFire *enemyFire = new EnemyFire(manager->spriteHandler, manager);
	enemyFire->Init(postX, postY + 17, isRight);
	manager->groupEnemy->AddObject(enemyFire);
}
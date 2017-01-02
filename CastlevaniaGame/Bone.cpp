#include "Bone.h"
#include "Sprite.h"
#include "World.h"
#include <time.h>
#include "Game.h"

Bone::Bone() {}

Bone::Bone(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	enemyType = BONE;
	timer = 5;
	sprite->_Index = 27;
	spriteRight->_Index = 27;

}

Bone :: ~Bone()
{

}

void Bone::Init(int _X, int _Y)
{

	health = 24;

	TimeToAttack = 0;
	isActive = true;
	postX = _X;
	postY = _Y;
	if (postX > manager->Simon->postX)
	{
		isRight = false;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		sprite = spriteRight;
	}
}


void Bone::Update(const float &_DeltaTime)
{
	// nếu bị đóng băng thì không Update các hoạt động
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;
		if (timerFreeze <= 0.0f)
			isFreezed = false;

		return;
	}

	if (!isActive)
		return;
	//random thoi gian tan cong
	srand(time(NULL));
	timer = (rand() % 400 + 100) / 100.0;
	if (postX > manager->Simon->postX)
	{
		isRight = false;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		sprite = spriteRight;
	}
	

		//tinh thoi gian tan cong
		TimeToAttack += _DeltaTime;
		if (TimeToAttack >= timer)
		{
			TimeToAttack = 0;
			ActivateEnemyFire();
			sprite->SetColorOverlay(255, 255, 255);
		}
		
}


void Bone::Render()
{
	if (!isActive)
		return;
	sprite->Render(postX, postY);
}

void Bone::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 300;
	isActive = false;
}

void Bone::Collision()
{
	Enemy::Collision();
}

void Bone::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}

void Bone::ActivateEnemyFire()
{
	EnemyFire *enemyFire = new EnemyFire(manager->spriteHandler, manager);
	enemyFire->Init(postX, postY + 14, isRight);
	manager->groupEnemy->AddObject(enemyFire);
	sprite->SetColorOverlay(255, 0, 0);
}

void Bone::TakeDamage(int damage)
{
	health -= damage;
	
	// làm chớp chớp

	int randomX = RandomOutside(8, 12);
	int randomY = RandomOutside(8, 12);

	Effect* hitEffect = Effect::CreateEffect(EFFECT_HIT, this->postX + randomX, this->postY + randomY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(hitEffect);

	if (health <= 0)
	{
		Game::gameSound->playSound(HITSOFT);
		Destroy();
		return;
	}
	Game::gameSound->playSound(HITSTEEL);
}
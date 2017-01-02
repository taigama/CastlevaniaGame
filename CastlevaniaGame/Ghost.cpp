#include "Ghost.h"
#include <math.h>
#include "World.h"
#include "Player.h"
#include "Game.h"

Ghost::Ghost(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -14, 14);
	enemyType = GHOST;

	spriteLeft->_Index = 25;
	spriteRight->_Index = 25;
}

void Ghost::Init(int _X, int _Y)
{
	health = 8;
	isActive = true;

	postX = _X;
	postY = _Y;
}

void Ghost::Init(int _X, int _Y, bool isRight)
{
	health = 8;
	isActive = true;

	//postX = _X;
	postY = _Y;

	// lật ngược chiều spawn
	int deltaX = _X - manager->Simon->postX;
	postX = _X - (2 * deltaX);
}

void Ghost::Update(const float &_DeltaTime)
{
	// nếu bị đóng băng thì không Update các hoạt động
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;
		if (timerFreeze <= 0.0f)
			isFreezed = false;
		
		return;
	}

	// khoảng cách ghost đến player
	float distance =
		sqrt(
			pow(manager->Simon->postX - this->postX, 2)
			+ pow(manager->Simon->postY - this->postY, 2)
		);

	// tính hướng bay của ghost
	float scale = distance / 20; // 30 la toc do cua con nay
	velocityX = (manager->Simon->postX - this->postX) / scale;
	velocityY = (manager->Simon->postY - this->postY) / scale;

	// chuyển sprite tuỳ theo hướng
	if (velocityX > 0)	// bay sang phải
	{
		sprite = spriteRight;
	}
	else
	{	// bay sang trái
		sprite = spriteLeft;
	}


	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;

	// chuyển sprite
	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		velocityY = velocityY / 2;
		sprite->Next(25, 26);
		timerSprite -= ANIM_TIME;
	}

	if (!IsInCamera())
		this->isActive = false;
}



void Ghost::Render()
{
	sprite->Render(postX, postY);
}

void Ghost::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 300;
	isActive = false;
}

void Ghost::Collision() {}

void Ghost::TakeDamage(int damage)
{
	// làm mất máu
	health -= damage;
	Game::gameSound->playSound(HITSOFT);

	// mất nhiều máu quá -> chết
	if (health <= 0)
	{
		Destroy();
		return;
	}

	Freeze(ANIM_TIME*2.0f);
}
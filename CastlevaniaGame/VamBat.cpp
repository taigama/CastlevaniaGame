#include "VamBat.h"
#include "Sprite.h"
#include "World.h"


VamBat::VamBat() {}

VamBat::VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = VAMBAT;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\VamBat.png", 96, 46, 3, 3);

	healthMax = 32;
	health = healthMax;
}

VamBat :: ~VamBat()
{

}

void VamBat::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;
	health = healthMax;
	velocityY = -150;
	velocityX = -80;
	sprite->Next(0, 0);
	isSleeping = true;
	timeSleeping = 0;
	thoigiandung = 2;
}

void VamBat::Update(const float &_DeltaTime)
{
	// nếu bị đóng băng thì không Update các hoạt động
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;
		if (timerFreeze <= 0.0f)
			isFreezed = false;

		return;
	}

	if (health <= 0)
	{
		health = 0;
		Destroy();
	}
	if (IsInCamera())
	{
		timeSleeping += _DeltaTime;
		if (timeSleeping > 6)
			isSleeping = false;
		if (isSleeping)
			sprite->Next(0, 0);
		else
		{
			if (postY <550)
				velocityY = 150;
			if (postY > 750)
				velocityY = -150;
			if (postX < 5250 || postX>5600)
			{
				velocityX = 0;
				velocityY = 0;
				thoigiandung -= _DeltaTime;
				if (thoigiandung <0)
				{
					if (manager->Simon->postX >= postX)
						velocityX = 80;
					else
						velocityX = -80;
					thoigiandung = 2;
				}
			}
			postX += velocityX * _DeltaTime;
			postY += velocityY * _DeltaTime;

			timerSprite += _DeltaTime;
			if (timerSprite >= 0.2f)
			{
				velocityY -= velocityX / 5;
				sprite->Next(1, 2);
				timerSprite -= 0.2f;
			}
		}
	}
}



void VamBat::Render()
{
	sprite->Render(postX, postY);
}

void VamBat::Destroy()
{
	// hang 1
	Effect* effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX - 32, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX + 32, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 2
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX - 32, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX + 32, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 3
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX - 32, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_BOSSSPIRIT, postX + 32, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, Sprite::cameraX+512/2,Sprite::cameraY-448/2, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
}

void VamBat::Collision()
{
	Enemy::Collision();
}

void VamBat::CheckActive()
{
	if (manager->Simon->postX<postX - 200 /*|| manager->Simon->postX>postX+400*/) //zone của vamBat từ 1000 - 15000, bắt đầu hành động khi simon còn cách 200
		isActive = false;
	else
		isActive = true;
}

int VamBat::HealthDot()
{
	float scale = 0.5f;	// 16/32
	return (int)(((float)health)*scale);
}
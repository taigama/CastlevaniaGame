#include "Medusa.h"
#include "Sprite.h"
#include "World.h"


Medusa::Medusa() {}

Medusa::Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(32, -32, -32, 32);
	enemyType = MEDUSA;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\medusa.png", 65, 64, 5, 5);
	thoigiandung = 0;

	healthMax = 64;
	health = healthMax;
}

Medusa :: ~Medusa()
{

}

void Medusa::Init(int _X, int _Y)
{
	health = healthMax;
	sprite->_Index = 4;
	TimeToAttack = 0;
	isActive = true;
	isSleeping = true;
	postX = _X;
	postY = _Y;
	lineY = 1020;
	if (manager->Simon->postX > postX)
		velocityX = 150;
	else
		velocityX = -150;
	a = 0;
	timeSleeping = 0;

}

void Medusa::Update(const float &_DeltaTime)
{
	// nếu bị đóng băng thì không Update các hoạt động
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;
		if (timerFreeze <= 0.0f)
			isFreezed = false;

		return;
	}
	//Tránh cho health bị trừ âm, thanh máu sẽ sai
	if (health <= 0)
	{
		health = 0;
		Destroy();
	}

	if (IsInCamera())
	{
		timeSleeping += _DeltaTime;
		if (timeSleeping > 5)
			isSleeping = false;
		if (isSleeping)
		{
			sprite->Next(4, 4);
			collider->setCollider(-14, 14, 10, -10);
		}
		else
		{
			collider->setCollider(14, -14, -10, 10);
			a+=0.05;
			//random thoi gian tan cong
			srand(time(NULL));
			timer = (rand() % 400 + 300) / 100.0;
			//sau thời gian trên sẽ nhả rắn 1 lần
			TimeToAttack += _DeltaTime;
			if (TimeToAttack >= timer)
			{
				TimeToAttack = 0;
				ActivateSnake();
			}
			//Dừng ở 2 cận trái phải
			if (postX < 100 || postX>500)
			{
				velocityX = 0;
				thoigiandung += _DeltaTime;
				if (thoigiandung > 2)
				{
					if (postX < 100)
						velocityX = 150;
					else
						velocityX = -150;
					thoigiandung = 0;
				}
			}
			postX += velocityX * _DeltaTime;
			
			timerSprite += _DeltaTime;
			if (timerSprite >= 0.1f)
			{
				postY = sin(a) * 20 + lineY;
				sprite->Next(0, 3);
				timerSprite = 0;
			}
		}
	}


}



void Medusa::Render()
{
	sprite->Render(postX, postY);
}

void Medusa::Destroy()
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
	/*Item* newItem = Item::CreateItem(CRYSTAL, this->postX, this->postY, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);*/
}

void Medusa::Collision()
{
	Enemy::Collision();
}

void Medusa::CheckActive()
{
	if (manager->Simon->postX <100 || manager->Simon->postX>600)
		isActive = false;
	else
		isActive = true;
}

void Medusa::ActivateSnake()
{
	Snake *snake = new Snake(manager->spriteHandler, manager);
	snake->Init(postX, postY + 14);
	manager->groupEnemy->AddObject(snake);
}


int Medusa::HealthDot()
{
	float scale = 0.25f;	// 16/64
	return (int)(((float)health)*scale);
}
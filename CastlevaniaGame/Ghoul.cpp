#include "Ghoul.h"
#include "Sprite.h"
#include "World.h"
Ghoul::Ghoul() {}

Ghoul::Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(32, -32, -14, 14);
	enemyType = GHOUL;
}

Ghoul :: ~Ghoul()
{

}

void Ghoul::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
		velocityX = -70;
	else
		velocityX = 70;

	velocityY = -3000.0f;
}
void Ghoul::Init(int _X, int _Y)
{
	isActive = true;
	postY = _Y;
	postX = _X;
	velocityX = -70;
}

void Ghoul::Update(const float &_DeltaTime)
{
	// mô phỏng trọng lực
	velocityY += -(1000 * _DeltaTime);
	Enemy::CheckGroundCollision(manager, _DeltaTime);

	//cập nhật tọa độ X,Y
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}

	if (!IsInCamera())
		this->isActive = false;
}



void Ghoul::Render()
{
	sprite->Render(postX, postY);
}

void Ghoul::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
	isActive = false;
}

void Ghoul::Collision()
{
	Enemy::Collision();
}

void Ghoul::CheckActive()
{
	if (postX < Sprite::cameraX || postX > Sprite::cameraX + 512)
		isActive = false;
}
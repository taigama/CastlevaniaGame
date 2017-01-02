#include "Knight.h"
#include "Sprite.h"
#include "World.h"
#include "Game.h"

Knight::Knight() {}

Knight::Knight(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(28, -32, -14, 14);
	enemyType = KNIGHT;
	spriteLeft->_Index = 14;
	spriteRight->_Index = 14;
}

Knight :: ~Knight()
{

}


void Knight::Init(int _X, int _Y)
{
	health = 8;

	isActive = true;
	postY = _Y;
	postX = _X;
	if (manager->Simon->isRight)
		velocityX = -30;
	else
		velocityX = 30;
	
}
void Knight::Init(int X, int Y, int Left, int Right)
{
	health = 8;

	isActive = true;
	//isSleeping = true;
	postY = Y;
	postX = X;
	maxLeft = Left;
	maxRight = Right;
	if (manager->Simon->isRight)
		velocityX = -30;
	else
		velocityX = 30;
}

void Knight::Update(const float &_DeltaTime)
{
	// nếu bị đóng băng thì không Update các hoạt động
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;
		if (timerFreeze <= 0.0f)
			isFreezed = false;

		return;
	}

	postX += velocityX * _DeltaTime;
	if (postX >= maxRight)
	{
		if (velocityX > 0)
		{
			velocityX *= -1;
			sprite = spriteLeft;
		}
	}
	else if (postX <= maxLeft)
	{
		if (velocityX < 0)
		{
			velocityX *= -1;
			sprite = spriteRight;
		}
	}
	timerSprite += _DeltaTime;
	if (timerSprite >= (ANIM_TIME*3))
	{
		sprite->Next(14, 17);
		timerSprite = 0;
	}
	
	
}

bool Knight::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
					if
						(normaly > 0.1f)//chạm từ trên xuống
						return true;
					break;
				}
			}
			break;
		}
	}
	return false;
}

void Knight::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

//void Knight::TakeDamage(int Damage)
//{
//	health -= Damage;
//	Effect* newEffect = Effect::CreateEffect(EFFECT_HIT, this->postX, this->postY, 1, spriteHandler, manager);
//	manager->groupEffect->AddObject(newEffect);
//
//	if (velocityX > 0) // đang đi sang phải
//		postX -= 4;
//	else if (velocityX < 0) // đang đi sang trái
//		postX += 4;
//
//	if (health <= 0)
//		Destroy();
//}

void Knight::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 400;
	isActive = false;
}

void Knight::Collision()
{
	Enemy::Collision();
}

void Knight::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;

}

void Knight::TakeDamage(int damage)
{
	// làm mất máu
	health -= damage;
	Game::gameSound->playSound(HITSOFT);

	// hiệu ứng *
	int randomX = RandomOutside(8, 12);
	int randomY = RandomOutside(8, 12);
	Effect* hitEffect = Effect::CreateEffect(EFFECT_HIT, this->postX + randomX, this->postY + randomY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(hitEffect);

	// mất nhiều máu quá -> chết
	if (health <= 0)
	{
		Destroy();
		return;
	}

	Freeze(ANIM_TIME*3.0f);
}
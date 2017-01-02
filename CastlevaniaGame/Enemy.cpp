#include "Enemy.h"
#include "World.h"
#include "Game.h"

Enemy::Enemy()
{
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	objectType = ENEMY_TYPE;
	manager = _manager;
	collider = new Collider();

	isActive = false;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteHandler = _SpriteHandler;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;

	/////////
	isFreezed = false;
	timerFreeze = 0.0f;
}

Enemy :: ~Enemy()
{

}

void Enemy::Init(int _X, int _Y)
{
}

void Enemy::Init(int _X, int _Y, bool _IsRight)
{
}

void Enemy::Update(const float &_DeltaTime)
{
}


void Enemy::Render()
{
}

void Enemy::Destroy()
{
	isActive = false;
}

// tam thoi chi xai ham nay
void Enemy::TakeDamage(int damage)
{
	health -= damage;
	Game::gameSound->playSound(HITSOFT);


	int randomX = rand() % 32 - 16;
	int randomY = rand() % 32 - 16;
	Effect* newEffect = Effect::CreateEffect(EFFECT_HIT, this->postX + randomX, this->postY + randomY, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(newEffect);
	
	if (health <= 0)
		Destroy();
}

void Enemy::Collision()
{
	Effect* effect = Effect::CreateEffect(EFFECT_HIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	TakeDamage(NULL, 1);
}



void Enemy::CheckActive()
{

}

// tam thoi ko xai ham nay
void Enemy::TakeDamage(GameObject * actor, int damage)
{
	health -= damage;
	Game::gameSound->playSound(HITSOFT);


	if (health <= 0)
		Destroy();
}

Enemy * Enemy::CreateEnemy(int enemyType, int X, int Y, LPD3DXSPRITE _SpriteHandler, World * _manager)
{
	Enemy* enemy = new Enemy();
	switch (enemyType)
	{
	case KNIGHT:
		enemy = new Knight(_SpriteHandler, _manager);
		enemy->Init(X, Y);
		break;
	case SNAKE:
		enemy = new Snake(_SpriteHandler, _manager);
		enemy->Init(X, Y);
		break;
	}
	return enemy;
}
bool Enemy::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;
	// Xét va chạm với nhóm đối tượng trong quadtree. Ví dụ như Ground, Destructibe, Zone,...
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		tempObject = manager->groupQuadtreeCollision->objects[i];
		if (tempObject->objectType == GROUND_TYPE)
		{
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			// nếu có va chạm
			if (collisionScale < 1.0f && normaly > 0.1f)
			{
				SlideFromGround(tempObject, _DeltaTime, collisionScale);
				return true;
			}
		}
	}
	return false;
}


//////////////////
void Enemy::Freeze(float _Time)
{
	isFreezed = true;
	timerFreeze = _Time;
}
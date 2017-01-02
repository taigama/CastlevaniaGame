#include "Snake.h"
#include "World.h"
#include "GroupObject.h"

Snake::Snake(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;

	collider = new Collider();
	collider->setCollider(10, -10, -16, 16);

	postX = 0;
	postY = 0;
	sizeWidth = 32;
	sizeHeight = 20;
	objectType = ENEMY_TYPE;
	enemyType = SNAKE;

	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\snakeRight.png", 32, 20, 0, 2);
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\snakeLeft.png", 32, 20, 0, 2);
	spriteRight->_Index = 0;
	spriteLeft->_Index = 0;
	sprite = spriteRight;

}
Snake::~Snake()
{

}
void Snake::Init(int _X, int _Y)
{
	health = 1;
	postX = _X;
	postY = _Y;
	isActive = true;
	isFalling = false;

	//simon nam ben trai medusa
	if (manager->Simon->postX < postX)
	{
		sprite = spriteLeft;
		velocityX = -160;
	}
	else
	{
		sprite = spriteRight;
		velocityX = 160;
	}
}

void Snake::Update(const float &_DeltaTime)
{
	//kiem tra snake co trong camera khong?
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}


	// mo phong trong luc
	velocityY += -(1000 * _DeltaTime);

	//truong hop dung gach theo phuong ngang
	if (CollisionObject(_DeltaTime))
	{
		isFalling = true;
		velocityX = 0;
	}

	//neu khong dung gach theo phuong ngang thi xet va cham voi gach tu tren xuong
	if (!isFalling)
		Enemy::CheckGroundCollision(manager, _DeltaTime);

	//tinh toan va kiem tra thoi gian chuyen sprite
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}

	postX += velocityX*_DeltaTime;
	postY += velocityY*_DeltaTime;
}
void Snake::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Snake::Destroy()
{
	isActive = false;
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
}
void Snake::Collision()
{}

bool Snake::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		tempObject = manager->groupQuadtreeCollision->objects[i];
		if (tempObject->objectType == GROUND_TYPE)
		{
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			// nếu có va chạm theo phương ngang
			if (collisionScale < 1.0f && (normalx < -0.1f || normalx > 0.1f))
				return true;
		}
	}
	return false;
}
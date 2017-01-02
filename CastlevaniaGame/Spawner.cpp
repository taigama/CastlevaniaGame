#include "Spawner.h"

#include "World.h"
#include "MainGame.h"

#include "OLoader.h"
#include "Sprite.h"

#include "Player.h"
#include "Head.h"
#include "Ghost.h"

Spawner::Spawner(LPD3DXSPRITE _SpriteHandler, World *_manager) :Zone(_SpriteHandler, _manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ZONE_TYPE;//9
	typeZone = ZONE_SPAWNER;//6

	isActive = false;
	objects = NULL;
	timers = NULL;
	timerRespawn = 0.0f;
}


Spawner::~Spawner()
{
}


// virtual function
void Spawner::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _TypeEnemy, int _Count,
	int rubbish1, int rubbish2, int rubbish3)
{
	isActive = true;
	// coordinate & collider
	Zone::Init(_X, _Y, _Width, _Height);
	// ----------

	typeEnemy = _TypeEnemy % 100; // 503 => 3 là ghoul
	numberEnemy = _Count;

	int parameters[] = { 0,typeEnemy,0,0 };

	objects = new Enemy*[numberEnemy];
	for (int i = 0; i < numberEnemy; i++)
	{
		objects[i] = NULL;
		// tạo enemy mới
		switch (typeEnemy)
		{
			// map1 enemies
		case REDBAT:
			objects[i] = new RedBat(spriteHandler, manager);
			break;
		case GHOUL:
			objects[i] = new Ghoul(spriteHandler, manager);
			break;
		case FISH:
			objects[i] = new Fish(spriteHandler, manager);
			break;

			// map2 enemies
		case HEAD:
			objects[i] = new Head(spriteHandler, manager);
			break;
		case GHOST:
			objects[i] = new Ghost(spriteHandler, manager);
			break;
		default:
			break;
		}

		// nếu tạo object thất bại
		if (objects[i] == NULL)
		{
			i--;
			numberEnemy--;
		}
		else
		{
			// thêm object vào group enemy
			manager->groupEnemy->AddObject(objects[i]);
		}
	}

	timerRespawn = (numberEnemy + 1);

	timers = new float[numberEnemy];
	for (int i = 0; i < numberEnemy; i++)
	{
		timers[i] = timerRespawn * (0.1f) + ((float)i * 0.75f);
	}

}

// player đụng vào => cho spawn các con enemy
void Spawner::Collision(Player *actor, const float &_DeltaTime)
{
	// kiểm tra từng object
	for (int i = 0; i < numberEnemy; i++)
	{
		// nếu object không active => sẵn sàng để xuất hiện lại
		if (objects[i]->isActive == false)
		{
			// chờ 1 lúc rồi mới tạo lại
			timers[i] += _DeltaTime;
			if (timers[i] >= timerRespawn)
			{
				// reset timer
				timers[i] -= timerRespawn;

				// init enemy theo hướng xoay của người chơi
				int calX, calY;
				calY = this->postY + this->collider->bottom + 33;

				if (actor->isRight)
				{
					calX = Sprite::cameraX + 512 - 0;
				}
				else
				{
					//
					calX = Sprite::cameraX + 0;
				}
				objects[i]->Init(calX, calY, actor->isRight);
			}
		}
	}
}
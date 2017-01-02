// K_1.1 & K_1.2 sửa kha khá để testing

#include "World.h"
#include "MainGame.h"
#include <time.h>
#include "GroupObject.h"
#include "ColliderBlock.h"


World::World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;
	castlevania = _MainGame;

	// ---  init static object  ---
	Simon = new Player(spriteHandler, this);
	
	//-----------
	
	groupSpecialCollision = new GroupObject(this);
	groupQuadtreeCollision = new GroupObject(this);
	groupItem = new GroupObject(this);
	groupEffect = new GroupObject(this);
	groupProjectile = new GroupObject(this);

	groupEnemy = new GroupObject(this);
	rootGONode = NULL;
	// -----------------

	isPaused = false;
	isFreezed = false;
	timerFreeze = 0.0f;
}


World::~World()
{
	delete Simon;
	delete whip;

	delete groupSpecialCollision;
	delete groupQuadtreeCollision;

}

// 
void World::Init()
{
	// ---  init changable object
	isFlash = false;

	

	//ghoul = new Ghoul(spriteHandler, this);
	//redBat = new RedBat(spriteHandler, this);
	//blueBat = new BlueBat(spriteHandler, this);
	
	//fish = new Fish(spriteHandler, this);
	//vamBat = new VamBat(spriteHandler, this);

	boss = NULL;

	whip = new Whip(spriteHandler, this);
	groupProjectile->AddObject(whip);

	knife[0] = new Knife(spriteHandler, this);
	knife[1] = new Knife(spriteHandler, this);
	knife[2] = new Knife(spriteHandler, this);
	groupProjectile->AddObject(knife[0]);
	groupProjectile->AddObject(knife[1]);
	groupProjectile->AddObject(knife[2]);

	boo[0] = new Boomerang(spriteHandler, this);
	boo[1] = new Boomerang(spriteHandler, this);
	boo[2] = new Boomerang(spriteHandler, this);
	groupProjectile->AddObject(boo[0]);
	groupProjectile->AddObject(boo[1]);
	groupProjectile->AddObject(boo[2]);

	axe[0] = new Axe(spriteHandler, this);
	axe[1] = new Axe(spriteHandler, this);
	axe[2] = new Axe(spriteHandler, this);
	groupProjectile->AddObject(axe[0]);
	groupProjectile->AddObject(axe[1]);
	groupProjectile->AddObject(axe[2]);

	holyFire[0] = new HolyFire(spriteHandler, this);
	holyFire[1] = new HolyFire(spriteHandler, this);
	holyFire[2] = new HolyFire(spriteHandler, this);
	groupProjectile->AddObject(holyFire[0]);
	groupProjectile->AddObject(holyFire[1]);
	groupProjectile->AddObject(holyFire[2]);

	holyWater[0] = new HolyWater(spriteHandler, this);
	holyWater[1] = new HolyWater(spriteHandler, this);
	holyWater[2] = new HolyWater(spriteHandler, this);
	groupProjectile->AddObject(holyWater[0]);
	groupProjectile->AddObject(holyWater[1]);
	groupProjectile->AddObject(holyWater[2]);

}

// gọi ở đầu game_run
void World::Update(float _DeltaTime)
{
	// nếu đang tạm ngừng thì không update
	if (isPaused)
		return;

	// -- cập nhật danh sách object có thể va chạm
	groupSpecialCollision->GetCollisionSpecial();
	groupQuadtreeCollision->GetCollisionQuadtree();
	// =========-------------------------

	Simon->Update(_DeltaTime);
	//whip->Update(_DeltaTime);
	//-----------
	//medusa->Update(_DeltaTime);
	//snake->Update(_DeltaTime);
	/*
	timer += _DeltaTime;
	if (timer >= 0.2f)
	{
		flash->Next(0, 1);
		timer = 0;
	}*/
	//fish->Update(_DeltaTime);


	// -----------
	if (isFreezed)
	{
		timerFreeze -= _DeltaTime;

		// Update group Item nếu như group Special (đã lấy item) không được Update
		groupItem->UpdateActive(_DeltaTime);

		if (timerFreeze <= 0)
		{
			isFreezed = false;

			// lúc này đang nhạc đánh boss
			//if(boss->isActive)
			//Game::gameSound->playSoundLoop();
			//else
			//{
			switch (castlevania->lvl)
			{
			case 1:
				Game::gameSound->playSoundLoop(LVL1_VAMKILL);
				break;
			case 2:
				Game::gameSound->playSoundLoop(LVL2_STALKER);
				break;
			default:
				break;
			}
			//}

		}
	}
	// không "dừng thời gian" thì mới update hoạt động của mấy cái này
	else
	{
		groupQuadtreeCollision->Update(_DeltaTime);
		groupSpecialCollision->Update(_DeltaTime);
		// thời gian -= _DeltaTime;
	}	

	
	groupProjectile->UpdateActive(_DeltaTime);
	groupEffect->UpdateActive(_DeltaTime);
	// ---------------
}

// gọi bên trong BeginScene() và EndScene();
void World::Render()
{
	
	//whip->Render();
	
	//fish->Render();
	
	//flash->Render(Sprite::cameraX + 512 / 2, Sprite::cameraY - 448 / 2);
	//heart->Render();
	groupQuadtreeCollision->Render();
	groupSpecialCollision->Render();

	groupProjectile->RenderActive();
	Simon->Render();
	groupEffect->RenderActive();
}

//void World::CheckActive(float _DeltaTime) {}

void World::Destroy()
{

}

// gọi hàm này khi bấm enter
void World::PauseSwitch()
{
	Game::gameSound->playSound(PAUSE);
	
	// nếu đang tạm ngừng thì cho nó hết tạm ngừng
	if (isPaused)
	{
		isPaused = false;

		// lúc này đang là nhạc đánh boss
		//if(boss->isActive)
			//Game::gameSound->playSoundLoop();
		//else
		//{
		switch (castlevania->lvl)
		{
		case 1:
			Game::gameSound->playSoundLoop(LVL1_VAMKILL);
			break;
		case 2:
			Game::gameSound->playSoundLoop(LVL2_STALKER);
			break;
		default:
			break;
		}
		//}
	}
	// nếu đang không tạm ngừng => cho nó tạm ngừng
	else
	{
		isPaused = true;

		// lúc này đang là nhạc đánh boss
		//if(boss->isActive)
		//Game::gameSound->stopSound();
		//else
		//{
		switch (castlevania->lvl)
		{
		case 1:
			Game::gameSound->stopSound(LVL1_VAMKILL);
			break;
		case 2:
			Game::gameSound->stopSound(LVL2_STALKER);
			break;
		default:
			break;
		}
		//}
	}
}

// xài "dừng thời gian"
void World::Freeze(float _Time)
{
	// lúc này đang nhạc đánh boss
	//if(boss->isActive)
		//Game::gameSound->stopSound();
	//else
	//{
		switch (castlevania->lvl)
		{
		case 1:
			Game::gameSound->stopSound(LVL1_VAMKILL);
			break;
		case 2:
			Game::gameSound->stopSound(LVL2_STALKER);
			break;
		default:
			break;
		}
	//}

	Game::gameSound->playSound(TICKTICKTICK);

	isFreezed = true;
	timerFreeze = _Time;
}
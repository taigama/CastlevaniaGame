#include "CinematicHost.h"
#include "GroupObject.h"
#include "MainGame.h"
#include "Player.h"
#include "Sprite.h"

CinematicHost::CinematicHost(LPD3DXSPRITE _SpriteHandler, MainGame* _MainGame)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;
	castlevania = _MainGame;

	// gán world cho có thôi chứ không xài đâu :v
	groupElement = new GroupObject(castlevania->world);

	// init vị trí camera
	Sprite::cameraX = 0;
	Sprite::cameraXLeft = 0;
	Sprite::cameraXRight = 0;
	Sprite::cameraY = 448;

	simon_cinematic = new Player(_SpriteHandler, _MainGame->world);
}

CinematicHost::~CinematicHost() {}

// gọi ở đầu game_run
void CinematicHost::Update(float _DeltaTime)
{
	groupElement->Update(_DeltaTime);
	UpdateSimon(_DeltaTime);
}

// gọi bên trong BeginScene() và EndScene();
void CinematicHost::Render()
{
	groupElement->Render();
	simon_cinematic->Render();
}

//void World::CheckActive(float _DeltaTime) {}

void CinematicHost::Destroy()
{
	// 
		//
			//
	// stop watching this, nothing to do here now
}

void CinematicHost::ScriptSimon(int startX, int startY, int moveKey, float timer)
{
	simon_cinematic->Init(startX, startY);
	this->moveKey = moveKey;
	this->timer = timer;
}

void CinematicHost::UpdateSimon(const float &_DeltaTime)
{
	if (timer > 0)
	{
		timer -= _DeltaTime;
		simon_cinematic->Move(moveKey, _DeltaTime);

		//float timescale = _DeltaTime / 2.0f;
		//simon_cinematic->Update(timescale);
		switch (castlevania->lvl)
		{
		case 1:
			simon_cinematic->postX += (simon_cinematic->velocityX * _DeltaTime / 3);
			break;
		case 2:
			simon_cinematic->postX += (simon_cinematic->velocityX * _DeltaTime);
			break;
		default:
			break;
		}
		
		// lúc chạm mốc 0 rồi thì đổi sprite
		if (timer <= 0)
		{
			simon_cinematic->sprite->Next(27,27);
		}
	}
}
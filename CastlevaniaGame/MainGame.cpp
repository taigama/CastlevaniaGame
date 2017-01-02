#include "MainGame.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "OLoader.h"
#include "CinematicHost.h"
#include "CinematicElement.h"

#define SIMON_SPEED 0.2f
#define GROUND 94
#define BACKGROUND_FILE "Resources\\map1_tiled.PNG"
#define VIEW_PORT_Y 448

MainGame::MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate) :Game(hInstance, Name, IsFullScreen, FrameRate)
{
	
	timer = 0;
	timeFlash = 0;
	stage = 1;

	intros[0] = NULL;
	intros[1] = NULL;
}

void MainGame::LoadResources(LPDIRECT3DDEVICE9 _d3ddevice)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(_d3ddevice, &_SpriteHandler);

	world = new World(_SpriteHandler, this);
	world->Init();

	// background ---------------------
	maps[0] = new TileMaps("Resources\\Maps\\map1_tiled.png", _SpriteHandler, 64, 104, 14);
	maps[0]->ReadMatrixFromFile("Resources\\Maps\\map1_matrix.txt", "\t");

	maps[1] = new TileMaps("Resources\\Maps\\map2_tiled.png", _SpriteHandler, 64, 49, 9);
	maps[1]->ReadMatrixFromFile("Resources\\Maps\\map2_matrix.txt", "\t");

	TreeBrs[0] = new BackgroundQuadTree();
	TreeBrs[0]->loadTreeFromFile("Resources\\Maps\\map1_quadtree.txt");

	TreeBrs[1] = new BackgroundQuadTree();
	TreeBrs[1]->loadTreeFromFile("Resources\\Maps\\map2_quadtree.txt");

	ListTileBackgoundID = new int[5000];
	size = 0;

	// gameobject ----------------
	oloaders[0] = new OLoader(1, _SpriteHandler, world);
	oloaders[1] = new OLoader(2, _SpriteHandler, world);

	lvl = 0;

	//NextLevel();
	

	// ------------- cinematics --------------

	// startscreen & objects
	startscreen = new CinematicHost(_SpriteHandler, this);
	startscreen->ScriptSimon(-100, -100, 0, 0);

	CinematicElement* theStartBack = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\start_screen.bmp", 512, 448, 1, 1);
	theStartBack->Script(256, 224, 256, 224, 0, 0, 0, 0, 0, 0, 0);

	CinematicElement* castleAndBat = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\castle_cinematic.bmp", 144, 112, 16, 4);
	castleAndBat->Script(444, 192, 444, 192, 0, 2.3f, 0, 0, 15, 12, 15);

	CinematicElement* btnStart = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\startbutton.bmp", 230, 22, 10, 1);
	btnStart->Script(256, 192, 256, 192, 0, 0, 0, 0, 9, 0, 9);

	//startbutton.bmp

	startscreen->groupElement->AddObject(theStartBack);
	startscreen->groupElement->AddObject(castleAndBat);
	startscreen->groupElement->AddObject(btnStart);
	// ---------------

	

	

	//Sprite::cameraY = 448;

	//Hình dùng để render thanh máu, trái tim, khung chứa đồ trên thanh status 
	statusBar = new Sprite(_SpriteHandler, "Resources\\Sprites\\bar_health.bmp", 8, 16, 4, 4);
	statusboard = new Sprite(_SpriteHandler, "Resources\\Sprites\\blackboard.png", 520, 80, 1, 1);
	weaponSprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", 64, 64, 22, 6);

	screenMode = GAMEMODE_START;
	//NextIntro();
}

// ==========================================================================
// --------------------------MAIN UPDATE FUNCTION ---------------------------
// ==========================================================================

// --------------------------------------
void MainGame::Update(float _DeltaTime)
{
	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START:
		UpdateStartScreen(_DeltaTime);
		break;
		// intro
	case GAMEMODE_INTRO:
		UpdateIntro(_DeltaTime);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		UpdateFrame(_DeltaTime);
		break;
	default:
		break;
	}
}

// ------------------------------
void MainGame::UpdateStartScreen(float _DeltaTime)
{
	startscreen->Update(_DeltaTime);
}

// ------------------------------
void MainGame::UpdateIntro(float _DeltaTime)
{
	intro->Update(_DeltaTime);
	
	// chỉ xuất hiện 1 lúc
	timerIntro -= _DeltaTime;
	if (timerIntro <= 0.0f)
	{
		NextLevel();
	}
}

// ------------------------------
void MainGame::UpdateFrame(float _DeltaTime)
{
	//cap nhat lai danh sach cac ID tile có nằm trong viewport
	size = 0;
	TreeBr->ListObjectInViewPort(ListTileBackgoundID, size);
	
	world->Update(_DeltaTime);
}

// -----------------------------------------------------------
// -----------------------------------------------------------


// --- UI FUNCTION ---
string MainGame::convertScoreFormat(int score)
{
	if (score < 10)
		return "00000" + std::to_string(score);
	else if (score < 100)
		return "0000" + std::to_string(score);
	else if (score < 1000)
		return "000" + std::to_string(score);
	else if (score < 10000)
		return "00" + std::to_string(score);
	else if (score < 100000)
		return "0" + std::to_string(score);
	else
		return std::to_string(score);
}
string MainGame::convertTimeFormat(int timeUI)
{
	if (timeUI < 10)
		return "000" + std::to_string(timeUI);
	else if (timeUI < 100)
		return "00" + std::to_string(timeUI);
	else if (timeUI < 1000)
		return "0" + std::to_string(timeUI);
	else
		return std::to_string(score);
}
string MainGame::convertTwoDigitFormat(int digit)
{
	if (digit < 10)
		return "0" + std::to_string(digit);
	else
		return std::to_string(digit);
}

void MainGame::LoadStatusBar(int curHealth, int curEnemy)
{
	statusboard->Render(160 + Sprite::cameraX, 400 + Sprite::cameraY - _ScreenHeight);
	for (int i = 0; i < curHealth; i++)
	{
		statusBar->Next(0, 0);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 410 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curHealth; i < 16; i++)
	{
		statusBar->Next(1, 1);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 410 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = 0; i < curEnemy; i++)
	{
		statusBar->Next(2, 2);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 396 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curEnemy; i < 16; i++)
	{
		statusBar->Next(3, 3);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 396 + Sprite::cameraY - _ScreenHeight);
	}
	switch (world->Simon->subWeapon)
	{
	case KNIFE:
		weaponSprite->Next(0, 0);
		break;
	case AXE:
		weaponSprite->Next(1, 1);
		break;
	case BOOMERANG:
		weaponSprite->Next(2, 2);
		break;
	case HOLYWATER:
		weaponSprite->Next(3, 3);
		break;
	case WATCH:
		weaponSprite->Next(4, 4);
		break;
	default:
		weaponSprite->Next(-1, -1);
		break;

	}
	weaponSprite->Render(Sprite::cameraX + 245, 395 + Sprite::cameraY - 448);

	switch (world->Simon->weaponNumber)
	{
	case 2:
		weaponSprite->Next(11, 11);
		break;
	case 3:
		weaponSprite->Next(12, 12);
		break;
	default:
		weaponSprite->Next(-1, -1);
		break;
	}
	weaponSprite->Render(Sprite::cameraX + 370, 395 + Sprite::cameraY - 448);
}


// ==========================================================================
// --------------------------MAIN RENDER FUNCTION ---------------------------
// ==========================================================================
// ---  between BeginScene & EndScene ---
void MainGame::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START:
		RenderStartScreen();
		break;
		// intro
	case GAMEMODE_INTRO:
		RenderIntro(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderFrame(d3ddv);
		break;
	default:
		break;
	}
}

// -----------------------
void MainGame::RenderStartScreen()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	startscreen->Render();
	_SpriteHandler->End();
}

// ------------------------
void MainGame::RenderIntro(LPDIRECT3DDEVICE9 d3ddv)
{
	//d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	intro->Render();
	_SpriteHandler->End();
}

// ---------------------
void MainGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)// , int t)
{
	
	
	//d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	if (world->isFlash)
	{
		timer += 0.1f;
		timeFlash += 0.1f;
		if (timer >= 0.3f)
		{
			d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(188, 188, 188));
			timer = 0;
		}
		if (timeFlash > 2.0f)
		{
			world->isFlash = false;
			timeFlash = 0;
		}

	}
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	map->LoadTiledMap(ListTileBackgoundID, size);

	world->Render();

	LoadStatusBar(world->Simon->health, world->boss->HealthDot());
	_SpriteHandler->End();
	//------------Lúc simon ăn thánh giá -> sấm chớp--------

	//-------------------------------------
	//Mấy dòng chữ sẽ hiện lên Status bar
	statusZone1 = "SCORE - " + convertScoreFormat(world->Simon->score) +
		"                  TIME "
		+ convertTimeFormat(world->Simon->timeUI) +
		"                 STAGE "+ convertTwoDigitFormat(lvl)+
		"\n" +
		"\nPLAYER" +
		"\nENEMY";
	statusZone2 = convertTwoDigitFormat(world->Simon->heart) + "\n"
		+ convertTwoDigitFormat(world->Simon->P);

}
// ----------------------------------------------------
//------------------------------------------------------
// ----------------------------------------------------


void MainGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime)		//Chạy khi nhấn giữ
{
	
	switch (screenMode)
	{
		// start screen --------------------------------------------------------
	case GAMEMODE_START:
		break;
	case GAMEMODE_INTRO:
		break;
		// game running ---------------------------------------------------------
	case GAMEMODE_GAMERUN:
	{
		// nếu world đang pause -> ko xử lý
		if (world->isPaused)
			return;

		if (world->Simon->onStair <= 0) // truong hop chua leo cau thang
		{
			if (IsKeyDown(DIK_DOWN))
			{
				if (world->Simon->onStair == 0)
				{
					world->Simon->Down(-1);
					return;
				}

				//-- trang thai khong lien quan den cau thang
				if (IsKeyDown(DIK_LEFT))
				{
					world->Simon->isRight = false;
				}
				else if (IsKeyDown(DIK_RIGHT))
				{
					world->Simon->isRight = true;
				}
				world->Simon->Move(0, _DeltaTime);
				world->Simon->Down(1);
			}
			else // khong nhan phim DOWN
			{
				//truong hop nhan phim UP
				if (IsKeyDown(DIK_UP))
				{
					if (world->Simon->onStair == 0)
					{
						if (world->Simon->stairType == STAIR_UPLEFT || world->Simon->stairType == STAIR_UPRIGHT)
						{
							world->Simon->onStair = 1;
							world->Simon->isMoveToX = true;
							world->Simon->MovingOnStair(1);

							return;
						}
					}

				}

				//cac trang thai ngoai cau thang
				world->Simon->Down(0);

				if (IsKeyDown(DIK_LEFT))
				{
					world->Simon->Move(-1, _DeltaTime);
				}
				else if (IsKeyDown(DIK_RIGHT))
				{
					world->Simon->Move(1, _DeltaTime);
				}
				else
				{
					world->Simon->Move(0, _DeltaTime);
				}
			}
		}


		else // truong hop dang leo cau thang
		{
			if (IsKeyDown(DIK_UP) ||
				(IsKeyDown(DIK_RIGHT) && ((world->Simon->stairType == STAIR_UPRIGHT) || (world->Simon->stairType == STAIR_DOWNLEFT))) ||
				(IsKeyDown(DIK_LEFT) && ((world->Simon->stairType == STAIR_UPLEFT) || (world->Simon->stairType == STAIR_DOWNRIGHT))))
			{
				world->Simon->MovingOnStair(1);
			}
			if (IsKeyDown(DIK_DOWN) ||
				(IsKeyDown(DIK_RIGHT) && ((world->Simon->stairType == STAIR_UPLEFT) || (world->Simon->stairType == STAIR_DOWNRIGHT))) ||
				(IsKeyDown(DIK_LEFT) && ((world->Simon->stairType == STAIR_UPRIGHT) || (world->Simon->stairType == STAIR_DOWNLEFT))))
			{
				world->Simon->MovingOnStair(-1);
			}
			world->Simon->MovingOnStair(0);
		}

		// ----------- cheat ------------
		if (IsKeyDown(DIK_Q))
		{
			world->Simon->velocityY = 400;
		}
	}
		break;
		// ------------------------------------------------------------------
	default:
		break;
	}

	
}

void MainGame::OnKeyDown(int KeyCode)
{

	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START://------------------------------------------------
	{
		if (KeyCode == DIK_RETURN)
		{
			NextIntro();
		}
	}
		break;
		// intro
	case GAMEMODE_INTRO:
		break;
		// game running
	case GAMEMODE_GAMERUN:// -------------------------------------------------
	{
		// các phím có thể bấm kể cả đã paused
		switch (KeyCode)
		{
			// bấm enter -> chuyển qua lại trạng thái pause
		case DIK_RETURN:
			world->PauseSwitch();
			break;
			// bấm C -> đổi vũ khí
		case DIK_C:
			world->Simon->subWeapon++;
			if (world->Simon->subWeapon == HOLYFIRE)
				world->Simon->subWeapon++;
			else if (world->Simon->subWeapon > WATCH)
				world->Simon->subWeapon = 1;
			break;
			// bấm + -> tăng đạn
		case DIK_NUMPADPLUS:
			world->Simon->heart++;
			break;
		}

		// không cho bấm nếu đã paused
		if (world->isPaused)
			return;

		switch (KeyCode)
		{
		case DIK_LSHIFT:
		case DIK_SPACE://Chỉ nhảy khi vừa nhấn, nhấn giữ không có tác dụng
			world->Simon->Jump();
			break;
		case DIK_LCONTROL:
			if (IsKeyDown(DIK_UP))
				world->Simon->ActivateWeapon();
			else
				world->Simon->Attack(0);
			break;
		case DIK_M:
			//NextLevel();
			NextIntro();
			break;
		}
	}
		break;
		// ------------------------------------------------------
	default:
		break;
	}
}

void MainGame::OnKeyUp(int KeyCode) {}

MainGame::~MainGame()
{

}

// hàm chuyển lvl
void MainGame::NextLevel()
{
	
	// cập nhật các con trỏ background theo lvl
	TreeBr = TreeBrs[lvl - 1];
	map = maps[lvl - 1];

	// cập nhật các con trỏ object theo lvl
	oloader = oloaders[lvl - 1];
	oloader->Reload();
	this->screenMode = GAMEMODE_GAMERUN;
	UpdateFrame(0.0f);

	switch (lvl)
	{
	case 1:
		Game::gameSound->playSoundLoop(LVL1_VAMKILL);
		world->Simon->timeUI = 300;
		break;
	case 2:
		Game::gameSound->playSoundLoop(LVL2_STALKER);
		world->Simon->timeUI = 600;
		break;
	default:
		break;
	}
}

void MainGame::NextIntro()
{
	lvl++;
	if (lvl > 2)
		lvl = 1;

	switch (lvl)
	{
	case 1:
	{
		Game::gameSound->stopSound(LVL2_STALKER);
		Game::gameSound->playSound(INTRODUCE1);
		timerIntro = 9.0f;

		// 1st intro
		if (intros[0] != NULL)
		{
			delete intros[0];
		}

		intros[0] = new CinematicHost(_SpriteHandler, this);
		intros[0]->ScriptSimon(550, 80, -1, 6);

		CinematicElement* background1 = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\intro1.bmp", 512, 448, 1, 1);
		background1->Script(256, 224, 256, 224, 0, 0, 0, 0, 0, 0, 0);

		CinematicElement* flyShip = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\object_cinematic.bmp", 64, 32, 4, 2);
		flyShip->Script(470, 302, 324, 302, 10, 10, 1, 0, 0, 0, 0);

		CinematicElement* bat1 = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\object_cinematic.bmp", 32, 32, 8, 4);
		bat1->Script(300, 306, 245, 332, 4, 10, 1, 2, 3, 2, 3);

		CinematicElement* bat2 = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\object_cinematic.bmp", 32, 32, 8, 4);
		bat2->Script(44, 188, 262, 294, 30, 10, 1, 2, 3, 2, 3);

		intros[0]->groupElement->AddObject(background1);
		intros[0]->groupElement->AddObject(flyShip);
		intros[0]->groupElement->AddObject(bat1);
		intros[0]->groupElement->AddObject(bat2);
		// --------
	}
		break;
	case 2:
	{
		Game::gameSound->stopSound(LVL1_VAMKILL);
		Game::gameSound->playSound(INTRODUCE2);
		timerIntro = 7;

		// 2st intro
		if (intros[1] != NULL)
		{
			delete intros[0];
		}
		intros[1] = new CinematicHost(_SpriteHandler, this);
		intros[1]->ScriptSimon(-180, 80, 1, 10);

		CinematicElement* background2 = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\intro2.bmp", 784, 370, 1, 1);
		background2->Script(860, 150, 340,150, 270, 1.75f, 1, 0, 0, 0, 0);
		CinematicElement* batSquare = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\object_cinematic.bmp", 32, 32, 8, 4);
		batSquare->Script(-16, -138, 188, 182, 0, 1.8f, 0, 4, 5, 4, 5);

		CinematicElement* square = new CinematicElement(_SpriteHandler, "Resources\\Cinematics\\object_cinematic.bmp", 32, 32, 8, 4);
		square->Script(-32, -32, 308, 124, 0, 1.8f, 0, 6, 7, 6, 7);

		intros[1]->groupElement->AddObject(background2);
		intros[1]->groupElement->AddObject(batSquare);
		intros[1]->groupElement->AddObject(square);

		// -----------
	}
		break;
	default:
		break;
	}
		
	Sprite::cameraXLeft = 0;
	Sprite::cameraXRight = 0;
	Sprite::cameraX = 0;
	Sprite::cameraY = 448;
	statusZone1 = "";
	statusZone2 = "";
	intro = intros[lvl - 1];
	this->screenMode = GAMEMODE_INTRO;
	
	UpdateIntro(0.0f);
}
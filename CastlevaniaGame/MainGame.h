#pragma once
#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#define GAMEMODE_START 0
#define GAMEMODE_INTRO 1
#define GAMEMODE_GAMERUN 2

#include "game.h"
#include "World.h"
#include "ThamSo.h"

class MainGame :public Game
{
public:
	MainGame() {}
	MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate);
	~MainGame();

	LPD3DXSPRITE _SpriteHandler;		//Dung truyen vao spritehandler cua class Sprite
	DWORD last_time;

	// ========== MAP ============

	// ------ update K_1.7
	//LPDIRECT3DSURFACE9 Background;
	//Sprite* bg;
	// background -----------
	//su dung TileMaps *_ by Le _*
	TileMaps *map;
	TileMaps *maps[2];
	//map <int, int > ListTileBackgoundID;

	int *ListTileBackgoundID;
	int size;

	//QuadTree Background
	BackgroundQuadTree *TreeBr;
	BackgroundQuadTree *TreeBrs[2];

	// game object ----------
	OLoader* oloader;
	OLoader* oloaders[2];

	// cinematics
	CinematicHost* startscreen;
	CinematicHost* intro;
	CinematicHost* intros[2];


	// -----------

	// manage level
	int lvl;
	int screenMode;
	float timerIntro;
	void NextLevel();
	void NextIntro();
	// --------
	// ============---------------

	World *world;


	// UI
	int score;
	int stage;

	float timer;
	float timeFlash;

	Sprite* statusBar;
	Sprite* statusboard;
	Sprite* weaponSprite;




protected:
	string convertScoreFormat(int score);
	string convertTimeFormat(int timeUI);
	string convertTwoDigitFormat(int digit);
	void LoadStatusBar(int curHealth, int curEnemy);
	
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddevice);
	// ---------------------------
	virtual void Update(float _DeltaTime);
	virtual void UpdateStartScreen(float _DeltaTime);
	virtual void UpdateIntro(float _DeltaTime);
	virtual void UpdateFrame(float _DeltaTime);
	// -----------------------------
	virtual void Render(LPDIRECT3DDEVICE9 d3ddevice);
	virtual void RenderStartScreen();
	virtual void RenderIntro(LPDIRECT3DDEVICE9 d3ddv);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddevice);// , int Delta);
	// -------------------------------
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddevice, float _DeltaTime);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

#endif
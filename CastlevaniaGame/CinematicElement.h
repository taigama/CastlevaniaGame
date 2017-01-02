#pragma once
#include "GameObject.h"

class CinematicElement :
	public GameObject
{
public:
	float targetX, targetY; // vị trí đi tới
	float speed, timer;// thời gian chuyển tới
	bool isWalk;
	int keyMode;// moving - alternating
	
	int indexSpriteFirst, indexSpriteLast;
	int alterSpriteFirst, alterSpriteLast;


	// ------------ function
	CinematicElement(LPD3DXSPRITE SpriteHandler, LPCSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	~CinematicElement();

	// init
	void Script(float _X, float _Y,
		float _TargetX, float _TargetY,
		float _Speed, float _Timer,
		bool _IsWalk,
		int firstIndex, int lastIndex,
		int firstAlter, int lastAlter);

	// update & render
	virtual void Update(const float &_DeltaTime);	// update per frame
	virtual void Render();							// render per frame

};


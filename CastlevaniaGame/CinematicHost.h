#ifndef _CINEMATICHOST_H_
#define _CINEMATICHOST_H_
#include "ThamSo.h";
class CinematicHost
{
public:
	// con trỏ đến "phần cứng" sprite
	LPD3DXSPRITE spriteHandler;
	// con trỏ đến "phần cứng" game
	MainGame* castlevania;

	// nhóm các đối tượng trong này
	GroupObject *groupElement;

	// simon rieng
	Player *simon_cinematic;
	int moveKey;
	float timer;

	// các hàm
	CinematicHost(LPD3DXSPRITE _SpriteHandler, MainGame* _MainGame);
	~CinematicHost();

	void Update(float _DeltaTime);
	void Render();
	void Destroy();

	void ScriptSimon(int startX, int startY, int moveKey, float timer);
	void UpdateSimon(const float &_DeltaTime);
};

#endif // !_CINEMATICHOST_H_

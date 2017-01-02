#ifndef _MEDUSA_H_
#define _MEDUSA_H_

#include "Enemy.h"

class Medusa :
	public Enemy

{
public:
	float thoigiandung,timer,TimeToAttack, timeSleeping;
	double a;
	bool isSleeping;
	int lineY;
	//Enemy* snake;
	Medusa();
	Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Medusa();

	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
	void ActivateSnake();

	// trả về tỉ lệ máu / 16
	virtual int HealthDot();
};
#endif // !_MEDUSA_H_
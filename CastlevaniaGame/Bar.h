#ifndef _BAR_H_
#define _BAR_H_

#include "ThamSo.h"
#include "Ground.h"

class Bar : public Ground
{
private:
	// dùng trong di chuyển
	bool isRight;
	float wait;

	// dùng trong xét va chạm
	float collisionScale;
	void HandlingCollision(const float &_DeltaTime);
	GameObject* tempObject;
public:
	Bar(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Bar();

	virtual void Init(int _X, int _Y, int rubbish1, int rubbish2);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
};

#endif

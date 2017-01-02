#ifndef _GRINDER_H_
#define _GRINDER_H_

#include "Zone.h"

class Grinder :
	public Zone
{

public:
	Sprite * spriteTop;
	float pos;
	int maxCount;
	int numberCount;
	float anchorY; //biến xác định tọa độ điểm trên cùng (điểm treo) của grinder
	bool isLifting; //xác định trạng thái đang được nâng lên

	Grinder(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Grinder();

	virtual void Update(const float &_DeltaTime);
	virtual void Render();

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int _Stack, int rubbish1,
		int rubbish2, int rubbish3, int rubbish4);
	virtual void Collision(Player *actor, const float &_DeltaTime);
};
#endif // !_GRINDER_H_



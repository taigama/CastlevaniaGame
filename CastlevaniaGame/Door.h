#ifndef _DOOR_H_
#define _DOOR_H_

#include "Zone.h"
class Door :
	public Zone
{
public:
	// vị trí mới của camera
	int newLeft;
	int newRight;
	// hướng
	int direct;
	bool isTagged; //bien xac dinh simon co cham door hay không
	bool doorOpened; // xac trang thai cua da mo xong
	bool doorClocked; //xac dinh cua khong bao gio duoc qua nua;


	Door(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Door();

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int rubbish1, int rubbish2,
		int camXLeft, int camXRight, int direct);
	virtual void Collision(Player *actor, const float &_DeltaTime);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
};

#endif // !_DOOR_H_
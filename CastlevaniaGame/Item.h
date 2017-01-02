#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObject.h"
#include "Player.h"


class Item :
	public GameObject

{
public:
	int itemType;
	float timeSurvive;
	float timeUp; 
	bool Stop;
	Item();
	Item(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Item();

	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, int _level);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision(Player *player);
	void CheckGroundCollision(World *manager, const float _DeltaTime);
	static Item* CreateItem(int itemType, int _X, int _Y, LPD3DXSPRITE _SpriteHandler,
		World *_manager);
	void GetMultiSprite(int itemType);
};
#endif // !_Item_H_
#ifndef _WORLD_H_
#define _WORLD_H_
#include "Player.h"
#include "Whip.h"
#include "Ghoul.h"
#include "RedBat.h"
#include "BlueBat.h"
#include "Panther.h"
#include "Fish.h"
#include "Item.h"
#include "Effect.h"
#include "GateWay.h"
#include "ThamSo.h"
#include "VamBat.h"
#include "Medusa.h"
#include "Snake.h"
#include "Knight.h"
//-------Item--------
#include "Heart.h"
#include "BigHeart.h"
#include "MoneyBag.h"
#include "Chicken.h"
#include "GetSubWeapon.h"
#include "Cross.h"
#include "Crystal.h"
#include "Multiply.h"
#include "Potion.h"
#include "Treasure.h"
#include "WhipUpgrade.h"

//------Effect-----
#include "Hit.h"
#include "Rubble.h"
#include "Spirit.h"
#include "Bubble.h"
#include "BossSpirit.h"
//------Projectile
#include "Whip.h"
#include "Knife.h"
#include "Boomerang.h"
#include "Axe.h"
#include "HolyFire.h"
#include "HolyWater.h"
//------Stair-------
#include "Stair.h"
class World
{
public:
	// con trỏ đến "phần cứng" sprite
	LPD3DXSPRITE spriteHandler;
	// con trỏ đến "phần cứng" game
	MainGame* castlevania;

	Sprite* background;
	Player* Simon;

	//Fish* fish;
	//Ghoul *ghoul;
	//RedBat *redBat;
	//BlueBat *blueBat;
	//Knight *panther;
	//Item *item;
	//VamBat *vamBat;
	//Medusa *medusa;
	//Snake *snake;

	//Projectile
	Whip* whip;
	Boomerang *boo[3];
	Knife *knife[3];
	Axe *axe[3];
	HolyFire *holyFire[3];
	HolyWater *holyWater[3];
	
	// group - managing object
	GroupObject *groupSpecialCollision;
	GroupObject *groupQuadtreeCollision;
	GroupObject *groupItem;
	GroupObject *groupEffect;
	GroupObject *groupProjectile;

	// update by OLoader, init as NULL
	GroupObject* groupEnemy;
	OTreeNode* rootGONode;
	// con trỏ boss
	Enemy* boss;
	
	// danh cho fx
	bool isPaused;
	bool isFlash;
	// int local; //bien random vi tri cua c?

	bool isFreezed;
	float timerFreeze;


	World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame);
	~World();

	void Init();
	void Update(float _DeltaTime);
	void Render();
	//void CheckActive(float _DeltaTime);
	void Destroy();

	// --------------
	void PauseSwitch();
	void Freeze(float _Time);
};


#endif // !_WORLD_H_

#ifndef _THAMSO_H_
#define _THAMSO_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>

// class prototype
class GameObject;	// GameObject.h
class Collider;		// Misc.h
class DropTable;	// Misc.h
class World;		// World.h
class MainGame;
class Sprite;		// Sprite.h

class Player;
// ---- update K_1.7
// gameobject prototype
class Enemy;
class Destructible;

// ground prototype
class Ground;
class ColliderBlock;
class Brick;
class Bar;

class Stair;

class Zone;

class GroupObject;

class OTreeNode;
class OLoader;
// ---------------
// cinematic
class CinematicHost;



// ===== --- GAME OBJECT --- =====
#define PLAYER_TYPE 1
#define PROJECTILE_TYPE 2
#define EFFECT_TYPE 3
#define ITEM_TYPE 4
#define ENEMY_TYPE 5
#define DESTRUCTIBLE_TYPE 6
#define GROUND_TYPE 7
#define STAIR_TYPE 8
#define ZONE_TYPE 9
#define CINEMATIC_TYPE 10

// ===== --- ENEMY --- ===== 5
#define REDBAT 1
#define BLUEBAT 2
#define GHOUL 3
#define FISH 4
#define PANTHER 5
#define ENEMYFIRE 6

#define VAMBAT 7
#define MEDUSA 8
#define SNAKE 9

#define KNIGHT 10
#define HEAD 11
#define GHOST 12
#define BONE 13

// ===== --- PROJECTILE --- ===== 2
#define WHIP 1
#define KNIFE 2
#define HOLYWATER 3
#define HOLYFIRE 4
#define AXE 5
#define BOOMERANG 6
#define WATCH 7

// ===== --- DESTRUCTIBLE --- ===== 6
#define DESTRUCTIBLE_TORCH 1
#define DESTRUCTIBLE_CANDLE 2

// ===== --- GROUND --- ===== 7
#define GROUND_BLOCK 1

#define GROUND_BRICK1 2 // chiếm 4 suất groundType trong object.txt
#define GROUND_BRICK2 3
#define GROUND_BRICK3 4
#define GROUND_BRICK4 5

#define GROUND_BAR 6

// ===== --- ZONE --- ===== 9
#define ZONE_GATEWAY 1
#define ZONE_STAND 2
#define ZONE_CROUCH 3

#define ZONE_DEAD 4 // chiếm 2 suất zoneType
#define ZONE_GRINDER 5

#define ZONE_SPAWNER 6
#define ZONE_BATTLEBOSS 7
#define ZONE_GATE 8
#define ZONE_DOOR 9

// ===== --- STAIR --- ===== 8
#define STAIR_UPRIGHT 1
#define STAIR_UPLEFT 2
#define STAIR_DOWNRIGHT 3
#define STAIR_DOWNLEFT 4

// ===== --- EFFECT --- ===== 3
#define EFFECT_HIT 1
#define EFFECT_RUBBLE 2
#define EFFECT_SPIRIT 3
#define EFFECT_BUBBLE 4
#define EFFECT_BOSSSPIRIT 5

// ===== --- ITEM --- ===== 4
#define HEART 1
#define BIGHEART 2

#define BAG100 3 // chiếm 3 suất itemType trong object.txt
#define BAG400 4
#define BAG700 5

#define BAG1000 6 // BIGMONEY
#define WHIPUPGRADE 7
#define GETKNIFE 8
#define GETAXE 9
#define GETWATER 10
#define GETWATCH 11
#define GETBOOMERANG 12
#define CROSS 13
#define POTION 14
#define CHICKEN 15
#define MULTIPLY 16
#define CROWN 17 // VUONG MIEN
#define TREASURE 18 // HOM
#define CRYSTAL 19
// ====---SOUND--=======
#define INTRODUCE1 0
#define INTRODUCE2 1
#define LVL1_VAMKILL 2
#define LVL2_STALKER 3
#define BOOMERANG 4
#define BRICKBREAK 5
#define DOWNWATER 6
#define EATCROSS 7
#define EATCRYSTAL 8
#define EATHEART 9
#define EATMONEY 10
#define EATPOTION 11
#define EATWEAPON_CHICKEN 12
#define HITSOFT 13
#define HITSTEEL 14
#define HOLYWATERBREAK 15
#define INJURED 16
#define SOUNDKNIFE 17
#define MAINGATE 18
#define PAUSE 19
#define POTIONIMMORTAL 20
#define SHOWSECRETITEM 21
#define TETRENCAOXUONG 22
#define TICKTICKTICK 23
#define TIMENEAREND 24
#define UPWATER 25
#define WHIPATTACK_AXE 26

#endif // !_THAMSO_H_

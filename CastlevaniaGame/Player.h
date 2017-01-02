#ifndef _PLAYER_H_
#define _PLAYER_H_

// Hướng leo cầu thang
#define STAIR_UPRIGHT 1
#define STAIR_UPLEFT 2
#define STAIR_DOWNRIGHT 3
#define STAIR_DOWNLEFT 4

#include "GameObject.h"

class Player :
	public GameObject
{
public:
	float timeUI;
	int tempGround;

	//cac bien kiem soat trang thai
	bool isRight;	//trang thai quay sang phai
	bool isJump;	//trang thai nhay
	bool downJump;	//trang thai nhay xuong
	bool isCrouch;	//trang thai ngoi
	bool isAttack;  //trang thai danh
	bool isJumpAttack; // trang thai nhay danh;
	bool killingMoment; //trang thai vung roi
	bool isHitted;  //trạng thai bị thuong
	bool isShocked;  //trang thai shock
	bool isImmortal; //trang thai bat tu
	bool isChangeFrame;
	bool isDead;
	int ChangingScene; // bien thu tu cac hanh dong khi chuyen scene

	bool isMoveToX; //biến xác định trạng thái simon bị chuyển đến vị trí X
	float DestinationX; // đích đến của Simon khi bị chuyển đến 1 vị trí xác định

	bool isStationary; // trạng thái đứng yên

					   // stair direction key
	int onStair; //< -1 nếu không ở gần cầu thang >; < 0 nếu ở đầu cầu thang > < 1 nếu đang trong cầu thang >
	int stairType; // loại cầu thang mà Player đang đứng
	int stairMoveKey; // Lệnh điều khiển chuyển động trên cầu thang < -1 đi xuống>; < 0 đứng yên >; < 1 đi lên >
	bool animStart; // bắt đầu thực hiện động tác đi cầu thang
	bool isClimbing; // xác đinh Player có phải đang đi lên hay không?
	float timeStairAnim; // biến tính thời gian để chuyển sprite
	bool isShowTime; // xác định Player đang thực hiện  1 động tác đi cầu thang


	float timeImmortal;//thoi gian bat tu

	Sprite *spriteLeft;
	Sprite *spriteRight;
	Sprite *potionLeft;
	Sprite *potionRight;
	Sprite *usualLeft;
	Sprite *usualRight;
	bool atePotion;

	Zone *zone;

	int weaponLevel;	// whip level
	int weaponNumber;	// số subweapon có thể ném liên tiếp
	bool isUsingWeapon;
	int invicinbleTimer;
	int subWeapon;

	int heart;			// số trái tim (số lượng đạn)
	int health;			// chừng nào mất 1 mạng (P)
	int P;
	int score;

	// dùng cho việc hồi sinh
	int checkpointX;
	int checkpointY;
	int savedCamXLeft;
	int savedCamXRight;
	int savedCamY;



	int savedOnStair;
	bool savedIsClimbing;
	int savedStairType;

	// constructor & destructor
	Player(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Player();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	void Player::CollisionObject(float _DeltaTime);

	//hàm update vị trí camera
	void UpdateCamera(float cameraX, float cameraY, float cameraXLeft, float cameraXRight);

	//ham mo phong chuyen dong di chuyen cua simon
	void BeenMoved(int moveKey, const float &_DeltaTime);

	// input function
	// Khi có input từ bàn phím => gọi các hàm này
	// nhấn giữ
	void Move(int moveKey, const float &_DeltaTime);// -1 <-    0      1 ->

	void Up(int upKey);
	void Down(int downKey);

	// nhấn 1 lần
	void Jump();
	void Attack(int keyAttack);
	void Injured(int keyInjured);
	void MovingOnStair(int keyMove);
	void ActivateWeapon();


	// các hàm update các trạng thái của simon
	void UpdateWhenJumping(float _DeltaTime);
	void UpdateWhenAttack(float _DeltaTime);
	void UpdateWhenAttackOnStair(float _DeltaTime);
	void UpdateWhenOnStair(float _DeltaTime);
	void UpdateWhenMoveToPossionX(float _DeltaTime);
	void UpdateWhenChangingScene(float _DeltaTime);

};

#endif

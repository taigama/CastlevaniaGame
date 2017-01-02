#include "CinematicElement.h"
#include <math.h>


CinematicElement::CinematicElement(LPD3DXSPRITE SpriteHandler, LPCSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	objectType = CINEMATIC_TYPE;
	sprite = new Sprite(SpriteHandler, FilePath, Width, Height, Count, SpritePerRow);
}


CinematicElement::~CinematicElement()
{
}

// Script vị trí / mục tiêu / tốc độ / thời gian / chuyển sprite
void CinematicElement::Script(float _X, float _Y,
	float _TargetX, float _TargetY,
	float _Speed, float _Timer,
	bool _IsWalk,
	int firstIndex, int lastIndex,
	int firstAlter, int lastAlter)
{
	// updating
	postX = _X; postY = _Y;
	targetX = _TargetX; targetY = _TargetY;
	speed = _Speed; timer = _Timer;
	isWalk = _IsWalk;

	// updating image - phrase  1
	indexSpriteFirst = firstIndex;
	indexSpriteLast = lastIndex;
	sprite->Next(indexSpriteFirst, indexSpriteFirst);

	// update image - phrase 2
	alterSpriteFirst = firstAlter;
	alterSpriteLast = lastAlter;

	keyMode = 0;
}

void CinematicElement::Update(const float &_DeltaTime)
{
	switch (keyMode)
	{
		// --------------- trạng thái đang ở đâu đó, chuẩn bị xuất hiện ở target -----------
	case 0:
	{
		//	chuyển sprite 
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite = 0;
			sprite->Next(indexSpriteFirst, indexSpriteLast);
		}

		if (isWalk) // nếu là đi từ từ chứ không phải tele
		{
			// khoảng cách từ element đến target ------
			float distance =
				sqrt(
					pow(targetX - this->postX, 2)
					+ pow(targetY - this->postY, 2)
				);

			// tính hướng đi của element
			float scale = distance / speed; // toc do cua con nay
			velocityX = (targetX - this->postX) / scale;
			velocityY = (targetY - this->postY) / scale;

			postX += velocityX*_DeltaTime;
			postY += velocityY*_DeltaTime;
			// ----------------
		}

		timer -= _DeltaTime;
		// đổi chế độ
		if (timer <= 0)
		{
			keyMode = 1;
			if (!isWalk)
			{
				postX = targetX;
				postY = targetY;
			}
		}
		break;
	}
	// --------------- trạng thái ngừng di chuyển, chỉ render -------------
	case 1:
	{
		//	chuyển sprite 
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite = 0;
			sprite->Next(alterSpriteFirst, alterSpriteLast);
		}
		
		break;
	}
	default:
		break;
	}

}

void CinematicElement::Render()
{
	sprite->Render(postX,postY);
}
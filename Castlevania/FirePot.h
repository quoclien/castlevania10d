#pragma once
#include "Holder.h"
#include "Brick.h"

#define FIREPOT_GRAVITY			0.002f
#define FIREPOT_DEFLECT_SPEED 0.2f

#define	FIREPOT_STATE_IDLE	0
#define FIREPOT_STATE_DIE	100

#define FIREPOT_ANI_IDLE	0
#define FIREPOT_ANI_DIE	1

#define FIREPOT_BBOX_WIDTH	32
#define FIREPOT_BBOX_HEIGHT	64

class CFirePot :public CHolder
{
	float start_x;			
	float start_y;
public:
	CFirePot(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	//CFirePot() {};

	virtual void Render();

	//virtual void SetState(int state);

	//void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
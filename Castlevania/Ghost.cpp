﻿#include "Ghost.h"
#include "Simon.h"
CGhost::CGhost(float x, float y, int nx):CEnemy()
{
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->type = 1; // 1 là ghost nên thay bằng enum
	isActive=true;

}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vx = GHOST_WALKING_SPEED * this->nx;
	CGameObject::Update(dt);
	vy += GHOST_GRAVITY * dt;
	vector<LPGAMEOBJECT> coObjectsGhost;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))

			coObjectsGhost.push_back(coObjects->at(i));
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if(isActive)
	  CalcPotentialCollisions(&coObjectsGhost, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0){}
		if (ny != 0) vy = 0;


		
		 //Collision logic with other objects
		
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<Simon *>(e->obj)) // if e->obj is simon 
		//	{
		//	}
		//}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGhost::Render() {
	ani = GHOST_ANI_RIGHT;
	if (this->nx < 0)
		ani = GHOST_ANI_LEFT;

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);
	RenderBoundingBox();
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}

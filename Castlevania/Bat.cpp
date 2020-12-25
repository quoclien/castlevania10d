﻿#include "Bat.h"
#include "Simon.h"
CBat::CBat(float x, float y, int nx, int itemType) :CEnemy()
{
	SetItem(itemType);
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->type = 20; // 20 là bat nên thay bằng enum
	isActive = true;
	vx = BAT_FLY_SPEED_X * this->nx;
}
void CBat::SetState(int state)
{
	this->state = state;

	if (state == ENEMY_STATE_DIE) {
		die_time = GetTickCount();
		vx = 0;
	}
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == ENEMY_STATE_DIE && ((GetTickCount() - die_time) > BAT_DIE_TIME))
		isVanish = true;
	else if (state != ENEMY_STATE_DIE)
		vx = BAT_FLY_SPEED_X * this->nx;

	CGameObject::Update(dt);
	vy += amplitude;
	
	if (vy >= BAT_FLY_SPEED_Y || vy <= -BAT_FLY_SPEED_Y)
		amplitude *= -1;

	x += dx;
	y += dy;

}

void CBat::Render() {

	ani = BAT_ANI_RIGHT;
	if (this->nx < 0) ani = BAT_ANI_LEFT;
	if (state == ENEMY_STATE_DIE) 
		ani = BAT_ANI_DIE;

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);
	RenderBoundingBox();
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
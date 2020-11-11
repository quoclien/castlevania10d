#include "Candle.h"
void CCandle::SetItem(int itemType) {
	ItemType type;
	switch (itemType)
	{
	case 1:
		type = ITEM_BIG_HEART;
		break;
	case 2:
		type = ITEM_MONEY_BAG_RED;
		break;
	case 3:
		type = ITEM_MONEY_BAG_WHITE;
		break;
	case 4:
		type = ITEM_MONEY_BAG_BLUE;
		break;
	case 5:
		type = ITEM_WHIP_RED;
		break;
	case 6:
		type = ITEM_WHIP_BLUE;
		break;
	case 7:
		type = ITEM_DAGGER;
		break;
	case 8:
		type = ITEM_STOP_WATCH;
		break;
	case 9:
		type = ITEM_CROSS;
		break;
	case 10:
		type = ITEM_HOLY_WATER;
		break;
	default:
		type = ITEM_SMALL_HEART;
		break;
	}
	this->itemType = type;
}
CCandle::CCandle(int itemType)
{

	SetState(CANDLE_STATE_IDLE);
	SetItem(itemType);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CCandle::SetState(int state)
{
	this->state = state;
	if (state == CANDLE_STATE_BREAK)
		break_time = GetTickCount();
}

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void CCandle::Render()
{
	int ani = CANDLE_ANI_IDLE;
	if (state == CANDLE_STATE_BREAK) {
		ani = CANLDE_ANI_BREAK;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (IsBroken())
	{
		item.Update(dt, coObjects);
	}*/
	CGameObject::Update(dt, coObjects);
	vy = 0;

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
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

		// block 
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (ny != 0) {
			vy = 0;
		}

		if (state == CANDLE_STATE_BREAK && ((GetTickCount() - break_time) > CANDLE_BREAK_TIME))
		{
			this->isVanish = true;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
#include "Board.h"
#include "Dagger.h"
#include"Simon.h"
#include"StopWatch.h"
#include "HolyWater.h"

#define DAGGER_SPRITE		40016
#define STOPWATCH_SPRITE	40012
#define	HOLYWATER_SPRITE	40019
Board* Board::_instance = NULL;

Board* Board::Getinstance()
{
	if (_instance == NULL)
		_instance = new Board();
	return _instance;
}

Board::Board()
{
	ani_set = CAnimationSets::GetInstance()->Get(BOARD_ID);
	HP_set = CAnimationSets::GetInstance()->Get(8);
	font = new CFont();
	doubleShot = CSprites::GetInstance()->Get(40024);
}

Board::~Board()
{
}

void Board::Render()
{
	ani_set->at(0)->Render(x, y);
	font->Render(std::to_string(score), x + 105, 15, 8);
	font->Render(std::to_string(time), x + 300, 15, 4);
	font->Render(std::to_string(stage), x + 480, 15, 2);
	font->Render(std::to_string(simon->GetHearts()), x + 400, 35, 2);
	font->Render(std::to_string(simon->GetLife()), x + 400, 55, 2);
	//Khung HP 
	for (int i = 0; i < 16; i++)
	{
		HP_set->at(39)->Render((x + 120) + i * 10, 32);
		HP_set->at(39)->Render((x + 120) + i * 10, 52);
	}
	//enemy
	for (int i = 0; i < 16; i++)
	{
		HP_set->at(38)->Render((x + 120) + i * 10, 52);
	}
	//simon
	for (int i = 0; i < board_health; i++)
	{
		HP_set->at(37)->Render((x + 120) + i * 10, 32);
	}
	if(time_flag)
		healtime = GetTickCount();
	if (sprite != NULL)
		sprite->Draw(x+312.0f, y +32.7f,255);
	if(Simon::GetInstance()->IsDoubleShot())
	doubleShot->Draw(x + 312.0f, y + 35.0f, GenerateAlpha());
}

void Board::ReloadAni()
{
	ani_set = CAnimationSets::GetInstance()->Get(BOARD_ID);
	HP_set = CAnimationSets::GetInstance()->Get(8);
	font = new CFont();
	doubleShot = CSprites::GetInstance()->Get(40024);
	SetSpriteSubWeap();
}

void Board::Update()
{
	x = cam->GetCamX();
	y = cam->GetCamY();
	if (!isFinish) 
	{
		if(simon->IsFreeze())
		simon->SetisFreeze(false);
		if (GetTickCount() - healtime >= 1000)
		{
			if (board_health < simon->GetHealth())
			{
				board_health += 1;
			}
			else
			{
				board_health = simon->GetHealth();
			}
				time_flag = true;
		}
		else
			time_flag = false;
		if (time != 0 && GetTickCount() - healtime >= 1000)
		{
			time--;
			healtime = 0;
			time_flag = true;
		}
		else
			time_flag = false;
	}
	else
	{
		simon->SetisFreeze(true);
		if (GetTickCount() - healtime >= 1000)
		{
			if (board_health < 16)
				board_health += 1;
			time_flag = true;
		}
		else
			time_flag = false;
		if (time != 0 && board_health == 16)
		{
			time--;
			score += 10;
		}
		if (simon->GetHearts()!=0 && time == 0)
		{
			simon->SetHearts(simon->GetHearts() - 1);
			score += 100;
		}
		if (simon->GetHearts() == 0)
			isFinish = false;
	}
	SetSpriteSubWeap();
	if (Simon::GetInstance()->IsDoubleShot() && flashingTime == 0)
		flashingTime = GetTickCount();
	else if (Simon::GetInstance()->IsDoubleShot() == false)
		flashingTime = 0;
}
int Board::GenerateAlpha() {
	int randNum = 255;
	if (GetTickCount() - flashingTime < 2000)
		randNum = rand() % 256;
	return randNum;
}
void Board::SetSpriteSubWeap()
{
	if (dynamic_cast<Dagger *>(Simon::GetInstance()->GetSubWeapon()))
		 sprite = CSprites::GetInstance()->Get(DAGGER_SPRITE);
	else if( dynamic_cast<StopWatch *>(Simon::GetInstance()->GetSubWeapon()))
		sprite = CSprites::GetInstance()->Get(STOPWATCH_SPRITE);
	else if (dynamic_cast<HolyWater *>(Simon::GetInstance()->GetSubWeapon()))
		sprite = CSprites::GetInstance()->Get(HOLYWATER_SPRITE);
	else sprite = NULL;
}

void Board::RewardingPoints(CGameObject * obj)
{
	if (dynamic_cast<CEnemy*>(obj))
	{
		SetScore(GetScore() + ENEMY_POINT_WORTH);
	}
	else if (dynamic_cast<CHolder*>(obj))
	{
		SetScore(GetScore() + HOLDER_POINT_WORTH);
	}
	else if (dynamic_cast<Item*>(obj))
	{
		Item* item = dynamic_cast<Item*>(obj);
		if (item->isEaten)
		{
			SetScore(GetScore() + ITEM_POINT_WORTH);
		}
	}
}
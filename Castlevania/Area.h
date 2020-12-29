#pragma once
#pragma once
#include <Windows.h>
#include <d3dx9.h>
#define LIMIT_LEFT_CAM_21	0
#define LIMIT_RIGHT_CAM_21	2285
#define LIMIT_LEFT_CAM_22	3072
#define LIMIT_RIGHT_CAM_22	3310
#define LIMIT_LEFT_CAM_23	4076
#define LIMIT_RIGHT_CAM_23	4864
class Area
{
	int areaID = 22;
	float spawnPos = 3500;
	float limitLeftCam = 0;
	float limitRightCam;

	static Area * __instance;
public:
	Area() {};

	int GetAreaID() { return areaID; }
	float GetSpawnPos() { return spawnPos; }
	float GetLimitLeftCam() { return limitLeftCam; }
	float GetLimitRightCam() { return limitRightCam; }

	void SetAreaID(int areaID) { this->areaID = areaID; }
	void SetSpawnPos(float spawnPos) { this->spawnPos = spawnPos; }
	void SetLimitLeftCam(float limitLeftCam) { this->limitLeftCam = limitLeftCam; }
	void SetLimitRightCam(float limitRightCam) { this->limitRightCam = limitRightCam; }

	static Area* GetInstance();

};
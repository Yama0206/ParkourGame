#pragma once
#include "FootBox.h"
#include "DxLib.h"

//’è‹`
const float ROCK_X_SIZE = 140.0f;
const float ROCK_Y_SIZE = 5.0f;
const float ROCK_Z_SIZE = 120.0f;

class CRock : public CFootBox
{
private:

public:
	void Init();					//‰Šú‰»
	void Init(VECTOR vPos, VECTOR vScale);			//‰ŠúÀ•W
	void Load();					//“Ç‚İ‚İ	
	void Step();					//’Êíˆ—
	void Draw();					//•`‰æ
	void Fin();						//I—¹ˆ—
};

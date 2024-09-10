#pragma once
#include "../Read.h"

struct SObject
{
	VECTOR m_vPos;
	VECTOR m_vSize;
	VECTOR m_vRot;


};

class CObjectRead : public CRead
{
private:

public:
	void Read();
};

#pragma once
#include "bear.h"
/*
MOMMA-BEAR
*/

class Mommabear:public Bear {
	public:
	Mommabear(float aWeight);
	
	void SetCub(Bear* aCub);
	Bear* GetCub(void) ;
	virtual float Meanness(void) ;
	float TotalMeanness(void);
	
	protected:
	Bear* cub;
	
	public:
	static void TestBears(void);
};
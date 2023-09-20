#pragma once
#include <stdio.h>
#include "bear.h"

Bear::Bear(float aWeight) {
	weight=aWeight;
}

void Bear::SetWeight(float aWeight){
	weight = aWeight;
}

float Bear::GetWeight(void){
	return weight;
}

float Bear::Meanness(void){
	if (weight <= 100)
		return (weight*2);
	else
		return (weight*3);
}
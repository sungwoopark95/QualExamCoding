#include <stdio.h>
#include "mommabear.h"

Mommabear::Mommabear(float aWeight)
			:Bear(aWeight)
{
	cub=NULL;
}

void Mommabear::SetCub(Bear* aCub){
	cub = aCub;
}							

Bear* Mommabear::GetCub(void){
	return cub;
}

float Mommabear::Meanness(void){
	return (Bear::Meanness()*2);
}

float Mommabear::TotalMeanness(void) {
	float cubMeanness;
	if (cub==NULL)
		cubMeanness=0.0;
	else
		cubMeanness=cub->Meanness();
	return (Meanness()+cubMeanness);
}

void Mommabear::TestBears(void){
	Bear* cub;
	Mommabear* mom;
	cub = new Bear(50);
	mom = new Mommabear(300);
	
	
	printf("%g\n", cub->Meanness());
	printf("%g\n", mom->Meanness());
	mom->SetCub(cub);
	cub->SetWeight(75);
	printf("%g\n", mom->TotalMeanness());
}
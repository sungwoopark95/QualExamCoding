#pragma once

//bear.h  file
class Bear {
	public:
	Bear(float aWeight);  //constructor
	
	void SetWeight(float aWeight); //weight
	float GetWeight(void);
	virtual float Meanness(void);
	
	protected:
	float weight;
};
#ifndef _Timer_H_
#define _Timer_H_

#include "Object.h"
#include "vector"
#include "data.h"
#include "string"
using namespace FTD;

class Timer 
{
public:
	Timer(); 
	// Restore callback function's attribute
	std::vector<SELECTOR*> selector;

	// To avoid out of range
	bool isSeltChange;

	// Initialize selector function
	void bindObjectAndSelector(Object*, SELECTOR*);
	void initAttr(SELECTOR*, float interval, float delay, int times);	
	void setDelayRemove(SELECTOR*, float);

	void update(float);
};

#endif
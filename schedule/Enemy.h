#ifndef _Enemy_H_
#define _Enemy_H_

#include "Object.h"

class Enemy :public Object
{
public:
	Enemy(const string& _name);
	virtual ~Enemy();

	// Initialize
	void init(float attack, float defence, float hp, float ex);
	void bindFightCallback();

	// attribute
	string name;
	float attack;
	float defence;
	float hp;
	float ex;
};

#endif
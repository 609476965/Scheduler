#ifndef _State_H_
#define _State_H_

template<typename object_type>
class State
{
public:
	virtual ~State(){};
	virtual void execute(object_type){};
	virtual void enter(object_type){};
	virtual void exit(object_type){};
	virtual int getType(){ return -1; }; 
	virtual void print(){ cout << "base" << endl; };
};

#endif
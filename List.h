#ifndef __LIST__
#define __LIST__
#include <stdio.h>
#define NaN 10e-66

#include "Array.h"

class List{
public:
	List();
	bool    append(double key);
	bool    prepend(double key);
	double  remove(int i);
	double  at(int i);
	void    print();
public:
	static const int SIZE=6; //Do Not Modify
private:
	Array   DATA;
	int     next;
};

#endif

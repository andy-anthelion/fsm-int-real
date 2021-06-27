#include "Array.h"

#include<cmath>// for NaN

Array::Array(int size){
	SIZE = size;
	DATA = new double[size];
}
Array::~Array(){
	delete DATA;
}

double Array::Get(int pos){
	if(pos >= SIZE) 
		return nan("");
	return DATA[pos];
}
bool Array::Set(int pos, double key){
	if(pos >= SIZE){
		return false;
	}
	DATA[pos] = key;
	return true;
}


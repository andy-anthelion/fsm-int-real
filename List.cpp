#include "List.h"

#include "Array.h"

#include<cmath>

List::List():
	DATA(List::SIZE)
{
	next = 0;
}

bool    List::append(double key){
	if(DATA.Set(next,key)){
		next = next+1;
		return true;
	}
	return false;
}
double  List::remove(int i){
	double key;
	if(i>=next || i<0) return nan("");
	if(next == 0)      return nan("");

	key = DATA.Get(i);

	while( i<next-1){
		DATA.Set(i,DATA.Get(i+1));
		i = i+1;
	}
	next = next-1;
	return key;
}
double  List::at(int i){
	if(i>=next || i<0) return NaN;
	return DATA.Get(i);
}
void   List::print(){
	int i;
	printf("[");
	for( i=0; i<next; i++){
		printf("%lf",DATA.Get(i));
		printf(", ");
	}
	printf("]");
}

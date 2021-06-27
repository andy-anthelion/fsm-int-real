#ifndef __ARRAY__
#define __ARRAY__
#define NaN 10e-66

using namespace std;
class Array{
private:
	double *DATA;
	int     SIZE;
public:
	Array(int size);
	~Array();
	double Get(int pos);
	bool   Set(int pos, double key);
};

#endif

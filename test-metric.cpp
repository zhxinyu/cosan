// #include<cosan/utils/CosanMetric.h>
#include<cosan/data/CosanData.h>

/*
	test cases for metric functions
	They are located in utils/CosanMetric.h
*/
using namespace cosan;
using namespace std;

int main()
{
	CosanMatrix m(2,2);
	m(0,0) = 3;
	m(1,0) = 2.5;
 	m(0,1) = -1;
  	m(1,1) = m(1,0) + m(0,1);
  	cout << m;
	return 0;
}
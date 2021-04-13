//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/Paralleltest.cpp
#include <iostream>
#include <vector>
#include <cosan/selection/kfold.h>
#include <cosan/selection/randomkfold.h>
#include <cosan/selection/timeseriessplit.h>

#include <chrono>
#include <algorithm>
int main(){
 //    std::chrono::time_point<std::chrono::system_clock> st,ed;
 //    std::chrono::duration<double> tmp,tmp1;

	// gsl::index nrows = 100000;
	// gsl::index foldnum = 50000;
	// st = std::chrono::system_clock::now();
	// Cosan::KFoldParallel(nrows,foldnum);
	// ed = std::chrono::system_clock::now();
 //    tmp = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);

	// st =std::chrono::system_clock::now();
	// Cosan::KFold(nrows,foldnum);
	// ed = std::chrono::system_clock::now();

 //    tmp1 = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);	
	// std::cout<<tmp.count()<<" "<<tmp1.count()<<std::endl;
	// return 0;
	// // run comparison: parallel 24.6386s, without parallel: 34.9594s

 //    std::chrono::time_point<std::chrono::system_clock> st,ed;
 //    std::chrono::duration<double> tmp,tmp1;

	// gsl::index nrows = 100000;
	// gsl::index foldnum = 50000;
	// st = std::chrono::system_clock::now();
	// Cosan::RandomKFoldParallel(nrows,foldnum);
	// ed = std::chrono::system_clock::now();
 //    tmp = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);

	// st =std::chrono::system_clock::now();
	// Cosan::RandomKFold(nrows,foldnum);
	// ed = std::chrono::system_clock::now();

 //    tmp1 = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);	
	// std::cout<<tmp.count()<<" "<<tmp1.count()<<std::endl;

	// run comparison: parallel 28.6542s, without parallel: 106.003s

    std::chrono::time_point<std::chrono::system_clock> st,ed;
    std::chrono::duration<double> tmp,tmp1;

	gsl::index nrows = 100000;
	gsl::index foldnum = 50000;
	st = std::chrono::system_clock::now();
	Cosan::TimeSeriesSplitParallel(nrows,foldnum);
	ed = std::chrono::system_clock::now();
    tmp = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);

	st =std::chrono::system_clock::now();
	Cosan::TimeSeriesSplit(nrows,foldnum);
	ed = std::chrono::system_clock::now();

    tmp1 = std::chrono::duration_cast<std::chrono::duration<double>>(ed-st);	
	std::cout<<tmp.count()<<" "<<tmp1.count()<<std::endl;

	// run comparison: parallel 10.3986s , without parallel: 16.503s

	return 0;
}

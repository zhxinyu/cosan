//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/Paralleltest.cpp
#include <iostream>
#include <vector>
#include <cosan/selection/kfoldparallel.h>
#include <cosan/selection/kfold.h>
#include <cosan/selection/randomkfoldparallel.h>
#include <cosan/selection/randomkfold.h>
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
	// // run comparison: parallel 26.5309s, without parallel: 35.0404s

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

	// run comparison: parallel 30.0762s, without parallel: 106.003s

	auto a = Cosan::RandomKFoldParallel(11).GetSplit();

	for (auto & each:a){
		fmt::print("Train Index: ");
		for (auto& each_test :std::get<0>(each)){
			std::cout<<each_test;
		}		
		std::cout<<std::endl;
		fmt::print("Test Index: ");
		for (auto& each_test :std::get<1>(each)){
			std::cout<<each_test;
		}	
	}
	std::cout<<std::endl;
	auto a = Cosan::RandomKFold(11).GetSplit();

	for (auto & each:a){
		fmt::print("Train Index: ");
		for (auto& each_test :std::get<0>(each)){
			std::cout<<each_test;
		}		
		std::cout<<std::endl;
		fmt::print("Test Index: ");
		for (auto& each_test :std::get<1>(each)){
			std::cout<<each_test;
		}	
	}
	std::cout<<std::endl;	
	return 0;
}

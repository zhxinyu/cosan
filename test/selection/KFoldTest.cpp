//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/selection/KFoldTest.cpp

#include <iostream>
#include <vector>
#include <cosan/selection/kfold.h>


int main(){

	auto a = Cosan::KFold(11).GetSplit();

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
		std::cout<<std::endl;

	}
	std::cout<<a.size()<<std::endl;

	
	// auto a = Cosan::RandomKFoldParallel(11).GetSplit();

	// for (auto & each:a){
	// 	fmt::print("Train Index: ");
	// 	for (auto& each_test :std::get<0>(each)){
	// 		std::cout<<each_test;
	// 	}		
	// 	fmt::print("Test Index: ");
	// 	for (auto& each_test :std::get<1>(each)){
	// 		std::cout<<each_test;
	// 	}	
	
	// 	std::cout<<std::endl;
	// }
	// a = Cosan::RandomKFold(11).GetSplit();

	// for (auto & each:a){
	// 	fmt::print("Train Index: ");
	// 	for (auto& each_test :std::get<0>(each)){
	// 		std::cout<<each_test;
	// 	}		
	// 	fmt::print("Test Index: ");
	// 	for (auto& each_test :std::get<1>(each)){
	// 		std::cout<<each_test;
	// 	}	
	// 	std::cout<<std::endl;	
	// }
	return 0;
}
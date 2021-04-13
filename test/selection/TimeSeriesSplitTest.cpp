//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/selection/TimeSeriesSplitTest.cpp

#include <iostream>
#include <vector>
#include <cosan/selection/timeseriessplit.h>
// #include <cosan/selection/timeseriessplitparallel.h>


int main(){

	auto a = Cosan::TimeSeriesSplit(6,5).GetSplit();

	for (auto & each:a){
		fmt::print("Train Index: ");
		for (auto& each_test :std::get<0>(each)){
			std::cout<<each_test;
		}		
		fmt::print("Test Index: ");
		for (auto& each_test :std::get<1>(each)){
			std::cout<<each_test;
		}		
		std::cout<<std::endl;

	}

	a = Cosan::TimeSeriesSplitParallel(6,5).GetSplit();
	for (auto & each:a){
	fmt::print("Train Index: ");
	for (auto& each_test :std::get<0>(each)){
		std::cout<<each_test;
	}		
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
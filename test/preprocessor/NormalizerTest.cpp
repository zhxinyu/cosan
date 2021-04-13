//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/preprocessor/NormalizerTest.cpp 

#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/preprocessing/normalizer.h>
#include <vector>
//using namespace Eigen;
//using namespace std;

int main() {

	Cosan::Normalizer normalizer;	
	Cosan::Normalizer normalizer1(1);	
	Cosan::Normalizer normalizerinf(std::numeric_limits<int>::max());	
	// Cosan::Normalizer normalizer3(3);		
	Cosan::CosanMatrix X1{3,3};

	X1<<3,4,0,
	    2,0,0,
	    5,12,13;

    std::cout << normalizer.normalize(X1) << '\n' << std::endl;

    Cosan::CosanMatrix X2{3, 3};

    X2 << 1, -1, 2,
            2, 0, 0,
            0, 0, 1;

    std::cout << normalizer.normalize(X2) << '\n' << std::endl;

    Cosan::CosanMatrix X3{3, 3};

	X3 << 1, -1, 2,
	            2, 0, 0,
	            0, 0, 0;

    std::cout << normalizer.normalize(X3) << '\n' << std::endl;    
    std::cout << normalizer1.normalize(X3) << '\n' << std::endl;    
    std::cout << normalizerinf.normalize(X3) << '\n' << std::endl;        
    Cosan::CosanMatrix X4{3, 1};

	X4 << 1, 
			2,
			0 ;

    std::cout << normalizer.normalize(X4) << '\n' << std::endl;        

	std::vector<double> values= {-1, 1, 0};
	

    std::cout << normalizer.normalize(Eigen::Map<const EigenMatrix>(values.data(), 1, 3)) << '\n' << std::endl;


    return 0;
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}

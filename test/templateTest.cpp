#include <iostream>
#include <vector>
#include <type_traits>
#include <numeric>
#include <string>
#include <gsl/gsl>
#include <Eigen/Dense>
namespace Cosan
{
//    MISSING VALUES, STRING, NUMERICAL
    template<typename NumericType,
             typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type
    >
    using vec = std::vector<NumericType> ;

    template<typename NumericType,
             typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type
    >
    using CosanMatrix = Eigen::Matrix<NumericType, Eigen::Dynamic, Eigen::Dynamic> ;

	template <typename NumericType=std::string>
	NumericType StringToNum(std::string arg) {
	    if constexpr (std::is_same_v<NumericType, unsigned long>) {
	    	return std::stoul(arg);
	    } 
	    else if constexpr (std::is_same_v<NumericType, unsigned long long>){
	    	return std::stoull(arg);
	    }
	    else if constexpr (std::is_same_v<NumericType, int>){
	    	return std::stoi(arg);
	    }
	    else if constexpr (std::is_same_v<NumericType, long>){
	    	return std::stol(arg);
	    }
	    else if constexpr (std::is_same_v<NumericType, long long>){
	    	return std::stoll(arg);
	    }
	    else if constexpr (std::is_same_v<NumericType, float>){
	    	return std::stof(arg);
	    }
	    else if constexpr (std::is_same_v<NumericType, double>){
	    	return std::stod(arg);
	    }
	    else{
	    	return std::stold(arg);
	    }	    
	}

    template<typename NumericType,
             typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type> 
	class Test {
		public:
			Test()=default;
			Test(vec<NumericType>& inputX){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");				
				b = inputX; 
				a = sumfunction(b);
			}
			Test(vec<NumericType> inputX){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");				
				b = inputX; 
				a = sumfunction(b);
			}			
			NumericType a;
			vec<NumericType> b;
			CosanMatrix<NumericType> face;
		private:
			NumericType sumfunction(vec<NumericType> &a){
				CosanMatrix<NumericType> X = Eigen::Map<const CosanMatrix<NumericType>>(a.data(), 1, a.size());
				std::cout<<X<<std::endl;
				return std::accumulate(a.begin(), a.end(), 0);
			}

	}    ;
}

int main(){

	// std::vector<bool> myVec = {0,1,1,0,0,1,0,1,0,1};
	// Eigen::Matrix<bool,2,5,Eigen::RowMajor> X1,X2;
	// for (gsl::index i =0;i<myVec.size();i++){
	// 	X1(i/5,i%5)=myVec[i];
	// }	
	// std::copy(myVec.begin(),myVec.end(),X2.data());
	// std::cout<<X1<<std::endl;
	// X2.resize(2, 5);
	// std::cout<<X2<<std::endl;	
	// std::string a = "nan";
	// std::cout<<Cosan::StringToNum<int>(a)<<std::endl;
	Cosan::Test a = Cosan::Test<int>();
	a.face.resize(2,2);
	a.face<<1,2,3,4;
	std::cout<<a.face<<std::endl;
	static_assert(std::is_same_v<decltype(a.face)::Scalar, int>);
	std::cout<<typeid(decltype(a.face)::Scalar).name()<<std::endl;
	return 0;
}
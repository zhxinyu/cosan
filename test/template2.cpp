#include <iostream>
#include <vector>
#include <type_traits>
#include <numeric>
#include <string>
#include <gsl/gsl>
#include <concepts>
#include <cosan/data/CosanData.h>
// // Maybe useful to restricted to only CosanBO class. 
// template <class T, class U>
// concept Derived = std::is_base_of<U, T>::value;

// // Useful for Metric, Model, Splittor class. 
// template <class T, class U>
// concept Derived = std::is_base_of<U, T>::value;
 
// template<Derived<Base> T>
// void f(T);  // T is constrained by Derived<T, Base>

template<typename NumericType>
concept Numeric = std::is_arithmetic<NumericType>::value ;

// template<Numeric  T>
template<typename NumericType,
             typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
void f(NumericType a){
	std::cout<<a<<std::endl;

}
// template<typename T> using Ref = T&;
// template<typename T> concept C =
// requires {
//     typename T::inner; // required nested member name
//     typename S<T>;     // required class template specialization
//     typename Ref<T>;   // required alias template substitution
// };
 
// template <class T, class U> using CommonType = std::common_type_t<T, U>;
// template <class T, class U> concept Common =
// requires (T&& t, U&& u) {
//     typename CommonType<T, U>; // CommonType<T, U> is valid and names a type
//     { CommonType<T, U>{std::forward<T>(t)} }; 
//     { CommonType<T, U>{std::forward<U>(u)} }; 
// };


int main(){
	f<std::string>(3);
	int 
	Cosan::CosanMatrix<double> M(5,4);
	return 0;
}

// template<typename T1>
// class A{
//   T1 a;
//   template<class T2, 
//            std::enable_if_t<std::is_same_v<std::decay_t<T2>,std::vector<T1>>,bool> = true>
//   void foo(T2 && a){
//     // stuff
//     }

// }

// int main(){
// 	return 0;
// }

// #include <iostream>
// #include <vector>
// #include <type_traits>
// #include <Eigen/dense>

// template<class T, 
//          std::enable_if_t<std::is_same_v<std::decay_t<T>,Eigen::MatrixXd>,bool> = true>		
// void foo(T && a){
// 	std::cout<<"Hello"<<std::endl;
// }
// int main(){
// 	Eigen::MatrixXd a;
// 	a.resize(3,3);
// 	a<<1,2,3,
// 	   4,5,6,
// 	   7,8,9;
// 	std::cout<<a(std::vector<int>({0,2}),Eigen::all)<<std::endl;
// 	foo(a(std::vector<int>({0,2}),Eigen::all));

// 	return 0;
// }
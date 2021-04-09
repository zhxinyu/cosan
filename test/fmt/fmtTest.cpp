#include <iostream>
#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif
#include <fmt/format.h>
int main() {
	std::cout<<fmt::format("The answer is {}.", 42)<<std::endl;
    return 0;
}

#include <iostream>
#include "kernel.hpp"
using namespace std;

int main(int argc, char** argv) {
	Kernel& kernel = Kernel::get();
	kernel.operate();
}

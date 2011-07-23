#include <iostream>
#include "kernel.hpp"
using namespace std;

int main(int argc, char** argv) {
	Kernel& kernel = Kernel::get();
	cout << "Getting kernel" << endl;
	kernel.ping();
	cout << "Pinging module test" << endl;
	kernel.pingModule("test");
}

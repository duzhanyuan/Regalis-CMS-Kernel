/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include <iostream>
#include "kernel.hpp"
using namespace std;

int main(int argc, char** argv) {
	Kernel& kernel = rcms::Kernel::get();
	kernel.operate();
}

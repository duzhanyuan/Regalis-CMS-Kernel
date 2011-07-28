/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#include "main.hpp"
#include "../../../kernel.hpp"
#include <iostream>
using namespace std;
using namespace rcms;

void ModuleTest::ping() {
	cout << "Hello world from test module!" << endl;
	Kernel::get().ping();
}

bool ModuleTest::init() {
	*log << "Hello!";
	return false;
}

extern "C" {
	KernelModule* factory() {
		return new ModuleTest();
	}
}

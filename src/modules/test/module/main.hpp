/* 
 *
 * Copyright (c) by Patryk Jaworski
 * Contact:
 *  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
 *  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
 *
*/

#ifndef _MODULE_TEST_HPP
#define _MODULE_TEST_HPP

#include "../../interface.hpp"
using namespace rcms;

namespace rcms {
	class ModuleTest : public KernelModule, public Installable {
		public:
			void ping();
			bool init();
			const char* test() const;
		protected:
			bool preInstall();
			bool postInstall();
			bool preRemove();
			bool postRemove();
	};
}

extern "C" {
	KernelModule* factory();
}

#endif

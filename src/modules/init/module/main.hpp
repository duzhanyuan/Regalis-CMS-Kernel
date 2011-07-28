#ifndef _MODULE_INIT_HPP
#define _MODULE_INIT_HPP
#include "../../module.hpp"
using namespace scms;

namespace scms {
	class InitModule : public KernelModule {
		public:
			void ping();
			void run();
	};
}

#endif
